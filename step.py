import log
import time
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

	def scan(self):

		intervals = self.epics_pvs["Intervals"].get(timeout=self.timeout, use_monitor=False)
		scans 	  = self.epics_pvs["Scans"].get(timeout=self.timeout, use_monitor=False)
		samples	  = self.epics_pvs["Samples"].get(timeout=self.timeout, use_monitor=False)

		CLIMessage(f"#Samples: {samples}, #Intervals: {intervals}, #Scans: {scans}", "I")
		log.info(f"#Samples: {samples}, #Intervals: {intervals}, #Scans: {scans}")

		for interval in range(intervals):
			log.info(f"Interval#{interval + 1}")
			for scan in range(scans):
				log.info(f"scan#{scan + 1}")
				self.scanpoints = self.drange(self.data_pvs[f"StartPoint{interval+1}"].get(timeout=self.timeout, use_monitor=False)
								,self.data_pvs[f"EndPoint{interval+1}"].get(timeout=self.timeout, use_monitor=False)
								,self.data_pvs[f"StepSize{interval+1}"].get(timeout=self.timeout, use_monitor=False))
				log.info(f"scan points: {self.scanpoints}")
				for index,point in enumerate(self.scanpoints,start=1):
					log.info(f"scan points: {point}")
				# 	for t in range(4): # Number of trials to get exactly to target position
				# 		self.epics_motors["TwoTheta"].move(point) # move 2 theta (detector arm)
				# 		time.sleep(0.5)
				# 		while not self.epics_motors["TwoTheta"].done_moving:
				# 			CLIMessage(f"2theta moving {self.epics_motors['TwoTheta'].readback}", "IO")
					CLIMessage(f"2theta moving {point} ...", "IO")
					time.sleep(1)

	def preCheck(self):
		super().preCheck()

	def moveSpinner(self):

		log.warning("stop spinner ...")
		PV(spineer + ".JVEL").put(200, wait=True)
		PV(spineer + ".SET").put(1, wait=True)
		PV(spineer + ".VAL").put(0, wait=True)
		PV(spineer + ".SET").put(0, wait=True)
		PV(spineer + ".JOGF").put(1, wait=True)
