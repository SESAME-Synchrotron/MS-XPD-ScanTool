#!/usr/bin/python3.9

import log
import time
from datetime import datetime, timedelta
from epics import PV

from MS import XPD
from SEDSS.CLIMessage import CLIMessage

spineer = "I09R2-MO-MC1:ES-DIFF-STP-ROTX3"

class step(XPD):
	def __init__(self, PVsFiles, macros, scanningSubs):
		super().__init__(PVsFiles, macros, scanningSubs)

		# self.preCheck()
		# self.initDir()
		# self.detectorInit()

		self.intervals, self.scans, self.scanPoints = self.calcScanPoints()

	def scan(self):

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

	def preCheck(self):
		super().preCheck()

	def moveSpinner(self):

		log.warning("stop spinner ...")
		PV(spineer + ".JVEL").put(200, wait=True)
		PV(spineer + ".SET").put(1, wait=True)
		PV(spineer + ".VAL").put(0, wait=True)
		PV(spineer + ".SET").put(0, wait=True)
		PV(spineer + ".JOGF").put(1, wait=True)
