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

class robot():
	def __init__(self):

		log.warning("robot in use")

		prcErrMntr = threading.Thread(target=self.processError, args=(), daemon=True)
		log.info("Start Monitoring Process Errors")
		# prcErrMntr.start()

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

		if self.waitPVVal(self.robotPVs["operationPVs"]["Status"], "Enabled"):
			CLIMessage("Servo On ...", "I")
			log.info("Servo On ...")
			self.robotPVs["servoPVs"]["On"].put(1, wait=True)
		else:
			log.error("Can't Enable the Robot!")
			sys.exit()

		if self.waitPVVal(self.robotPVs["servoPVs"]["Status"], "Servo On"):
			CLIMessage("Set Automatic Mode ...", "I")
			log.info("Set Automatic Mode ...")
			self.robotPVs["statePVs"]["Mode"].put(0, wait=True)
		else:
			log.error("Can't Enable the Servo!")
			sys.exit()

		if not self.waitPVVal(self.robotPVs["statePVs"]["operationMode"], "Automatic"):
			log.error("Can't Set Automatic Mode!")
			sys.exit()

		CLIMessage("Run the Program ...", "I")
		log.info("Run the Program ...")
		self.robotPVs["programPVs"]["Run"].put(1, wait=True)

	def checkStatus(self):

		# if self.robotPVs["environmentPVs"]["sampleContainer"].get(timeout=self.timeout, use_monitor=False) !=0:
		# 	self.robotPVs["environmentPVs"]["sampleContainer"].put(0, wait=True)

		# if self.robotPVs["environmentPVs"]["sampleStage"].get(timeout=self.timeout, use_monitor=False) !=0:
		# 	self.robotPVs["environmentPVs"]["sampleStage"].put(0, wait=True)

		# if self.robotPVs["environmentPVs"]["gripperStatus"].get(timeout=self.timeout, use_monitor=False) !=1:
		# 	self.robotPVs["environmentPVs"]["gripperStatus"].put(1, wait=True)

		# val, msg = self.val(self.robotPVs["programPVs"]["Run"].get(timeout=self.timeout, use_monitor=False) !=1, "the program has been stopped!")
		# val, msg = self.val(self.robotPVs["statePVs"]["Mode"].get(timeout=self.timeout, use_monitor=False) !=0, "the mode is manual!")
		# val, msg = self.val(self.robotPVs["servoPVs"]["On"].get(timeout=self.timeout, use_monitor=False) !=1, "the servo is off!")
		# val, msg = self.val(self.robotPVs["operationPVs"]["Enable"].get(timeout=self.timeout, use_monitor=False) !=1, "the operation has been disabled!")
		# val, msg = self.val(self.robotPVs["controllerErrorPVs"]["errorNumber"].get(timeout=self.timeout, use_monitor=False) !=0, "please check the controller error!")

		return val, msg

	def val(self, expression, msg):
		if expression:
			return False, msg
		else:
			return True, ""

	def processError(self):

		errorType = self.robotPVs["processErrorPVs"]["errorType"].get(timeout=self.timeout, use_monitor=False)
		while errorType != "No Error":
			if errorType == "Skip":
				pass	# go to next sample
			if errorType == "Wait For Human Action":
				pass  # exit or stop immediately
			errorType = self.robotPVs["processErrorPVs"]["errorType"].get(timeout=self.timeout, use_monitor=False)
			time.sleep(0.01)

	def startExperiment(self):

		log.warning("sample in operation, the robot is ready to pickup the sample ...")
		# self.robotPVs["environmentPVs"]["sampleInOperation"].put(1, wait=True)

		# while not self.robotPVs["statePVs"]["currentState"].get(as_string=True, timeout=self.timeout, use_monitor=False) == "Wait For Scan Done":
		CLIMessage("waiting for scan done ...", "IO")
		time.sleep(5)

	def finishExperiment(self):

		log.warning("scan has been done, the robot is ready to return the sample to sample container ...")
		# self.robotPVs["environmentPVs"]["scanStatus"].put(0, wait=True)

		# while not self.robotPVs["statePVs"]["currentState"].get(as_string=True, timeout=self.timeout, use_monitor=False) == "Ready":
		CLIMessage("waiting for drop the sample to sample container ...", "IO")

		log.info("the sample is dropped, the scan has been finished sucssesfully ...")
		time.sleep(3)

	def moveSampleContainer(self, position):

		log.info(f"move robot to position {position}")
		# SC.move(self.SC[position])
		time.sleep(0.3)
		# while not SC.done_moving:
		# 	CLIMessage(f"sample container moving: {SC.readback}", "IO")
		# 	time.sleep(0.05)
