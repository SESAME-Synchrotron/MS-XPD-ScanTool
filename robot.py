#!/usr/bin/python3.9
# **: for UI Visualization tool use

import os
import sys
import time
import log
import signal
import threading
import _thread
from epics import PV

from SEDSS.CLIMessage import CLIMessage
from SEDSS.SEDFileManager import readFile
from emailNotifications import email

robotPVsFile = "configurations/robot.json"
sampleContainer = "configurations/sampleContainer.json"

def checkErrors(func):
	def wrapper(self, *args, **kwargs):
		if self.ctrlErr:
			self.ctrlErrPause()
		result = func(self, *args, **kwargs)
		if self.ctrlErr:
			self.ctrlErrPause()
		return result
	return wrapper

class robot:
	def __init__(self, **kwargs):

		log.warning("robot in use")

		items = kwargs
		robotPVs = readFile(robotPVsFile).readJSON()
		self.SC = readFile(sampleContainer).readJSON()

		self.timeout = 1
		self.testingMode = items["testingMode"]
		self.experimentType = items["experimentType"]
		self.expDataPath = items["expDataPath"]
		self.proposalID = None if self.experimentType != "Users" else items["proposalID"]
		self.programmaticInterrupt = items["programmaticInterrupt"]
		self.SCMotor = items["SC"]
		self.scanStatus = items["scanStatus"]

		self.robotPVs = {}
		self.robotPVsName = {}
		allPVsConnected = True
		for category, subdata in robotPVs.items():
			self.robotPVs[category] = {}
			self.robotPVsName[category] = {}
			if isinstance(subdata, dict):
				for key, value in subdata.items():
					if PV(value).get(timeout=self.timeout, use_monitor=False) is None:
						CLIMessage(f"PV {value} is not connected", "E")
						log.error(f"PV {value} is not connected")
						allPVsConnected = False
					else:
						self.robotPVs[category][key] = PV(value)
						self.robotPVsName[category][key] = value
						CLIMessage(f"PV {value} is connected", "I")

		if not allPVsConnected:
			CLIMessage("Robot PVs not connected, the program won't continue", "E")
			log.error("Robot PVs not connected, the program won't continue")
			self.scanStatus.put(5, wait=True)		# **
			if not self.testingMode:
				email(self.experimentType, self.proposalID).sendEmail("robotPVs")
			sys.exit()

		self.__init()

	def __init(self):

		# Prepare the PVs to be added to callback, with their attr.

		self.ctrlErr = False
		self.ctrlMsg = ""
		self.robotPauseTime = 0
		self.__procErr = False
		self.__procType = ""
		self.__val1 = False		# flag for program run
		self.__val2 = False		# flag for automatic mode
		self.__val3 = False		# flag for servo on
		self.__val4 = False		# flag for operation enabled
		self.__val5 = False		# flag for controller errors

		errCallbackPVs = [
			self.robotPVs["programPVs"]["Status"],
			self.robotPVs["statePVs"]["Mode"],
			self.robotPVs["servoPVs"]["Status"],
			self.robotPVs["operationPVs"]["Status"],
			self.robotPVs["controllerErrorPVs"]["errorNumber"],
			self.robotPVs["processErrorPVs"]["errorType"],
		]

		log.info("Start Monitoring Controller Errors")
		log.info("Start Monitoring Process Errors")

		for pv in errCallbackPVs:
			pv.add_callback(self.pv_callback)

		procErrExit = threading.Thread(target=self.__procErrExit, args=(), daemon=True)
		procErrExit.start()

	def waitPVVal(self, PV, val, timeout = 5):
		"""
		Check the PV value is reached to the target val within predefined timeout
		"""
		startTime = time.time()
		while time.time() - startTime < timeout:
			checkVal = PV.get(as_string=True, timeout=self.timeout, use_monitor=False)

			if checkVal == val:
				return True

			mins, secs = divmod(int(timeout - (time.time() - startTime)), 60)
			timeformat = f"{mins:02d}:{secs:02d}"
			CLIMessage(f"waiting ... {timeformat}", "IO")
			time.sleep(1)

		CLIMessage(f"Timeout reached {timeout} sec. Value ({val}) of {PV} ({checkVal}) not reached.", "E")
		log.error(f"Timeout reached {timeout} sec. Value ({val}) of {PV} ({checkVal}) not reached.")
		return False

	def setup(self):
		"""
		Setup the robot:
		- homing sample container
		- check the errors (controller/process)
		- reset the process error notification to No
		- disable the sample (stage/container) sensors (temporary until installing the sensors)
		- check if sample is crucial (this should come from SUP)
		- enable operation
		- servo on
		- automatic mode
		- run the program
		- homing robot
		- check if the robot in homing position (Ready State)
		- send emails notifications for each failed case
		"""

		log.info("move sample container to home position")
		self.SCMotor.move(0, wait=True)
		time.sleep(0.3)
		while not self.SCMotor.done_moving:
			CLIMessage(f"sample container moving: {self.SCMotor.readback}", "IO")
			time.sleep(0.05)

		if self.robotPVs["controllerErrorPVs"]["errorNumber"].get(timeout=self.timeout, use_monitor=False) != 0 or self.robotPVs["processErrorPVs"]["errorType"].get(as_string=True, timeout=self.timeout, use_monitor=False) != "No Error":
			CLIMessage("The program won't continue!!! please check the (controller/process) errors, and try again.", "E")
			log.error("The program won't continue!!! please check the (controller/process) errors, and try again.")
			self.scanStatus.put(5, wait=True)		# **
			if not self.testingMode:
				email(self.experimentType, self.proposalID).sendEmail("robotErrors")
			sys.exit()

		self.robotPVs["processErrorPVs"]["errorNotified"].put("No", wait=True)

		log.info("Set Sample Container to 0 ...")
		self.robotPVs["environmentPVs"]["sampleContainer"].put(0, wait=True)

		log.info("Set Sample Stage to 0 ...")
		self.robotPVs["environmentPVs"]["sampleStage"].put(0, wait=True)

		log.info("Set Gripper Status to 1 ...")
		self.robotPVs["environmentPVs"]["gripperStatus"].put(1, wait=True)

		# log.warning(f"Crucial Experiment? {}")
		# self.robotPVs["environmentPVs"]["crucialExperiment"].put(1, wait=True)

		log.info("Enable operation ...")
		self.robotPVs["operationPVs"]["Enable"].put(1, wait=True)

		if self.waitPVVal(self.robotPVs["operationPVs"]["Status"], "Enabled", 30):
			log.info("Servo On ...")
			self.robotPVs["servoPVs"]["On"].put(1, wait=True)
		else:
			log.error("Can't Enable the Robot!")
			self.scanStatus.put(5, wait=True)		# **
			if not self.testingMode:
				email(self.experimentType, self.proposalID).sendEmail(type="robotEnable", PV=self.robotPVs["operationPVs"]["Status"])
			sys.exit()

		if self.waitPVVal(self.robotPVs["servoPVs"]["Status"], "Servo On", 30):
			log.info("Set Automatic Mode ...")
			self.robotPVs["statePVs"]["Mode"].put(0, wait=True)
		else:
			log.error("Can't Enable the Servo!")
			self.scanStatus.put(5, wait=True)		# **
			if not self.testingMode:
				email(self.experimentType, self.proposalID).sendEmail(type="robotServo", PV=self.robotPVs["servoPVs"]["Status"])
			sys.exit()

		if self.waitPVVal(self.robotPVs["statePVs"]["operationMode"], "Automatic", 30):
			log.info("Run the Program ...")
			self.robotPVs["programPVs"]["Run"].put(1, wait=True)
		else:
			log.error("Can't Set Automatic Mode!")
			self.scanStatus.put(5, wait=True)		# **
			if not self.testingMode:
				email(self.experimentType, self.proposalID).sendEmail(type="robotMode", PV=self.robotPVs["statePVs"]["operationMode"])
			sys.exit()

		if not self.waitPVVal(self.robotPVs["programPVs"]["Status"], "RUN", 30):
			log.error("Can't Run the Program!")
			self.scanStatus.put(5, wait=True)		# **
			if not self.testingMode:
				email(self.experimentType, self.proposalID).sendEmail(type="robotProgram", PV=self.robotPVs["programPVs"]["Status"])
			sys.exit()

		log.info("move robot to home position ...")
		CLIMessage("move robot to home position ...", "W")
			### to add homing procedure from Amro ###

		if not self.waitPVVal(self.robotPVs["statePVs"]["currentState"], "Ready", 120):
			CLIMessage("The program won't continue!!! the robot isn't in Home Position (Ready State).", "W")
			log.warning("The program won't continue!!! the robot isn't in Home Position (Ready State).")
			self.scanStatus.put(5, wait=True)		# **
			if not self.testingMode:
				email(self.experimentType, self.proposalID).sendEmail(type="robotHoming", PV=self.robotPVs["statePVs"]["currentState"])
			sys.exit()

	@checkErrors
	def readyState(self):
		"""
		Ready state:
		- check if the robot in home position within max timeout
		- check the environment errors (wrapper)
		- send email notification the case failed
		"""

		CLIMessage("robot in Ready State ...", "W")
		if not self.waitPVVal(self.robotPVs["statePVs"]["currentState"], "Ready", 300):
			msg = "The program won't continue!!! the robot isn't in Home Position (Ready State)"
			CLIMessage(msg, "E")
			log.warning(msg)
			self.scanStatus.put(5, wait=True)		# **
			self.programmaticInterrupt.put(1, wait=True)		# define the interrupt as programmatic interrupt
			if not self.testingMode:
				email(self.experimentType, self.proposalID).sendEmail(type="readyState", PV=self.robotPVs["statePVs"]["currentState"], DS=self.expDataPath)
			os.kill(os.getpid(), signal.SIGINT)			# emit interrupt signal max timeout has been reached

	@checkErrors
	def sampleInOperation(self):
		"""
		Sample in operation:
		- confirm that the sample is in the right position
		- check the environment errors (wrapper)
		"""

		log.warning("sample in operation, the robot is ready to pickup the sample ...")
		self.robotPVs["environmentPVs"]["sampleInOperation"].put(1, wait=True)

	@checkErrors
	def startExperiment(self, count=0):
		"""
		Start experiment:
		- waiting for scan to be done (in order to start scan)
		- check the environment (errors)
		- do the check two times if not (wait for scan done) from the 1st trial (recursion)
		- send email notification the case failed
		"""

		msg = "Max time of (wait for scan done reached 90 sec)"

		if count >= 2:
			CLIMessage(msg, "E")
			log.error(msg)
			self.scanStatus.put(5, wait=True)		# **
			self.programmaticInterrupt.put(1, wait=True)		# define the interrupt as programmatic interrupt
			if not self.testingMode:
				email(self.experimentType, self.proposalID).sendEmail(type="waitScanDone", PV=self.robotPVs["statePVs"]["currentState"], DS=self.expDataPath)
			os.kill(os.getpid(), signal.SIGINT)			# emit interrupt signal max timeout has been reached

		CLIMessage("waiting for scan done ...", "W")
		if not self.waitPVVal(self.robotPVs["statePVs"]["currentState"], "Wait For Scan Done", 90):
			log.warning(msg)

			if self.__procErr and self.__procType == "Skip":
				procMsg = self.robotPVs["processErrorPVs"]["errorMessage"].get(as_string=True, timeout=self.timeout, use_monitor=False)
				self.robotPVs["processErrorPVs"]["errorNotified"].put("Confirmed", wait=True)
				return self.__procType, procMsg

			return self.startExperiment(count + 1)

		return 1, "pass"

	@checkErrors
	def dropSampleInSc(self):
		"""
		Drop sample in SC:
		- confirm that the scan is done
		"""

		log.warning("scan has been done, the robot is ready to return the sample to sample container ...")
		self.robotPVs["environmentPVs"]["scanStatus"].put(0, wait=True)

	@checkErrors
	def finishExperiment(self, count=0):
		"""
		Finish experiment:
		- check the environment (errors)
		- do the check two times if not (waiting for ready state reached 90 sec) from the 1st trial (recursion)
		- send email notification the case failed
		"""

		msg = "Max time of (waiting for ready state reached 90 sec)"

		if count >= 2:
			CLIMessage(msg, "E")
			log.error(msg)
			self.scanStatus.put(5, wait=True)		# **
			self.programmaticInterrupt.put(1, wait=True)		# define the interrupt as programmatic interrupt
			if not self.testingMode:
				email(self.experimentType, self.proposalID).sendEmail(type="waitDropSample", PV=self.robotPVs["statePVs"]["currentState"], DS=self.expDataPath)
			os.kill(os.getpid(), signal.SIGINT)			# emit interrupt signal max timeout has been reached

		CLIMessage("waiting for drop the sample to sample container ...", "W")
		if not self.waitPVVal(self.robotPVs["statePVs"]["currentState"], "Ready", 90):
			log.warning(msg)

			if self.__procErr and self.__procType == "Skip":
				procMsg = self.robotPVs["processErrorPVs"]["errorMessage"].get(as_string=True, timeout=self.timeout, use_monitor=False)
				self.robotPVs["processErrorPVs"]["errorNotified"].put("Confirmed", wait=True)
				return self.__procType, procMsg

			return self.finishExperiment(count + 1)

		return 1, "pass"

	def moveSampleContainer(self, position):

		# Move sample container to the target position

		log.info(f"move sample container to position {position}")
		self.SCMotor.move(self.SC[position], wait=True)
		time.sleep(0.3)
		while not self.SCMotor.done_moving:
			CLIMessage(f"sample container moving: {self.SCMotor.readback}", "IO")
			time.sleep(0.05)

	def stopRobot(self):
		"""
		Stop robot:
		- stop the program
		- servo off
		- disable operation
		"""

		CLIMessage("Stop Robot ...", "W")
		log.warning("stop robot program")
		self.robotPVs["programPVs"]["Stop"].put(1, wait=True)

		log.warning("robot servo off")
		self.robotPVs["servoPVs"]["Off"].put(1, wait=True)

		log.warning("disable robot operation")
		self.robotPVs["operationPVs"]["Disable"].put(1, wait=True)

	def ctrlErrPause(self):
		"""
		Control error pause:
		- pause the program for any controller error
		- send emails notifications for (pause/resume)
		"""

		if self.__val5:			# get the pv message out of the pv_callback thread
			self.ctrlMsg = self.robotPVs["controllerErrorPVs"]["errorMessage"].get(as_string=True, timeout=self.timeout, use_monitor=False)
		self.scanStatus.put(3, wait=True)		# **

		startTime = time.time()
		log.warning(f"Scan is paused, {self.ctrlMsg}")

		if not self.testingMode:
			email(self.experimentType, self.proposalID).sendEmail(type="ctrlErr", msg=self.ctrlMsg)

		while self.ctrlErr:
			diffTime = time.time() - startTime
			mm, ss = divmod((int(diffTime)), 60)
			hh, mm = divmod(mm, 60)
			timeformat = f"{hh:02d}:{mm:02d}:{ss:02d}"
			CLIMessage(f"Scan is paused, {self.ctrlMsg}, the scan will be resumed automatically | pausing time hh:mm:ss {timeformat}", "IO")
			time.sleep(0.05)
		log.warning(f"Pausing time (hh:mm:ss): {timeformat}")

		self.scanStatus.put(1, wait=True)		# **
		if not self.testingMode:
			email(self.experimentType, self.proposalID).sendEmail(type="robotResumed", msg=f"pausing time (hh:mm:ss) was: {timeformat}")

		self.robotPauseTime = diffTime

	def __procErrExit(self):
		"""
		Process error exit:
		- Exit from the program immediately if the process error "Wait For Human Action
		- send email notification
		"""

		check = 1
		procMsg = self.robotPVs["processErrorPVs"]["errorMessage"].get(as_string=True, timeout=self.timeout, use_monitor=False)
		while check:
			if self.__procErr and self.__procType == "Wait For Human Action":
				self.scanStatus.put(5, wait=True)		# **
				self.programmaticInterrupt.put(1, wait=True)		# define the interrupt as programmatic interrupt
				if not self.testingMode:
					email(self.experimentType, self.proposalID).sendEmail(type="procErr", msg=procMsg, DS=self.expDataPath)
				CLIMessage(f"Process Error!, {procMsg}", "E")
				log.error(f"Process Error!, {procMsg}")
				check = 0
				_thread.interrupt_main()			# exit from main thread (KeyInterrupt)
			time.sleep(0.1)

	def pv_callback(self, pvname=None, value=None, char_value=None, **kw):
		"""
		Callback function that is called by pyEpics when certain EPICS PVs are changed

		The PVs that are handled are:
		- Program is Run
		- Automatic Mode
		- Servo is On
		- Operation is Enabled
		- Controller Errors
		- Process Errors
		"""
		log.debug(f"pv_callback pvName={pvname}, value={value}, char_value={char_value}")

		if (pvname.find(self.robotPVsName["programPVs"]["Status"]) != -1):
			if (char_value ==  "STOP"):
				self.__val1 = True
				self.ctrlMsg = "the program is stopped!"
			else:
				self.__val1 = False

		elif (pvname.find(self.robotPVsName["statePVs"]["Mode"]) != -1):
			if (value != 0):
				self.__val2 = True
				self.ctrlMsg = "the operation mode is manual!"
			else:
				self.__val2 = False

		elif (pvname.find(self.robotPVsName["servoPVs"]["Status"]) != -1):
			if (char_value == "Servo Off"):
				self.__val3 = True
				self.ctrlMsg = "the servo is off!"
			else:
				self.__val3 = False

		elif (pvname.find(self.robotPVsName["operationPVs"]["Status"]) != -1):
			if (char_value == "Disabled"):
				self.__val4 = True
				self.ctrlMsg = "the operation is disabled!"
			else:
				self.__val4 = False

		elif (pvname.find(self.robotPVsName["controllerErrorPVs"]["errorNumber"]) != -1):
			if (value != 0):
				self.__val5 = True
			else:
				self.__val5 = False

		elif (pvname.find(self.robotPVsName["processErrorPVs"]["errorType"]) != -1):
			if (char_value != "No Error"):
				self.__procErr = True
				self.__procType = char_value
			else:
				self.__procErr = False
				self.__procType = ""

		if self.__val1 or self.__val2 or self.__val3 or self.__val4 or self.__val5:
			self.ctrlErr = True
		else:
			self.ctrlErr = False