#!/usr/bin/python3.9

import epics
from MS import XRD
from SEDSS.CLIMessage import CLIMessage
import log
import time

class twoThetaStep(XRD):

	def __init__(self, PVsFiles, macros):
		super().__init__(PVsFiles, macros)
	
	def startScan(self):
		
		CLIMessage("ss","e")
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

