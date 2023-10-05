#!/usr/bin/python3.9

import log
import time
import threading
import _thread
from epics import PV

from step import step
from robot import robot
from SEDSS.CLIMessage import CLIMessage

spinner = PV("I09R2-MO-MC1:ES-DIFF-STP-ROTX3.STOP")

class twoThetaStep(step):
	def __init__(self, PVsFiles, macros, scanningSubs):
		super().__init__(PVsFiles, macros, scanningSubs)

		log.info(f"start {self.epics_pvs['ScanningType'].get(timeout=self.timeout, use_monitor=False, as_string=True)}")
		self.startScan()

	def startScan(self):

		log.info("Start the scan")

		if self.epics_pvs["UseRobot"].get():

			self.useRobot = robot()				# create a new instance from robot class
			self.useRobot.setup()
			self.stopProcErrFlag = False		# flag to stop the main thread if process error happened (see procErr())

			# start monitoring the process error (Wait For Human Action)
			procErr = threading.Thread(target=self.procErr, args=(), daemon=True)
			procErr.start()

			self.samplesPositions = list(self.epics_pvs["SamplesPositions"].get(timeout=self.timeout, use_monitor=False))
			log.info(f"Samples Positions: {self.samplesPositions}")

			self.samplesDone = []
			self.skippedSamples = {}
			self.skippedReturnSamples = {}

			for pos in self.samplesPositions:

				spinner.put(1, wait=True)			# stop the spinner before moving the robot

				sampleName = self.data_pvs[f"Sample{pos}"].get(timeout =self.timeout, use_monitor=False, as_string=True)
				CLIMessage(f"Start scanning sample on position: {pos}")
				CLIMessage(f"Sample Position: {pos}, Sample Name: {sampleName}", "I")

				self.useRobot.moveSampleContainer(f"Sample{pos}")
				time.sleep(2)

				val, msg = self.useRobot.startExperiment()
				if val in [1, "Skip", "timeout"]:
					if val == "Skip":
						self.skippedSamples[pos] = sampleName
						CLIMessage(f"Process Error! {msg} the sample{pos} will be skipped", "E")
						log.error(f"The sample{pos} has been skipped. Process Error! {msg}")
					elif val == 1:
						self.checkPause()
					elif val == "timeout":
						pass 		## if x == timeout >> spinner moving
						# spinner.put(1, wait=True)
				else:
					self.moveSpinner()
					time.sleep(2)
					if self.epics_motors["Spinner"].done_moving == 1:
						CLIMessage("spinner not moving!!", "E")		### exit???
					self.scan()
					val, msg = self.useRobot.finishExperiment()
					if val in [1, "Skip", "timeout"]:
						if val == "Skip":
							self.skippedReturnSamples[pos] = sampleName
							self.samplesDone.append(pos)
							CLIMessage(f"Process Error (sample{pos})! {msg}", "E")
							log.error(f"Process Error (sample{pos})! {msg}")
						elif val == 1:
							self.checkPause()
							self.samplesDone.append(pos)
						elif val == "timeout":
							pass 		## if x == timeout >> spinner moving
							spinner.put(1, wait=True)
					else:
						self.samplesDone.append(pos)
						log.info(f"The scan on sample{pos} has been done successfully")

				CLIMessage(f"scan has been done for samples: {self.samplesDone} | "
							f"skipped samples: {'No skipped samples' if not self.skippedSamples else self.skippedSamples} | "
							f"samples didn't return to the sample container: {'None' if not self.skippedReturnSamples else self.skippedReturnSamples} | "
							f"remaining samples: {len(self.samplesPositions) - len(self.samplesDone) - len(self.skippedSamples)}", "I")
				log.info(f"scan has been done for samples: {self.samplesDone} | "
							f"skipped samples: {'No skipped samples' if not self.skippedSamples else self.skippedSamples} | "
							f"samples didn't return to the sample container: {'None' if not self.skippedReturnSamples else self.skippedReturnSamples} | "
							f"remaining samples: {len(self.samplesPositions) - len(self.samplesDone) - len(self.skippedSamples)}")

			CLIMessage("The experiment has been finished \n"
						f"scan has been done for samples: {self.samplesDone} | "
						f"skipped samples: {'No skipped samples' if not self.skippedSamples else self.skippedSamples} | "
						f"samples didn't return to the sample container: {'None' if not self.skippedReturnSamples else self.skippedReturnSamples}", "I")
			log.info("The experiment has been finished \n"
						f"scan has been done for samples: {self.samplesDone} | "
						f"skipped samples: {'No skipped samples' if not self.skippedSamples else self.skippedSamples} | "
						f"samples didn't return to the sample container: {'None' if not self.skippedReturnSamples else self.skippedReturnSamples}")
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

	def checkPause(self):

		val, msg = self.useRobot.ctrlErrVal()
		if val:
			startTime = time.time()
			log.warning(f"Scan is paused, {msg}")
			while val:
				difftime = time.time() - startTime
				CLIMessage(f"Scan is paused, {msg}, the scan will be resumed automatically | pausing time {difftime}", "IO")
				val, msg = self.useRobot.ctrlErrVal()
				time.sleep(0.05)
			log.warning(f"Pausing time: {difftime}")

	def procErr(self):

		while not self.stopProcErrFlag:
			val, msg, type = self.useRobot.procErrVal()
			if val and type == "Wait For Human Action":
				log.error(f"Process Error!, {msg}")
				CLIMessage(f"Process Error!, {msg}", "IR")
				_thread.interrupt_main()			# exit from main thread (KeyInterrupt)
			time.sleep(0.1)

	def signal_handler(self, sig, frame):

		self.stopProcErrFlag = True  		# stop checking the procErr loop

		CLIMessage("The scan has been aborted \n"
					f"scan has been done for samples: {self.samplesDone}, {len(self.samplesDone)} out of {len(self.samplesPositions)}", "W")
		log.warning("The scan has been aborted \n"
					f"scan has been done for samples: {self.samplesDone}, {len(self.samplesDone)} out of {len(self.samplesPositions)}")

		super().signal_handler(sig, frame)
