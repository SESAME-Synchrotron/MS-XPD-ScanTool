#!/usr/bin/python3.9

import log
import os
import time
import signal
from datetime import datetime, timedelta
from epics import PV

from MS import XPD
from SEDSS.CLIMessage import CLIMessage

spinner = "I09R2-MO-MC1:ES-DIFF-STP-ROTX3"

class step(XPD):
	def __init__(self, PVsFiles, macros, scanningSubs):
		super().__init__(PVsFiles, macros, scanningSubs)

		# self.preCheck()
		# self.initDir()
		# self.detectorInit()

		self.intervals, self.scans, self.scanPoints = self.calcScanPoints()

	def scan(self):

		log.warning("move spinner before the scan ...")
		self.moveSpinner()
		time.sleep(1)

		CLIMessage(f"#Intervals: {self.intervals}, #Scans: {self.scans}", "I")
		log.info(f"#Intervals: {self.intervals}, #Scans: {self.scans}")

		scanStartTime = datetime.now().strftime("%d.%m.%Y %H:%M:%S")
		startScanTime = time.time()
		totalPoints = 0
		totalIndex = 0
		for key, value in self.scanPoints.items():
			totalPoints += len(value)

		log.info(f"scan start time: {scanStartTime}")

		for interval in range(self.intervals):
			log.info(f"Interval#{interval + 1}")
			for scan in range(self.scans):
				startIntervalTime = time.time()
				log.info(f"scan#{scan + 1}")
				log.info(f"scan points: {self.scanPoints[interval]}")
				for index, point in enumerate(self.scanPoints[interval], start=1):
					log.info(f"scan points: {point}")
				# 	for t in range(4): # Number of trials to get exactly to target position
				# 		self.epics_motors["TwoTheta"].move(point) # move 2 theta (detector arm)
				# 		time.sleep(0.5)
				# 		while not self.epics_motors["TwoTheta"].done_moving:
				# 			CLIMessage(f"2theta moving {self.epics_motors['TwoTheta'].readback}", "IO")
					CLIMessage(f"2theta moving {point} ...", "IO")
					time.sleep(1)

					elapsedIntervalTime = time.time() - startIntervalTime
					elapsedScanTime = time.time() - startScanTime
					totalIndex = totalIndex + 1
					remainingIntervalTime = elapsedIntervalTime * ((len(self.scanPoints[interval]) - index) / max(float(index), 1))
					remainingScanTime = elapsedScanTime * ((self.scans * totalPoints - totalIndex) / max(float(totalIndex), 1))
				log.info(f"expected remaining time for the scan: {str(timedelta(seconds=int(remainingScanTime)))}")

		scanEndTime = datetime.now().strftime("%d.%m.%Y %H:%M:%S")
		log.info(f"scan end time: {scanEndTime}")

		log.warning("stop spinner after the scan ...")
		self.stopSpinner()

	def preCheck(self):
		super().preCheck()

	def stopSpinner(self):

		PV(f"{spinner}.STOP").put(1)

		CLIMessage("stop spinner ...", "W")
		time.sleep(1)
		if not self.waitSpinner(1):
			CLIMessage("can't stop the spinner!!!","E")
			log.error("can't stop the spinner!!!")
			os.kill(os.getpid(), signal.SIGINT)

	def moveSpinner(self):

		PV(spinner + ".JVEL").put(200, wait=True)
		PV(spinner + ".SET").put(1, wait=True)
		PV(spinner + ".VAL").put(0, wait=True)
		PV(spinner + ".SET").put(0, wait=True)
		PV(spinner + ".JOGF").put(1)

		time.sleep(1)
		CLIMessage("move spinner ...", "W")
		if not self.waitSpinner(0):
			CLIMessage("can't move the spinner!!!","E")
			log.error("can't move the spinner!!!")
			os.kill(os.getpid(), signal.SIGINT)

	def waitSpinner(self, val, timeout = 60):
		"""
		Check the PV value is reached to the target val within predefined timeout
		"""
		startTime = time.time()
		while time.time() - startTime < timeout:
			checkVal = self.epics_motors["Spinner"].done_moving

			if checkVal == val:
				return True
			time.sleep(1)

		return False