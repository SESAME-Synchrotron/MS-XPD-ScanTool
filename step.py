#!/usr/bin/python3.9
# **: for UI Visualization tool use

import log
import os
import sys
import subprocess
import time
import signal
from datetime import datetime, timedelta
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
		startScanTime = time.time()
		self.totalCollectedPoints = 0		# **
		self.totalPoints = 0
		totalIndex = 0
		for key, value in self.scanPoints.items():
			self.totalPoints += len(value)

		log.info(f"scan start time: {scanStartTime}")

		for interval in range(self.intervals):
			print("\n")
			log.info(f"Interval#{interval + 1}, Exposure Time: {self.exposureTime[interval]}")
			self.epics_pvs["CurrentInterval"].put(interval+1, wait=True)		# **

			for scan in range(self.scans):
				startIntervalTime = time.time()
				log.info(f"scan#{scan + 1}")
				log.info(f"scan points: {self.scanPoints[interval]}")
				self.epics_pvs["CurrentScan"].put(scan+1, wait=True)							# **
				self.epics_pvs["TotalPoints"].put(len(self.scanPoints[interval]), wait=True)	# **

				collectedImages = []
				missedImages = []
				for index, point in enumerate(self.scanPoints[interval], start=1):

					if self.pauseErr:
						self.pause()

					print("-" * 100)
					log.info(f"scan points: {point}")
					self.epics_pvs["CurrentPoint"].put(index, wait=True)	# **

					twoTheta = 0
					for trial in range(4): 								# number of trials to get exactly to target position
						self.epics_motors["TwoTheta"].move(point) 		# move 2theta (detector arm)
						time.sleep(self.settlingTime)
						while not self.epics_motors["TwoTheta"].done_moving:
							twoTheta = self.epics_motors["TwoTheta"].readback
							CLIMessage(f"2theta moving to {point}, {twoTheta}", "IO")
							time.sleep(0.02)

					time.sleep(self.settlingTime)
					imageName = f"{sampleName}_{interval + 1}_{scan + 1}_{index}_{twoTheta:.4f}.tiff"

					try:
						self.epics_pvs["DetExposureTime"].put(self.exposureTime[interval], wait=True)
						self.epics_pvs["ImageName"].put(str(imageName), wait=True)
						self.epics_pvs["isAcquiring"].put(1, wait=True)
						self.epics_pvs["Acquiring"].put(1, wait=True)
						self.epics_pvs["isAcquiring"].put(0, wait=True)

						log.info(f"Collecting image: {imageName}")
						for i in tqdm(range(int(self.exposureTime[interval] * 10)), desc=f"Collecting image: {index}", ascii=False, ncols=100, leave=False):
							time.sleep(0.1)

						log.info(f"acquiring {imageName} has been done")
						if self.transfer(path) != 0:
							missedImages.append(point)
						else:
							collectedImages.append(point)
					except:
						missedImages.append(point)
						log.error(f"can't acquire {imageName}!!!")

					totalImages = f"Total images to be collected in interval#{interval + 1}: {len(self.scanPoints[interval])}"
					collected = f"collected images: {len(collectedImages)}/{len(self.scanPoints[interval])}"
					missed = f"missed images: {len(missedImages)} at scan point/s:{missedImages}"

					self.epics_pvs["CollectedPoints"].put(f"{len(collectedImages)}/{len(self.scanPoints[interval])}", wait=True)	# **

					if len(missedImages):
						log.warning(f"{totalImages} | {collected} | {missed}")
					else:
						log.info(f"{totalImages} | {collected}")

					elapsedIntervalTime = time.time() - startIntervalTime
					elapsedScanTime = time.time() - startScanTime
					totalIndex = totalIndex + 1
					remainingIntervalTime = elapsedIntervalTime * ((len(self.scanPoints[interval]) - index) / max(float(index), 1))
					remainingScanTime = elapsedScanTime * ((self.scans * self.totalPoints - totalIndex) / max(float(totalIndex), 1))
					self.epics_pvs["IntervalRemTime"].put(str(timedelta(seconds=int(remainingIntervalTime))), wait=True)		# **
					self.epics_pvs["ScanRemTime"].put(str(timedelta(seconds=int(remainingScanTime))), wait=True)				# **

					if self.exit:
						sys.exit()

				self.totalCollectedPoints += len(collectedImages)	# **
				log.info(f"expected remaining time for the scan: {str(timedelta(seconds=int(remainingScanTime)))}")
				print("#" * 100)

		self.epics_pvs["TotalCollectedPoints"].put(f"{self.totalCollectedPoints}/{self.totalPoints*self.scans}", wait=True)	# **
		scanEndTime = datetime.now().strftime("%d.%m.%Y %H:%M:%S")
		log.info(f"scan end time: {scanEndTime}")

		log.warning("stop spinner after the scan ...")
		self.stopSpinner()

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