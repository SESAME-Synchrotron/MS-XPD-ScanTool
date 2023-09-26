#!/usr/bin/python3.9

import log
import time
from step import step
from robot import robot
from SEDSS.CLIMessage import CLIMessage
from epics import PV

spinner = PV("I09R2-MO-MC1:ES-DIFF-STP-ROTX3.STOP")
class twoThetaStep(step):

	def __init__(self, PVsFiles, macros, scanningSubs):
		super().__init__(PVsFiles, macros, scanningSubs)

		log.info(f"start {self.epics_pvs['ScanningType'].get(timeout=self.timeout, use_monitor=False, as_string=True)}")

		self.startScan()

	def startScan(self):

		log.info("Start the scan")

		if self.epics_pvs["UseRobot"].get():

			useRobot = robot()
			# useRobot.setup()

			samplesPositions = list(self.epics_pvs["SamplesPositions"].get(timeout=self.timeout, use_monitor=False))
			log.info(f"Samples Positions: {samplesPositions}")

			for pos in samplesPositions:

				spinner.put(1, wait=True)

				sampleName = self.data_pvs[f"Sample{pos}"].get(timeout =self.timeout, use_monitor=False, as_string=True)
				CLIMessage(f"Start scanning sample on position: {pos}")
				CLIMessage(f"Sample Position: {pos}, Sample Name: {sampleName}", "I")

				val, msg = useRobot.checkStatus()
				if not val:
					log.warning(f"Scan is paused, {msg}")
				while not val:
					CLIMessage(f"Scan is paused, {msg}", "IO")
					val, msg = useRobot.checkStatus()
					time.sleep(0.01)

				useRobot.moveSampleContainer(f"Sample{pos}")
				time.sleep(2)
				useRobot.startExperiment()
				# self.moveSpinner()
				# time.sleep(4)
				# if self.epics_motors["Spinner"].done_moving == 1:
				# 	CLIMessage("spinner not moving!!", "E")		### exit???
				self.scan()
				useRobot.finishExperiment()
				log.info(f"The scan on sample{pos} has been done successfully")
		else:
			self.scan()
			# 	current2theta = self.epics_motors["TwoTheta"].readback
			# 	currentImgName = f"{self.epics_pvs['ExperimentalFileName']}_{index}_{current2theta:.4f}.tiff"
			# 	self.epics_pvs["ImageName"].put(str(currentImgName)) # set Image Name
			# 	self.epics_pvs["isAcquiring"].put(1) # disable temp measurment
			# 	self.epics_pvs["Acquiring"].put(1)
			# 	self.epics_pvs["isAcquiring"].put(0) # re-enable temp measurment

			# for i in range(int(self.exptime*10+1)):
			# 	print("acquiring {}: ".format(currentImgName)+"*"*i)
			# 	time.sleep(0.1)
		log.info("The experiment has been finished successfully")

	def drange(self, start, stop, step, prec=10):
		return super().drange(start, stop, step, prec)
