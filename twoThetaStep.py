#!/usr/bin/python3.9

import log
import time
from step import step
from robot import robot
from SEDSS.CLIMessage import CLIMessage

X = robot()

class twoThetaStep(step):

	def __init__(self, PVsFiles, macros, scanningSubs):
		super().__init__(PVsFiles, macros, scanningSubs)
		
		if self.epics_pvs["UseRobot"].get():
			self.robot()

	def startScan(self):

		log.info("Start the scan")

		self.scanpoints = self.drange(self.data_pvs["StartPoint1"].get(),self.data_pvs["EndPoint1"].get(),self.data_pvs["StepSize1"].get())
		print(self.scanpoints)
		for index,point in enumerate(self.scanpoints,start=1):
			for t in range(4): # Number of trials to get exactly to target position
				self.epics_motors["TwoTheta"].move(point) # move 2 theta (detector arm)
				time.sleep(0.5)
				# while not self.epics_motors["TwoTheta"].done_moving:
				# 	CLIMessage(f"2theta moving {self.epics_motors['TwoTheta'].readback}", "IO")

			current2theta = self.epics_motors["TwoTheta"].readback
			currentImgName = f"{self.epics_pvs['ExperimentalFileName']}_{index}_{current2theta:.4f}.tiff"
			# self.epics_pvs["ImageName"].put(str(currentImgName)) # set Image Name
			# self.epics_pvs["isAcquiring"].put(1) # disable temp measurment
			# self.epics_pvs["Acquiring"].put(1)
			# self.epics_pvs["isAcquiring"].put(0) # re-enable temp measurment


	def startScan(self):

		CLIMessage(f"start {self.epics_pvs['ScanningType'].get(as_string=True)}", "I")
		log.info(f"start {self.epics_pvs['ScanningType'].get(as_string=True)}")

		if self.epics_pvs["UseRobot"].get():
			pass

		CLIMessage("#######################", "I")
		CLIMessage("#Experiment Parameters#", "I")
		CLIMessage("#######################", "I")
		# CLIMessage(f"2theta start angle (degree) :",self.start)
		# CLIMessage("2theta end angle (degree) :",self.end)
		# CLIMessage("2theta angle step size (degree) :",self.stepsize)
		# CLIMessage("exposure time (seconds) :",self.exptime)
		CLIMessage(f"experiment name : {self.epics_pvs['ExperimentalFileName'].get(as_string=True)}", "I")
		CLIMessage(f"experiment type (local,users) : {self.epics_pvs['ExperimentType'].get(as_string=True)}", "I")
		# CLIMessage(f"experiment proposal number : {self.epics_pvs['']}", "I")
		CLIMessage("scan will start in 3 seconds ...", "IO")
		time.sleep(3)

	def robot(self):
		CLIMessage("robot in use","E")
		X.setup()
		# X.startExperiment()

	def drange(self, start, stop, step, prec=10):
		return super().drange(start, stop, step, prec)
