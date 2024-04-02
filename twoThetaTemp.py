#!/usr/bin/python3.9
# **: for UI Visualization tool use

import sys
import log
import math
import time
from datetime import datetime, timedelta
import threading

from step import step
from emailNotifications import email
from SEDSS.CLIMessage import CLIMessage

class twoThetaTemp(step):
	def __init__(self, PVsFiles, macros, scanningSubs):
		super().__init__(PVsFiles, macros, scanningSubs)

		log.info(f"start {self.epics_pvs['ScanningType'].get(timeout=self.timeout, use_monitor=False, as_string=True)}")
		self.startScan()

	def startScan(self):
		"""
		Start Scan:
		- initialize directory for the sample
		- call scan() method
		"""
		super().startScan()

		self.epics_pvs["StartTime"].put(datetime.now().strftime("%H:%M:%S"), wait=True)		# **

		floatingPointCompensation = 0.001
		deadband = float(self.epics_pvs["TempDeadband"].get(timeout=self.timeout, use_monitor=False)) + floatingPointCompensation
		self.__deadband = 0.1 + floatingPointCompensation if deadband == floatingPointCompensation else deadband

		sampleName = self.epics_pvs["Sample"].get(as_string=True, timeout=self.timeout, use_monitor=False)
		sampleName = "sample" if sampleName.strip() == "" else sampleName
		self.epics_pvs["CurrentSample"].put(1, wait=True)			# **
		self.epics_pvs["SampleName"].put(sampleName, wait=True)		# **

		path = f"{self.fullExpFileName}/{sampleName}_{self.creationTime}"
		self.initDir(path)

		CLIMessage(f"Start scanning sample: {sampleName}", "I")
		self.scan(path, sampleName)

		log.info("The experiment has been finished")
		self.epics_pvs["ScanStatus"].put(2, wait=True)				# **

		self.epics_pvs["TempSetPoint"].put(25, wait=True)		# set gas blower temperature to 25C

		if not self.testingMode and self.receiveNotifications:
			email(self.experimentType, self.proposalID).sendEmail(type="finishScan", msg="The experiment has been finished", DS=self.fullExpDataPath)
		self.finishScan()

		expEndTime = datetime.now().strftime("%d.%m.%Y %H:%M:%S")
		log.info(f"experiment end time: {expEndTime}")

	def temperaturePoints(self):

		intervals = self.epics_pvs["Intervals"].get(timeout=self.timeout, use_monitor=False)
		temperaturePoints = {}
		settlingTime = []
		NScans = []
		stepSize = []

		for interval in range(intervals):
			temperaturepoints = self.drange(self.data_pvs[f"TStart{interval+1}"].get(timeout=self.timeout, use_monitor=False)
							,self.data_pvs[f"TEnd{interval+1}"].get(timeout=self.timeout, use_monitor=False)
							,self.data_pvs[f"TStepSize{interval+1}"].get(timeout=self.timeout, use_monitor=False))
			temperaturePoints[interval] = temperaturepoints
			settlingTime.append(self.data_pvs[f"TSettlingTime{interval+1}"].get(timeout=self.timeout, use_monitor=False))
			NScans.append(int(self.data_pvs[f"NScans{interval+1}"].get(timeout=self.timeout, use_monitor=False)))
			stepSize.append(self.data_pvs[f"TStepSize{interval+1}"].get(timeout=self.timeout, use_monitor=False))

		return temperaturePoints, settlingTime, NScans, stepSize

	def scan(self, path, sampleName):
		"""
		Scan:
		- calculate expected theoretical remaining time:
			interval time = ((#scanIntervalPoints * stepSize) or (endPoint - startPoint) / motorSpeed)
			+ (#scanIntervalPoints * #Scans * (exposureTime + motorSettlingTime))
			+ ((#temperaturePoints * temperatureStepSize * 60) / temperatureRate) (60: convert time seconds)
			+ (#temperaturePoints * #Scans * (temperatureSettlingTime))
			+ transition time between intervals
			+ margin log base 2
		- start scanning (intervals >> temperature points >>scans >> intervals points)
		- calculate time parameters
		"""

		temperaturePoints, tempSettlingTime, NScans, tempStepSize = self.temperaturePoints()

		log.warning("move spinner before the scan ...")
		self.moveSpinner()
		time.sleep(1)

		CLIMessage(f"#Intervals: {self.intervals}", "I")
		log.info(f"#Intervals: {self.intervals}")

		scanStartTime = datetime.now().strftime("%d.%m.%Y %H:%M:%S")
		self._path = path
		self._totalCollectedPoints = 0		# **
		self._totalPoints = 0
		intervalsTime = 0		# **
		totalIndex = 0
		speed = float(self.epics_pvs["TwoThetaSpeed"].get(timeout=self.timeout, use_monitor=False))		# **
		temperatureRate = float(self.epics_pvs["TempRate"].get(timeout=self.timeout, use_monitor=False))		# **

		for interval in range(self.intervals):
			points = len(self.scanPoints[interval])
			tempPoints = len(temperaturePoints[interval])
			self._totalPoints += points * NScans[interval] * tempPoints

			transitionTime = (abs(self.data_pvs[f"EndPoint{interval+1}"].get(timeout=self.timeout, use_monitor=False) - self.data_pvs[f"StartPoint{interval+2}"].get(timeout=self.timeout, use_monitor=False)) / speed
					 + (abs(self.data_pvs[f"TEnd{interval+1}"].get(timeout=self.timeout, use_monitor=False) - self.data_pvs[f"TStart{interval+2}"].get(timeout=self.timeout, use_monitor=False)) * 60) / temperatureRate) if (interval + 1) != self.intervals else 0		# **

			intervalsTime += (points * (self.stepSize[interval] / speed + NScans[interval] * tempPoints * (self.exposureTime[interval] + self.settlingTime))
					 + tempPoints * ((tempStepSize[interval] * 60) / temperatureRate + NScans[interval] * tempSettlingTime[interval])
					 + transitionTime)

		intervalsTime += (abs(self.epics_motors["TwoTheta"].readback - self.data_pvs["StartPoint1"].get(timeout=self.timeout, use_monitor=False)) / speed
					+ (abs(float(self.epics_pvs["TempReadback"].get(timeout=self.timeout, use_monitor=False)) - self.data_pvs["TStart1"].get(timeout=self.timeout, use_monitor=False)) * 60) / temperatureRate)
		intervalsTime += math.log(intervalsTime, 2)
		threading.Thread(target=self.expectedRemainingTime, args=(intervalsTime,), daemon=True).start()		# **

		log.info(f"scan start time: {scanStartTime}")

		for interval in range(self.intervals):
			self._interval = interval
			print("\n")
			log.info(f"Interval#{interval + 1}, Exposure Time: {self.exposureTime[interval]}")
			self.epics_pvs["CurrentInterval"].put(interval+1, wait=True)		# **

			for temperature in temperaturePoints[interval]:
				log.info(f"temperature point: {temperature}")
				self.epics_pvs["TempSetPoint"].put(temperature, wait=True)

				while math.fabs(float(self.epics_pvs["TempReadback"].get(timeout=self.timeout, use_monitor=False)) - temperature) >= self.__deadband:
					CLIMessage(f"sample temperature {self.epics_pvs['TempReadback'].get(timeout=self.timeout, use_monitor=False):.2f} ", "IO")
					time.sleep(0.01)

				log.warning(f"waiting {tempSettlingTime[interval]} seconds after sample reached target temperature")
				time.sleep(tempSettlingTime[interval])

				self.scans = NScans[interval]
				log.info(f"#Scans: {self.scans}")

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
						imageName = f"{sampleName}_{interval + 1}_{index}_{twoTheta:.4f}_{temperature}_{scan + 1}.tiff"
						self.acquire(imageName)

						elapsedIntervalTime = time.time() - startIntervalTime
						totalIndex = totalIndex + 1
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

	def signal_handler(self, sig, frame):

		if not self.lock:
			self.lock = True
			self.exit = True		# force exit from the acquiring process
			self.epics_pvs["TempSetPoint"].put(25, wait=True)		# set gas blower temperature to 25C
			super().signal_handler(sig, frame)
