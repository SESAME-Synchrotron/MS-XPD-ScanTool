#!/usr/bin/python3.9

import os
import log
import time
from datetime import datetime, timedelta

from step import step
from robot import robot
from emailNotifications import email
from SEDSS.CLIMessage import CLIMessage

class twoThetaStep(step):
	def __init__(self, PVsFiles, macros, scanningSubs):
		super().__init__(PVsFiles, macros, scanningSubs)

		log.info(f"start {self.epics_pvs['ScanningType'].get(timeout=self.timeout, use_monitor=False, as_string=True)}")
		self.startScan()

	def startScan(self):
		super().startScan()

		if self.robotInUse:

			# send the needed PVs to robot class
			sendToRobot = {}
			sendToRobot["testingMode"] 		   	 = self.testingMode
			sendToRobot["proposalID"] 	 	   	 = self.proposalID
			sendToRobot["experimentType"] 	   	 = self.experimentType
			sendToRobot["programmaticInterrupt"] = self.epics_pvs["ProgInt"]
			sendToRobot["SC"] 				   	 = self.epics_motors["SC"]

			self.useRobot = robot(**sendToRobot)		# create a new instance from robot class
			self.useRobot.setup()

			startTime = time.time()

			samples = self.epics_pvs["Samples"].get(timeout=self.timeout, use_monitor=False)
			self.samplesPositions = list(self.epics_pvs["SamplesPositions"].get(timeout=self.timeout, use_monitor=False))
			pickingOrder = self.epics_pvs["PickingOrder"].get(as_string=True, timeout=self.timeout, use_monitor=False)

			CLIMessage(f"#Samples: {samples}, Samples Positions: {self.samplesPositions}, Picking Order: {pickingOrder}", "I")
			log.info(f"#Samples: {samples}")
			log.info(f"Samples Positions: {self.samplesPositions}")

			self.samplesDone = []
			skippedSamples = {}
			skippedReturnSamples = {}
			sameSample = 0

			for index, pos in enumerate(self.samplesPositions, start=1):

				print("\n")

				sampleName = self.data_pvs[f"Sample{pos}"].get(timeout =self.timeout, use_monitor=False, as_string=True)
				path = f"{self.expFileName}/{self.expFileName}_{sampleName}"

				# if the sample name is duplicated, the folder name will be sample{pos}
				if sampleName.strip() == "" or os.path.exists(path):
					sampleName = f"sample{pos}"
					path = f"{self.expFileName}/{self.expFileName}_{sampleName}"

				CLIMessage(f"Start scanning sample on position: {pos}")
				CLIMessage(f"Sample Position: {pos}, Sample Name: {sampleName}", "I")

				if self.initDir(path) !=0:
					log.error(f"Data path {path} init failed!")
					skippedSamples[pos] = sampleName			# skip the sample if the path init failed

				else:
					if not sameSample:
						log.warning("stop spinner before moving the robot ...")
						self.stopSpinner()			# stop the spinner before moving the robot

						self.useRobot.readyState()

						# wait the robot to complete the transition (it will not affect the process at all, can be ignored)
						time.sleep(2)
						self.useRobot.moveSampleContainer(f"Sample{pos}")
						time.sleep(2)

						self.useRobot.sampleInOperation()

					val, msg = self.useRobot.startExperiment()
					if val == "Skip":
						skippedSamples[pos] = sampleName
						CLIMessage(f"Process Error! {msg} the sample{pos} will be skipped", "E")
						log.warning(f"The sample{pos} has been skipped. Process Error! {msg}")
					else:
						if self.pauseErr:
							self.pause()
						self.scan(path)
						self.samplesDone.append(pos)
						log.info(f"The scan on sample{pos} has been done successfully")

						""" if the sample is repeated for random order:
						- don't return is to container
						- don't move the robot at the beginning
						- just repeat the scan
						"""
						try:
							if (pickingOrder == "Random" and self.samplesPositions[index-1] == self.samplesPositions[index]):
								log.info(f"the scan on sample{pos} will be repeated, random pattern:{self.samplesPositions}")
								CLIMessage(f"the scan on sample{pos} will be repeated, random pattern:{self.samplesPositions}", "W")
								sameSample = 1
							else:
								sameSample = 0
						except:
							sameSample = 0

						if not sameSample:
							self.useRobot.dropSampleInSc()
							val, msg = self.useRobot.finishExperiment()
							if val == "Skip":
								skippedReturnSamples[pos] = sampleName
								CLIMessage(f"Process Error (sample{pos})! {msg}", "E")
								log.warning(f"Process Error (sample{pos})! {msg}")
							else:
								log.info(f"the sample{pos} has been dropped to sample container successfully")

				elapsedTime = time.time() - startTime
				remainingTime = (elapsedTime * ((len(self.samplesPositions) - index) / max(float(index), 1))) - self.pauseTime - self.useRobot.robotPauseTime
				log.info(f"expected remaining time for the experiment: {str(timedelta(seconds=int(remainingTime)))}")
				self.pauseTime = 0					# reset pausing time
				self.useRobot.robotPauseTime = 0 		# reset robot pausing time

				done = f"scan has been done for samples: {self.samplesDone}"
				skip = f"skipped samples {len(skippedSamples)}: {skippedSamples}"
				notReturn = f"samples didn't return to the sample container {len(skippedReturnSamples)}: {skippedReturnSamples}"
				remaining = f"remaining samples: {len(self.samplesPositions) - len(self.samplesDone) - len(skippedSamples)}"

				if skippedSamples and skippedReturnSamples:
					CLIMessage(f"{done} | {skip} | {notReturn} | {remaining}", "I")
					log.info(f"{done} | {skip} | {notReturn} | {remaining}")
				elif skippedSamples:
					CLIMessage(f"{done} | {skip} | {remaining}", "I")
					log.info(f"{done} | {skip} | {remaining}")
				elif skippedReturnSamples:
					CLIMessage(f"{done} | {notReturn} | {remaining}", "I")
					log.info(f"{done} | {notReturn} | {remaining}")
				else:
					CLIMessage(f"{done} | {remaining}", "I")
					log.info(f"{done} | {remaining}")

			if skippedSamples and skippedReturnSamples:
				logMsg = f"The experiment has been finished \n{done} | {skip} | {notReturn}"
			elif skippedSamples:
				logMsg = f"The experiment has been finished \n{done} | {skip}"
			elif skippedReturnSamples:
				logMsg = f"The experiment has been finished \n{done} | {notReturn}"
			else:
				logMsg = "The experiment has been finished"

			CLIMessage(logMsg, "I")
			log.info(logMsg)

			self.useRobot.stopRobot()

			if not self.testingMode:
				email(self.experimentType, self.proposalID).sendEmail(type="finishScan", msg=logMsg)
			self.finishScan()

		else:
			sampleName = self.epics_pvs["Sample"].get(as_string=True, timeout=self.timeout, use_monitor=False)
			sampleName = f"sample" if sampleName.strip() == "" else sampleName
			self.initDir(self.expFileName)
			CLIMessage(f"Start scanning sample: {sampleName}", "I")
			self.scan(self.expFileName)
			log.info("The experiment has been finished successfully")
			if not self.testingMode:
				email(self.experimentType, self.proposalID).sendEmail(type="finishScan", msg="The experiment has been finished successfully")
			self.finishScan()

		expEndTime = datetime.now().strftime("%d.%m.%Y %H:%M:%S")
		log.info(f"experiment end time: {expEndTime}")

	def signal_handler(self, sig, frame):

		self.exit = True		# force exit from the acquiring process

		# try & except to stop the robot & print the log only if the robot in use
		try:
			self.useRobot.stopRobot()

			CLIMessage("The scan has been aborted \n"
						f"scan has been done for samples: {self.samplesDone}, {len(self.samplesDone)} out of {len(self.samplesPositions)}", "W")
			log.warning("The scan has been aborted \n"
						f"scan has been done for samples: {self.samplesDone}, {len(self.samplesDone)} out of {len(self.samplesPositions)}")
		except:
			pass
		super().signal_handler(sig, frame)
