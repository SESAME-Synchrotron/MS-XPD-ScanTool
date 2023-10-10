#!/usr/bin/python3.9

import log
import os
import time
import signal
from datetime import datetime, timedelta
from epics import PV

from step import step
from robot import robot
from SEDSS.CLIMessage import CLIMessage

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

			startTime = time.time()

			samples  = self.epics_pvs["Samples"].get(timeout=self.timeout, use_monitor=False)
			self.samplesPositions = list(self.epics_pvs["SamplesPositions"].get(timeout=self.timeout, use_monitor=False))

			CLIMessage(f"#Samples: {samples}, Samples Positions: {self.samplesPositions}", "I")
			log.info(f"#Samples: {samples}")
			log.info(f"Samples Positions: {self.samplesPositions}")

			self.samplesDone = []
			self.skippedSamples = {}
			self.skippedReturnSamples = {}

			for index, pos in enumerate(self.samplesPositions, start=1):

				log.warning("stop spinner before moving the robot ...")
				self.stopSpinner()			# stop the spinner before moving the robot

				sampleName = self.data_pvs[f"Sample{pos}"].get(timeout =self.timeout, use_monitor=False, as_string=True)
				CLIMessage(f"Start scanning sample on position: {pos}")
				CLIMessage(f"Sample Position: {pos}, Sample Name: {sampleName}", "I")

				self.useRobot.moveSampleContainer(f"Sample{pos}")
				time.sleep(2)

				val = self.useRobot.sampleInOperation()
				if val in ["notReady"]:
					os.kill(os.getpid(), signal.SIGINT)

				val, msg = self.useRobot.startExperiment()
				if val in ["Skip", "waiting"]:
					if val == "Skip":
						self.skippedSamples[pos] = sampleName
						CLIMessage(f"Process Error! {msg} the sample{pos} will be skipped", "E")
						log.error(f"The sample{pos} has been skipped. Process Error! {msg}")
					elif val == "waiting":
						os.kill(os.getpid(), signal.SIGINT)
				else:
					self.scan()
					self.samplesDone.append(pos)
					log.info(f"The scan on sample{pos} has been done successfully")

					self.useRobot.dropSampleInSc()
					val, msg = self.useRobot.finishExperiment()
					if val in ["Skip", "waiting"]:
						if val == "Skip":
							self.skippedReturnSamples[pos] = sampleName
							CLIMessage(f"Process Error (sample{pos})! {msg}", "E")
							log.error(f"Process Error (sample{pos})! {msg}")
						elif val == "waiting":
							os.kill(os.getpid(), signal.SIGINT)
						else:
							log.info(f"the sample{pos} is dropped, the scan has been finished successfully ...")

				elapsedTime = time.time() - startTime
				remainingTime = elapsedTime * ((len(self.samplesPositions) - index) / max(float(index), 1))
				log.info(f"expected remaining time for the experiment: {str(timedelta(seconds=int(remainingTime)))}")

				done = f"scan has been done for samples: {self.samplesDone}"
				skip = f"skipped samples: {self.skippedSamples}"
				notReturn = f"samples didn't return to the sample container: {self.skippedReturnSamples}"
				remaining = f"remaining samples: {len(self.samplesPositions) - len(self.samplesDone) - len(self.skippedSamples)}"

				if self.skippedSamples and self.skippedReturnSamples:
					CLIMessage(f"{done} | {skip} | {notReturn} | {remaining}", "I")
					log.info(f"{done} | {skip} | {notReturn} | {remaining}")
				elif self.skippedSamples:
					CLIMessage(f"{done} | {skip} | {remaining}", "I")
					log.info(f"{done} | {skip} | {remaining}")
				elif self.skippedReturnSamples:
					CLIMessage(f"{done} | {notReturn} | {remaining}", "I")
					log.info(f"{done} | {notReturn} | {remaining}")
				else:
					CLIMessage(f"{done} | {remaining}", "I")
					log.info(f"{done} | {remaining}")

			if self.skippedSamples and self.skippedReturnSamples:
				CLIMessage(f"The experiment has been finished \n{done} | {skip} | {notReturn}", "I")
				log.info(f"The experiment has been finished \n{done} | {skip} | {notReturn}")
			elif self.skippedSamples:
				CLIMessage(f"The experiment has been finished \n{done} | {skip}", "I")
				log.info(f"The experiment has been finished \n{done} | {skip}")
			elif self.skippedReturnSamples:
				CLIMessage(f"The experiment has been finished \n{done} | {notReturn}", "I")
				log.info(f"The experiment has been finished \n{done} | {notReturn}")
			else:
				log.info("The experiment has been finished")

		else:
			self.scan()
			log.info("The experiment has been finished successfully")

		expEndTime = datetime.now().strftime("%d.%m.%Y %H:%M:%S")
		log.info(f"experiment end time: {expEndTime}")

	def drange(self, start, stop, step, prec=10):
		return super().drange(start, stop, step, prec)

	def signal_handler(self, sig, frame):

		CLIMessage("The scan has been aborted \n"
					f"scan has been done for samples: {self.samplesDone}, {len(self.samplesDone)} out of {len(self.samplesPositions)}", "W")
		log.warning("The scan has been aborted \n"
					f"scan has been done for samples: {self.samplesDone}, {len(self.samplesDone)} out of {len(self.samplesPositions)}")

		super().signal_handler(sig, frame)
