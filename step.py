#!/usr/bin/python3.9
# **: for UI Visualization tool use

import log
import os
import sys
import subprocess
import time
from datetime import datetime, timedelta
import signal
import threading
from epics import PV
from tqdm import tqdm

from MS import XPD
from emailNotifications import email
from SEDSS.CLIMessage import CLIMessage

class step(XPD):
	def __init__(self, PVsFiles, macros, scanningSubs):
		super().__init__(PVsFiles, macros, scanningSubs)

		self.intervals, self.scans, self.scanPoints, self.exposureTime = self.calcScanPoints()
		self.settlingTime = self.epics_pvs["SettlingTime"].get(timeout=self.timeout, use_monitor=False)

	def scan(self, path, sampleName):
		"""
		Scan:
		- start scanning (intervals >> scans >> intervals points)
		- calculate time parameters
		"""

		log.warning("move spinner before the scan ...")
		self.moveSpinner()
		time.sleep(1)

		CLIMessage(f"#Intervals: {self.intervals}, #Scans: {self.scans}", "I")
		log.info(f"#Intervals: {self.intervals}, #Scans: {self.scans}")

		scanStartTime = datetime.now().strftime("%d.%m.%Y %H:%M:%S")
		self._path = path
		self._totalCollectedPoints = 0		# **
		self._totalPoints = 0
		intervalsTime = 0		# **
		totalIndex = 0
		for interval in range(self.intervals):
			self._totalPoints += len(self.scanPoints[interval])
			intervalsTime += len(self.scanPoints[interval]) * self.scans * ((1 / float(self.epics_pvs["TwoThetaSpeed"].get(timeout=self.timeout, use_monitor=False))) + self.exposureTime[interval] + self.settlingTime)
		intervalsTime += (float(self.epics_pvs["TwoThetaRange"].get(timeout=self.timeout, use_monitor=False)) / float(self.epics_pvs["TwoThetaSpeed"].get(timeout=self.timeout, use_monitor=False)))
		self._totalPoints *= self.scans
		threading.Thread(target=self.expectedRemainingTime, args=(intervalsTime,), daemon=True).start()		# **

		log.info(f"scan start time: {scanStartTime}")

		for interval in range(self.intervals):
			self._interval = interval
			print("\n")
			log.info(f"Interval#{interval + 1}, Exposure Time: {self.exposureTime[interval]}")
			self.epics_pvs["CurrentInterval"].put(interval+1, wait=True)		# **

			for scan in range(self.scans):
				startIntervalTime = time.time()
				log.info(f"scan#{scan + 1}")
				log.info(f"scan points: {self.scanPoints[interval]}")
				self.epics_pvs["CurrentScan"].put(scan+1, wait=True)							# **
				self.epics_pvs["TotalPoints"].put(len(self.scanPoints[interval]), wait=True)	# **

				self._collectedImages = []
				self._missedImages = []
				for index, point in enumerate(self.scanPoints[interval], start=1):
					self._index = index
					self._point = point

					if self.pauseErr:
						self.pause()

					print("-" * 100)
					log.info(f"scan points: {point}")
					self.epics_pvs["CurrentPoint"].put(index, wait=True)	# **

					twoTheta = self.moveTheta(point)
					imageName = f"{sampleName}_{interval + 1}_{scan + 1}_{index}_{twoTheta:.4f}.tiff"
					self.acquire(imageName)

					elapsedIntervalTime = time.time() - startIntervalTime
					totalIndex += 1
					remainingIntervalTime = elapsedIntervalTime * ((len(self.scanPoints[interval]) - index) / max(float(index), 1))
					self.epics_pvs["IntervalRemTime"].put(str(timedelta(seconds=int(remainingIntervalTime))), wait=True)		# **

					if self.exit:
						sys.exit()

				self._totalCollectedPoints += len(self._collectedImages)	# **
				self.epics_pvs["TotalCollectedPoints"].put(f"{self._totalCollectedPoints}/{self._totalPoints}", wait=True)	# **
				print("#" * 100)

		scanEndTime = datetime.now().strftime("%d.%m.%Y %H:%M:%S")
		log.info(f"scan end time: {scanEndTime}")

		log.warning("stop spinner after the scan ...")
		self.stopSpinner()

	def moveTheta(self, point):

		twoTheta = 0
		for trial in range(4): 											# number of trials to get exactly to target position
			self.epics_motors["TwoTheta"].move(point, wait=True) 		# move 2theta (detector arm)
			time.sleep(self.settlingTime)
			while not self.epics_motors["TwoTheta"].done_moving:
				twoTheta = self.epics_motors["TwoTheta"].readback
				CLIMessage(f"2theta moving to {point}, {twoTheta}", "IO")
				time.sleep(0.02)
		time.sleep(self.settlingTime)

		return twoTheta

	def acquire(self, imageName):

		try:
			self.epics_pvs["DetExposureTime"].put(self.exposureTime[self._interval], wait=True)
			self.epics_pvs["ImageName"].put(str(imageName), wait=True)
			self.epics_pvs["isAcquiring"].put(1, wait=True)
			self.epics_pvs["Acquiring"].put(1, wait=True)
			self.epics_pvs["isAcquiring"].put(0, wait=True)

			log.info(f"Collecting image: {imageName}")
			for i in tqdm(range(int(self.exposureTime[self._interval] * 10)), desc=f"Collecting image: {self._index}", ascii=False, ncols=100, leave=False):
				time.sleep(0.1)

			log.info(f"acquiring {imageName} has been done")
			if self.transfer(self._path) != 0:
				self._missedImages.append(self._point)
			else:
				self._collectedImages.append(self._point)
		except:
			self._missedImages.append(self._point)
			log.error(f"can't acquire {imageName}!!!")

		totalImages = f"Total images to be collected in interval#{self._interval + 1}: {len(self.scanPoints[self._interval])}"
		collected = f"collected images: {len(self._collectedImages)}/{len(self.scanPoints[self._interval])}"
		missed = f"missed images: {len(self._missedImages)} at scan point/s:{self._missedImages}"

		self.epics_pvs["CollectedPoints"].put(f"{len(self._collectedImages)}/{len(self.scanPoints[self._interval])}", wait=True)	# **

		if len(self._missedImages):
			log.warning(f"{totalImages} | {collected} | {missed}")
		else:
			log.info(f"{totalImages} | {collected}")

	def transfer(self, path):
		"""
		Transfer:
		- rsync the images from cam server
		- remove the images (--remove-source-files)
		"""

		result = subprocess.run(f"rsync --remove-source-files -aqc {self.pilatusServerUser}@{self.pilatusServer}:{self.detDataPath}/* {self.dataPath}/{path}", shell=True, stderr=subprocess.PIPE)
		if result.returncode != 0:
			log.error(f"rsync to {self.dataPath}/{path} failed!")
		return result.returncode

	def stopSpinner(self):

		PV(f"{self.spinner}.STOP").put(1)

		CLIMessage("stop spinner ...", "W")
		time.sleep(1)
		if not self.waitSpinner(1):
			msg = "can't stop the spinner!!!"
			CLIMessage(msg,"E")
			log.error(msg)
			self.epics_pvs["ProgInt"].put(1, wait=True)
			self.programmaticInterrupt = True
			self.epics_pvs["ScanStatus"].put(5, wait=True)
			if not self.testingMode:
				email(self.experimentType, self.proposalID).sendEmail("spinnerStop", DS=self.fullExpDataPath)
			os.kill(os.getpid(), signal.SIGINT)

	def moveSpinner(self):

		PV(self.spinner + ".JVEL").put(200, wait=True)
		PV(self.spinner + ".SET").put(1, wait=True)
		PV(self.spinner + ".VAL").put(0, wait=True)
		PV(self.spinner + ".SET").put(0, wait=True)
		PV(self.spinner + ".JOGF").put(1)

		time.sleep(1)
		CLIMessage("move spinner ...", "W")
		if not self.waitSpinner(0):
			msg = "can't move the spinner!!!"
			CLIMessage(msg,"E")
			log.error(msg)
			self.epics_pvs["ProgInt"].put(1, wait=True)
			self.epics_pvs["ScanStatus"].put(5, wait=True)
			if not self.testingMode:
				email(self.experimentType, self.proposalID).sendEmail("spinnerMove", DS=self.fullExpDataPath)
			os.kill(os.getpid(), signal.SIGINT)

	def waitSpinner(self, val, timeout = 60):
		"""
		Check the Motor value is reached to the target val within predefined timeout
		"""
		startTime = time.time()
		while time.time() - startTime < timeout:
			checkVal = self.epics_motors["Spinner"].done_moving

			if checkVal == val:
				return True
			time.sleep(1)

		return False