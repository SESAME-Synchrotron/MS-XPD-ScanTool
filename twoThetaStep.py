#!/usr/bin/python3.9

import log
import time
from MS import XRD
from SEDSS.CLIMessage import CLIMessage
MS = __import__('2theta-step')
class twoThetaStep(XRD):

	def __init__(self, PVsFiles, macros, scanningSubs):
		super().__init__(PVsFiles, macros, scanningSubs)
		MS.XRD(self.data_pvs['StartPoint1'].get(as_string=True), self.data_pvs['EndPoint1'].get(as_string=True), self.data_pvs['StepSize1'].get(as_string=True), self.data_pvs['ExposureTime1'].get(as_string=True), self.epics_pvs['ExperimentalFileName'].get(as_string=True))
	
	def startScan(self):
		
		CLIMessage(f"start {self.epics_pvs['ScanningType'].get(as_string=True)}", "I")
		log.info(f"start {self.epics_pvs['ScanningType'].get(as_string=True)}")

		if self.epics_pvs["UseRobot"].get():
			self.robot()
		
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

		super().startScan()

	def robot(self):
		CLIMessage("robot in use","E")

	def drange(self, start, stop, step, prec=10):
		return super().drange(start, stop, step, prec)
