import sys
import time
import log
import threading
import _thread
from epics import PV, Motor

from SEDSS.CLIMessage import CLIMessage
from SEDSS.SEDFileManager import readFile

config = "configurations/robot.json"
sampleContainer = "configurations/sampleContainer.json"
SC = Motor("I09R2-MO-MC1:ES-DIFF-STP-ROTX1")

class robot():
	def __init__(self):

		log.warning("robot in use")

		self.cfg = readFile(config).readJSON()
		self.SC = readFile(sampleContainer).readJSON()
		self.timeout = 1

		self.robotPVs = {}
		self.robotPVsName = {}
		allPVsConnected = True
		for category, subdata in self.cfg.items():
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
			sys.exit()

		self.init()

	def init(self):

		# Prepare the PVs to be added to callback, with their attr.

		self.ctrlErr = False
		self.ctrlMsg = ""
		self.procErr = False
		self.procMsg = ""
		self.procType = ""
		self.val1 = False
		self.val2 = False
		self.val3 = False
		self.val4 = False
		self.val5 = False

		errCallbackPVs = [
			self.robotPVs["programPVs"]["Run"],
			self.robotPVs["statePVs"]["Mode"],
			self.robotPVs["servoPVs"]["On"],
			self.robotPVs["operationPVs"]["Enable"],
			self.robotPVs["controllerErrorPVs"]["errorNumber"],
			self.robotPVs["processErrorPVs"]["errorType"],
		]

		log.info("Start Monitoring Controller Errors")
		log.info("Start Monitoring Process Errors")

		for pv in errCallbackPVs:
			pv.add_callback(self.pv_callback)

		procErrExit = threading.Thread(target=self.procErrExit, args=(), daemon=True)
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
			CLIMessage(f"Retrying check the value, time left: {timeformat}", "IO")
			time.sleep(1)

		CLIMessage(f"Timeout reached {timeout} sec. Value {PV} not reached.", "E")
		log.error(f"Timeout reached {timeout} sec. Value {PV} not reached.")
		return False

	def setup(self):
		"""
		Setup the robot:
		- homing sample container
		- check the errors (controller/process)
		- reset the process error notification to confirmed
		- disable the sample (stage/container) sensors (temporary until installing the sensors)
		- check if sample is crucial (this should come from SUP)
		- enable operation
		- servo on
		- automatic mode
		- run the program
		"""

		log.info(f"move sample container to home position")
		SC.move(0)
		time.sleep(0.3)
		while not SC.done_moving:
			CLIMessage(f"sample container moving: {SC.readback}", "IO")
			time.sleep(0.05)

		if self.robotPVs["controllerErrorPVs"]["errorNumber"].get(timeout=self.timeout, use_monitor=False) !=0 or self.robotPVs["processErrorPVs"]["errorType"].get(as_string=True, timeout=self.timeout, use_monitor=False) != "No Error":
			CLIMessage(f"The program won't continue!!! please check the (controller/process) errors, and try again.", "E")
			log.error(f"The program won't continue!!! please check the (controller/process) errors, and try again.")
			sys.exit()

		self.robotPVs["processErrorPVs"]["errorNotified"].put("Confirmed", wait=True)

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

		if self.waitPVVal(self.robotPVs["operationPVs"]["Status"], "Enabled", 60):
			log.info("Servo On ...")
			self.robotPVs["servoPVs"]["On"].put(1, wait=True)
		else:
			log.error("Can't Enable the Robot!")
			sys.exit()

		if self.waitPVVal(self.robotPVs["servoPVs"]["Status"], "Servo On", 60):
			log.info("Set Automatic Mode ...")
			self.robotPVs["statePVs"]["Mode"].put(0, wait=True)
		else:
			log.error("Can't Enable the Servo!")
			sys.exit()

		if not self.waitPVVal(self.robotPVs["statePVs"]["operationMode"], "Automatic", 60):
			log.error("Can't Set Automatic Mode!")
			sys.exit()

		log.info("Run the Program ...")
		self.robotPVs["programPVs"]["Run"].put(1, wait=True)

	def startExperiment(self):
		"""
		Start experiment:
		- confirm that the sample is in the right position
		- check the environment (errors)
		"""

		log.warning("sample in operation, the robot is ready to pickup the sample ...")
		self.robotPVs["environmentPVs"]["sampleInOperation"].put(1, wait=True)

		CLIMessage("waiting for scan done ...", "IO")
		if not self.waitPVVal(self.robotPVs["statePVs"]["currentState"], "Wait For Scan Done", 300):
			log.warning("Max time of (wait for scan done reached 300 sec)")

		if self.procErr and self.procType == "Skip":
			self.robotPVs["processErrorPVs"]["errorNotified"].put("Confirmed", wait=True)
			return self.procType, self.procMsg

		if self.ctrlErr:
			self.ctrlErrPause()

		return 2, "timeout"

	def finishExperiment(self):
		"""
		Finish experiment:
		- confirm that the scan is done
		- check the environment (errors)
		"""

		log.warning("scan has been done, the robot is ready to return the sample to sample container ...")
		self.robotPVs["environmentPVs"]["scanStatus"].put(0, wait=True)

		CLIMessage("waiting for drop the sample to sample container ...", "IO")
		if not self.waitPVVal(self.robotPVs["statePVs"]["currentState"], "Ready", 300):
			log.warning("Max time of waiting for ready state reached 300 sec)")

		if self.procErr and self.procType == "Skip":
			self.robotPVs["processErrorPVs"]["errorNotified"].put("Confirmed", wait=True)
			return self.procType, self.procMsg

		if self.ctrlErr:
			self.ctrlErrPause()

		return 2, "timeout"    ## to add spinner condition

	def moveSampleContainer(self, position):

		# Move sample container to the target position

		log.info(f"move sample container to position {position}")
		SC.move(self.SC[position])
		time.sleep(0.3)
		while not SC.done_moving:
			CLIMessage(f"sample container moving: {SC.readback}", "IO")
			time.sleep(0.05)

	def controllerError(self):
		if self.procErr:
			self.ctrlMsg = self.robotPVs["controllerErrorPVs"]["errorMessage"].get(as_string=True, timeout=self.timeout, use_monitor=False)

	def processError(self):
		if self.procErr:
			self.procMsg = self.robotPVs["processErrorPVs"]["errorMessage"].get(as_string=True, timeout=self.timeout, use_monitor=False)

	def ctrlErrPause(self):

		# Pause the program for any controller error

		startTime = time.time()
		log.warning(f"Scan is paused, {self.ctrlMsg}")
		while self.ctrlErr:
			difftime = time.time() - startTime
			CLIMessage(f"Scan is paused, {self.ctrlMsg}, the scan will be resumed automatically | pausing time {difftime}", "IO")
			time.sleep(0.05)
		log.warning(f"Pausing time: {difftime}")

	def procErrExit(self):

		# Exit from the program immediately if the process error "Wait For Human Action"

		check = 1
		while check:
			if self.procErr and self.procType == "Wait For Human Action":
				log.error(f"Process Error!, {self.procMsg}")
				CLIMessage(f"Process Error!, {self.procMsg}", "IR")
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

		if (pvname.find(self.robotPVsName["programPVs"]["Run"]) != -1):
			if (value != 1):
				self.val1 = True
				self.ctrlMsg = "the program is stopped!"
			else:
				self.val1 = False

		elif (pvname.find(self.robotPVsName["statePVs"]["Mode"]) != -1):
			if (value != 0):
				self.val2 = True
				self.ctrlMsg = "the operation mode is manual!"
			else:
				self.val2 = False

		elif (pvname.find(self.robotPVsName["servoPVs"]["On"]) != -1):
			if (value != 1):
				self.val3 = True
				self.ctrlMsg = "the servo is off!"
			else:
				self.val3 = False

		elif (pvname.find(self.robotPVsName["operationPVs"]["Enable"]) != -1):
			if (value != 1):
				self.val4 = True
				self.ctrlMsg = "the operation is disabled!"
			else:
				self.val4 = False

		elif (pvname.find(self.robotPVsName["controllerErrorPVs"]["errorNumber"]) != -1):
			if (value != 0):
				self.val5 = True
				self.ctrlMsg = self.controllerError()
			else:
				self.val5 = False

		elif (pvname.find(self.robotPVsName["processErrorPVs"]["errorType"]) != -1):
			if (char_value != "No Error"):
				self.procErr = True
				self.procType = char_value
				self.procMsg = self.processError()
			else:
				self.procErr = False
				self.procType = ""

		if self.val1 or self.val2 or self.val3 or self.val4 or self.val5:
			self.ctrlErr = True
		else:
			self.ctrlErr = False