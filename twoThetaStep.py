#!/usr/bin/python3.9

import log
import time
from step import step
from robot import robot
from SEDSS.CLIMessage import CLIMessage

class twoThetaStep(step):

	def __init__(self, PVsFiles, macros, scanningSubs):
		super().__init__(PVsFiles, macros, scanningSubs)

		self.startScan()
		
	def startScan(self):

		CLIMessage(f"start {self.epics_pvs['ScanningType'].get(timeout = self.timeout, as_string=True)}", "I")
		log.info(f"start {self.epics_pvs['ScanningType'].get(timeout = self.timeout, as_string=True)}")

		log.info("Start the scan")

		intervals = self.epics_pvs["Intervals"].get(timeout = self.timeout)
		scans 	  = self.epics_pvs["Scans"].get(timeout = self.timeout)
		samples	  = self.epics_pvs["Samples"].get(timeout = self.timeout)
		CLIMessage(f"#Samples: {samples}, #Intervals: {intervals}, #Scans: {scans}", "I")

		if self.epics_pvs["UseRobot"].get():

			CLIMessage("robot in use","E")
			self.useRobot = robot()
			# self.useRobot.setup()

			samplesPositions = list(self.epics_pvs["SamplesPositions"].get(timeout = self.timeout))
			for sample in samplesPositions:
				sampleName =self.data_pvs[f'Sample{sample}'].get(timeout = self.timeout, as_string=True)
				CLIMessage(f"sample position, name: {sample}, {sampleName}", "I")
				CLIMessage(f"move robot to position {sample}", "E")
				self.useRobot.startExperiment(sample)
				time.sleep(5)
				for interval in range(intervals):
					for scan in range(scans):
						self.scanpoints = self.drange(self.data_pvs[f"StartPoint{interval+1}"].get(timeout = self.timeout)
										,self.data_pvs[f"EndPoint{interval+1}"].get(timeout = self.timeout)
										,self.data_pvs[f"StepSize{interval+1}"].get(timeout = self.timeout))
						CLIMessage(f"scan points: {self.scanpoints}", "I")
						CLIMessage(f">>> sample: {samples}, interval: {interval + 1}, scan: {scan + 1} <<<", "I")
						for index,point in enumerate(self.scanpoints,start=1):
							CLIMessage(f"scan points: {point}", "W")
						# 	for t in range(4): # Number of trials to get exactly to target position
						# 		self.epics_motors["TwoTheta"].move(point) # move 2 theta (detector arm)
						# 		time.sleep(0.5)
						# 		while not self.epics_motors["TwoTheta"].done_moving:
						# 			CLIMessage(f"2theta moving {self.epics_motors['TwoTheta'].readback}", "IO")
							CLIMessage(f"2theta moving {point} ...", "IO")
							time.sleep(1)
				self.useRobot.finishExperiment()
		else:
			for interval in range(intervals):
				for scan in range(scans):
					self.scanpoints = self.drange(self.data_pvs[f"StartPoint{interval+1}"].get(timeout = self.timeout)
									,self.data_pvs[f"EndPoint{interval+1}"].get(timeout = self.timeout)
									,self.data_pvs[f"StepSize{interval+1}"].get(timeout = self.timeout))
					CLIMessage(f"scan points: {self.scanpoints}", "I")
					CLIMessage(f">>> sample: {samples}, interval: {interval + 1}, scan: {scan + 1} <<<", "I")
					for index,point in enumerate(self.scanpoints,start=1):
						CLIMessage(f"scan points: {point}", "W")
					# 	for t in range(4): # Number of trials to get exactly to target position
					# 		self.epics_motors["TwoTheta"].move(point) # move 2 theta (detector arm)
					# 		time.sleep(0.5)
					# 		while not self.epics_motors["TwoTheta"].done_moving:
					# 			CLIMessage(f"2theta moving {self.epics_motors['TwoTheta'].readback}", "IO")
						CLIMessage(f"2theta moving {point} ...", "IO")
						time.sleep(1)

					# 	current2theta = self.epics_motors["TwoTheta"].readback
					# 	currentImgName = f"{self.epics_pvs['ExperimentalFileName']}_{index}_{current2theta:.4f}.tiff"
					# 	self.epics_pvs["ImageName"].put(str(currentImgName)) # set Image Name
					# 	self.epics_pvs["isAcquiring"].put(1) # disable temp measurment
					# 	self.epics_pvs["Acquiring"].put(1)
					# 	self.epics_pvs["isAcquiring"].put(0) # re-enable temp measurment

					# for i in range(int(self.exptime*10+1)):
					# 	print("acquiring {}: ".format(currentImgName)+"*"*i)
					# 	time.sleep(0.1)

	def drange(self, start, stop, step, prec=10):
		return super().drange(start, stop, step, prec)
