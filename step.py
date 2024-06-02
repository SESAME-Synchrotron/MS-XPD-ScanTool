#!/usr/bin/python3.9
# **: for UI Visualization tool use

import log
import os
import sys
import subprocess
import math
import time
from datetime import datetime, timedelta
import signal
import threading
from epics import PV
from tqdm import tqdm
import csv

from MS import XPD
from emailNotifications import email
from SEDSS.CLIMessage import CLIMessage

class step(XPD):
	def __init__(self, PVsFiles, macros, scanningSubs):
		super().__init__(PVsFiles, macros, scanningSubs)

		self.intervals, self.scans, self.scanPoints, self.exposureTime, self.stepSize = self.calcScanPoints()
		self.settlingTime = self.epics_pvs["SettlingTime"].get(timeout=self.timeout, use_monitor=False)
		self.waitingTime = self.epics_pvs["WaitingTime"].get(timeout=self.timeout, use_monitor=False)
		self.spinnerSpeed = PV(self.spinner + ".JVEL").get(timeout=self.timeout, use_monitor=False)
		self.IonChamberPV = PV("I09-DI-AMP-1:getVoltage")	# temporary

	def scan(self, path, sampleName):
		"""
		Scan:
		- calculate expected theoretical remaining time:
			interval time = ((#scanIntervalPoints * stepSize) or (endPoint - startPoint) / motorSpeed)
			+ (#scanIntervalPoints * #Scans * (exposureTime + motorSettlingTime))
			+ (#Scans * waitingTime)
			+ transition time between intervals
			+ margin log base 2
		- start scanning (intervals >> scans >> intervals points)
		- calculate time parameters
		"""

		# temporary
		with open(self.ICFile, 'a', newline='') as f:
			self.header = ["interval", "scan", "index", "twoTheta", "ICVoltage"]
			writer = csv.DictWriter(f, fieldnames=self.header)
			writer.writeheader()

		if not self.GIXRD:
			log.warning("move spinner before the scan ...")
			self.moveSpinner()
		else:
			log.info("GIXRD Scan")

		CLIMessage(f"#Intervals: {self.intervals}, #Scans: {self.scans}", "I")
		log.info(f"#Intervals: {self.intervals}, #Scans: {self.scans}")

		scanStartTime = datetime.now().strftime("%d.%m.%Y %H:%M:%S")
		self._path = path
		self._totalCollectedPoints = 0		# **
		self._totalPoints = 0
		intervalsTime = 0		# **
		totalIndex = 0
		speed = float(self.epics_pvs["TwoThetaSpeed"].get(timeout=self.timeout, use_monitor=False))		# **

		for interval in range(self.intervals):
			points = len(self.scanPoints[interval])
			self._totalPoints += points
			transitionTime = abs(self.data_pvs[f"EndPoint{interval+1}"].get(timeout=self.timeout, use_monitor=False) - self.data_pvs[f"StartPoint{interval+2}"].get(timeout=self.timeout, use_monitor=False)) / speed if (interval + 1) != self.intervals else 0		# **
			intervalsTime += (points * (self.stepSize[interval] / speed + self.scans * (self.exposureTime[interval] + self.settlingTime))
					  + self.scans * self.waitingTime + transitionTime)

		intervalsTime += abs(self.epics_motors["TwoTheta"].readback - self.data_pvs["StartPoint1"].get(timeout=self.timeout, use_monitor=False)) / speed
		intervalsTime += math.log(intervalsTime, 2)
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

				if self.scans > 1:
					log.warning(f"waiting time ({self.waitingTime} sec) ...")
					time.sleep(self.waitingTime)

				self._collectedImages = []
				self._missedImages = []
				for index, point in enumerate(self.scanPoints[interval], start=1):
					self._index = index
					self._point = point

					if self.pauseErr:
						self.pause()

					print("-" * 100)
					log.info(f"scan point: {point}")
					self.epics_pvs["CurrentPoint"].put(index, wait=True)	# **

					twoTheta = self.moveTheta(point)
					imageName = f"{sampleName}_{interval + 1}_{scan + 1}_{index}_{twoTheta:.4f}.tiff"
					info = imageName.split("_")
					self.csvData = {"interval": info[-4], "scan": info[-3], "index": info[-2], "twoTheta": info[-1].replace(".tiff", "")}	# temporary
					self.acquire(imageName)
					self.dataTransfer(imageName)

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

		if not self.GIXRD:
			log.warning("stop spinner after the scan ...")
			self.stopSpinner()

	def moveTheta(self, point):

		twoTheta = 0
		self.epics_motors["TwoTheta"].move(point, wait=True)
		time.sleep(self.settlingTime)
		twoTheta = self.epics_motors["TwoTheta"].readback

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

		# temporary part to dump IC voltage in csv file
		with open(self.ICFile, 'a', newline='') as f:
			writer = csv.DictWriter(f, fieldnames=self.header)

			ICVoltage = self.IonChamberPV.get(timeout=self.timeout, use_monitor=False)
			log.info(f"acquiring IC voltage {ICVoltage} V")
			self.csvData["ICVoltage"] = ICVoltage
			writer.writerow(self.csvData)

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
				email(self.experimentType, self.proposalID).sendEmail("spinnerStop", DS=self.localExpDataPath, userIn="No")
			os.kill(os.getpid(), signal.SIGINT)

	def moveSpinner(self):

		PV(self.spinner + ".JVEL").put(self.spinnerSpeed, wait=True)
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
				email(self.experimentType, self.proposalID).sendEmail("spinnerMove", DS=self.localExpDataPath, userIn="No")
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