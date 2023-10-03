import sys
import time
import log
import threading
from epics import PV, Motor

from SEDSS.CLIMessage import CLIMessage
from SEDSS.SEDFileManager import readFile

config = "configurations/robot.json"
sampleContainer = "configurations/sampleContainer.json"
# SC = Motor("I09R2-MO-MC1:ES-DIFF-STP-ROTX1")
pause = PV("MS:PauseScan")

class robot():
	def __init__(self):

		log.warning("robot in use")

		self.cfg = readFile(config).readJSON()
		self.SC = readFile(sampleContainer).readJSON()

		self.robotPVs = {}
		allPVsConnected = True
		for category, subdata in self.cfg.items():
			self.robotPVs[category] = {}
			if isinstance(subdata, dict):
				for key, value in subdata.items():
					# if PV(value).get(timeout=self.timeout, use_monitor=False) is None:
						CLIMessage(f"PV {value} is not connected", "E")
						log.error(f"PV {value} is not connected")
						allPVsConnected = False
					# else:
						self.robotPVs[category][key] = PV(value)
						CLIMessage(f"PV {value} is connected", "I")

		# if not allPVsConnected:
		#     CLIMessage("Robot PVs not connected, the program won't continue", "E")
		#	  log.error("Robot PVs not connected, the program won't continue")
		#     sys.exit()
		self.init()

	def init(self):

		self.ctrlErr = False
		self.ctrlMsg = ""
		self.procErr = False
		self.procMsg = ""
		self.val1 = False
		self.val2 = False
		self.val3 = False
		self.val4 = False
		self.val5 = False

		log.info("Start Monitoring Controller Errors")
		ctrlErrPause = threading.Thread(target=self.controllerError, args=(), daemon=True)
		ctrlErrPause.start()

		log.info("Start Monitoring Process Errors")
		procErrPause = threading.Thread(target=self.processError, args=(), daemon=True)
		procErrPause.start()

		errCallbackPVs = [
			self.robotPVs["programPVs"]["Run"],
			self.robotPVs["statePVs"]["Mode"],
			self.robotPVs["servoPVs"]["On"],
			self.robotPVs["operationPVs"]["Enable"],
			self.robotPVs["controllerErrorPVs"]["errorNumber"],
			self.robotPVs["processErrorPVs"]["errorType"],
		]

		for pv in errCallbackPVs:
			PV(pv).add_callback(self.pv_callback)

	def waitPVVal(self, PV, val, timeout = 5):

		startTime = time.time()
		while time.time() - startTime < timeout:
			checkVal = PV.get(as_string=True, timeout=self.timeout, use_monitor=False)

			if checkVal == val:
				return True

			mins, secs = divmod(int(timeout - (time.time() - startTime)), 60)
			timeformat = f"{mins:02d}:{secs:02d}"
			CLIMessage(f"Retrying check the value, time left: {timeformat}", "W")
			time.sleep(1)

		CLIMessage(f"Timeout reached {timeout} sec. Value {PV} not reached.", "E")
		log.error(f"Timeout reached {timeout} sec. Value {PV} not reached.")
		return False

	def setup(self):

		log.info(f"move sample container to home position")
		# SC.move(0)
		# time.sleep(0.3)
		# while not SC.done_moving:
		# 	CLIMessage(f"sample container moving: {SC.readback}", "IO")
		# 	time.sleep(0.05)

		if self.robotPVs["controllerErrorPVs"]["errorNumber"].get(timeout=self.timeout, use_monitor=False) !=0 or self.robotPVs["processErrorPVs"]["errorType"].get(as_string=True, timeout=self.timeout, use_monitor=False) != "No Error":
			CLIMessage(f"The program won't continue!!! please check the (controller/process) errors, and try again.", "E")
			log.error(f"The program won't continue!!! please check the (controller/process) errors, and try again.")
			sys.exit()

		CLIMessage("Set Sample Container to 0 ...", "I")
		log.info("Set Sample Container to 0 ...")
		self.robotPVs["environmentPVs"]["sampleContainer"].put(0, wait=True)

		CLIMessage("Set Sample Stage to 0 ...", "I")
		log.info("Set Sample Stage to 0 ...")
		self.robotPVs["environmentPVs"]["sampleStage"].put(0, wait=True)

		CLIMessage("Set Geipper Status to 1 ...", "I")
		log.info("Set Geipper Status to 1 ...")
		self.robotPVs["environmentPVs"]["gripperStatus"].put(1, wait=True)

		# CLIMessage(f"Crucial Experiment? {}", "I")
		# log.warning(f"Crucial Experiment? {}")
		# self.robotPVs["environmentPVs"]["crucialExperiment"].put(1, wait=True)

		CLIMessage("Enable operation ...", "I")
		log.info("Enable operation ...")
		self.robotPVs["operationPVs"]["Enable"].put(1, wait=True)

		if self.waitPVVal(self.robotPVs["operationPVs"]["Status"], "Enabled", 60):
			CLIMessage("Servo On ...", "I")
			log.info("Servo On ...")
			self.robotPVs["servoPVs"]["On"].put(1, wait=True)
		else:
			log.error("Can't Enable the Robot!")
			sys.exit()

		if self.waitPVVal(self.robotPVs["servoPVs"]["Status"], "Servo On", 60):
			CLIMessage("Set Automatic Mode ...", "I")
			log.info("Set Automatic Mode ...")
			self.robotPVs["statePVs"]["Mode"].put(0, wait=True)
		else:
			log.error("Can't Enable the Servo!")
			sys.exit()

		if not self.waitPVVal(self.robotPVs["statePVs"]["operationMode"], "Automatic", 60):
			log.error("Can't Set Automatic Mode!")
			sys.exit()

		CLIMessage("Run the Program ...", "I")
		log.info("Run the Program ...")
		self.robotPVs["programPVs"]["Run"].put(1, wait=True)

	def startExperiment(self):

		log.warning("sample in operation, the robot is ready to pickup the sample ...")
		# self.robotPVs["environmentPVs"]["sampleInOperation"].put(1, wait=True)

		CLIMessage("waiting for scan done ...", "IO")
		# if not self.waitPVVal(self.robotPVs["statePVs"]["currentState"], "Wait For Scan Done", 300):
			# log.error("Max time of (wait for scan done reached 300 sec)")
			# sys.exit()		
		time.sleep(3)

	def finishExperiment(self):

		log.warning("scan has been done, the robot is ready to return the sample to sample container ...")
		# self.robotPVs["environmentPVs"]["scanStatus"].put(0, wait=True)

		CLIMessage("waiting for drop the sample to sample container ...", "IO")
		# if not self.waitPVVal(self.robotPVs["statePVs"]["currentState"], "Ready", 300):
			# log.error("Max time of waiting for ready state reached 300 sec)")
			# sys.exit()	

		log.info("the sample is dropped, the scan has been finished sucssesfully ...")
		time.sleep(3)

	def moveSampleContainer(self, position):

		log.info(f"move sample container to home position")
		# SC.move(self.SC[position])
		time.sleep(0.3)
		# while not SC.done_moving:
		# 	CLIMessage(f"sample container moving: {SC.readback}", "IO")
		# 	time.sleep(0.05)

	def controllerError(self):
		while True:
			if self.ctrlErr:
				pass
			time.sleep(0.2)

	def processError(self):
		while True:
			if self.procErr:
				pass
			time.sleep(0.2)

	# def processError(self):

	# 	errorType = self.robotPVs["processErrorPVs"]["errorType"].get(timeout=self.timeout, use_monitor=False)
	# 	while errorType != "No Error":
	# 		if errorType == "Skip":
	# 			pass	# go to next sample
	# 		if errorType == "Wait For Human Action":
	# 			pass  # exit or stop immediately
	# 		errorType = self.robotPVs["processErrorPVs"]["errorType"].get(timeout=self.timeout, use_monitor=False)
	# 		time.sleep(0.01)

	def ctrlErrVal(self):
		return self.ctrlErr, self.ctrlMsg
		
	def procErrVal(self):
		return self.procErr, self.procMsg

	def pv_callback(self, pvname=None, value=None, char_value=None, **kw):
		"""Callback function that is called by pyEpics when certain EPICS PVs are changed

		The PVs that are handled are:
		"""

		log.debug(f"pv_callback pvName={pvname}, value={value}, char_value={char_value}")
		
		if (pvname.find(self.robotPVs["programPVs"]["Run"]) != -1):
			if (value != 1):
				self.val1 = True
				self.ctrlMsg = "the program is stopped!"
			else:
				self.val1 = False 

		elif (pvname.find(self.robotPVs["statePVs"]["Mode"]) != -1):
			if (value != 0):
				self.val2 = True
				self.ctrlMsg = "the operation mode is manual!"
			else:
				self.val2 = False 

		elif (pvname.find(self.robotPVs["servoPVs"]["On"]) != -1):
			if (value != 1):
				self.val3 = True
				self.ctrlMsg = "the servo is off!"
			else:
				self.val3 = False 

		elif (pvname.find(self.robotPVs["operationPVs"]["Enable"]) != -1):
			if (value != 1):
				self.val4 = True
				self.ctrlMsg = "the operation is disabled!"
			else:
				self.val4 = False 

		elif (pvname.find(self.robotPVs["controllerErrorPVs"]["errorNumber"]) != -1):
			if (value != 0):
				self.val5 = True
				self.ctrlMsg = char_value
			else:
				self.val5 = False 

		elif (pvname.find(self.robotPVs["processErrorPVs"]["errorType"]) != -1):
			if (char_value != "No Error"):
				self.procErr = True
				self.procMsg = char_value
			else:
				self.procErr = False 

		if self.val1 or self.val2 or self.val3 or self.val4 or self.val5:
			self.ctrlErr = True
		else:
			self.ctrlErr = False