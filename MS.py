#!/usr/bin/python3.9
# **: for UI Visualization tool use

import os
import sys
import log
import time
from datetime import datetime
import decimal
import shutil
import signal
import subprocess
import threading
import _thread

from epics import PV, Motor
from emailNotifications import email
from SEDSS.CLIMessage import CLIMessage
from SEDSS.SEDTransfer import SEDTransfer
from SEDSS.SEDFileManager import readFile, path

configFileName = "configurations/main.json"
configFile = readFile(configFileName).readJSON()

P = configFile["macros"]["macrosList"]["P"]
N = configFile["macros"]["macrosList"]["N"]
R = configFile["macros"]["macrosList"]["R"]
proposalsInfo = configFile["paths"]["proposalsInfo"]

def pauseErrors(func):
	def wrapper(self, *args, **kwargs):
		if self.pauseErr:
			self.pause()
		result = func(self, *args, **kwargs)
		if self.pauseErr:
			self.pause()
		return result
	return wrapper

class XPD():
	def __init__(self, PVsFiles, macros, scanningSubs):

		log.setup_custom_logger("./SED_MS_Scantool.log")

		self.PVsFiles = PVsFiles
		self.macros   = macros
		self.scanSubs = scanningSubs

		self.epics_pvs 	  = {}		# store the PVs endwith PVName in req files
		self.epics_motors = {}		# store the PVs endwith MotorName in req files
		self.epics_cfg 	  = {}		# store the PVs endwith ConfigName in req files
		self.data_pvs 	  = {}		# store the PVs of tables (intervals) & samples names
		self.epics_names  = {}		# store the PVs names for epics_pvs & epics_motors

		self.timeout = 1
		self.exit = False			# exit flag to be used in special cases
		self.lock = False			# lock signal_handler for the 1st call

		for pv_file in self.PVsFiles:
			self.readPVsFile(pv_file)

		if not self.checkConnectedPVs():
			CLIMessage("The scanning tool will not continue, please check the non connected PVs", "E")
			log.error("The The scanning tool will not continue, some PVs are not connected")
			email("").sendEmail("MS_IOC")
			sys.exit()

		self.epics_pvs["ProgInt"].put(0, wait=True)			# programmatic interrupt to define the source of interruption (program:1, user action:0)

		log.info("Start scanning tool")
		self.init()

		self.robotInUse 	   = self.epics_pvs["UseRobot"].get(timeout=self.timeout, use_monitor=False)
		self.creationTime 	   = self.epics_pvs["CreationTime"].get(timeout=self.timeout, use_monitor=False)
		self.experimentType    = self.epics_pvs["ExperimentType"].get(as_string=True, timeout=self.timeout, use_monitor=False)
		self.expFileName 	   = self.epics_pvs['ExperimentalFileName'].get(as_string=True, timeout=self.timeout, use_monitor=False)
		self.fullExpFileName   = f"{self.expFileName}_{self.creationTime}"
		self.proposalID 	   = None if self.experimentType != "Users" else self.epics_pvs["ProposalID"].get(timeout=self.timeout, use_monitor=False)
		self.DS				   = self.epics_cfg["DS"]
		self.DSUser			   = self.epics_cfg["DSUser"]
		self.pilatusServerUser = self.epics_cfg["PilatusServerUser"]
		self.pilatusServer 	   = self.epics_cfg["PilatusServer"]
		self.dataPath 		   = self.epics_cfg["DataPath"]
		self.detDataPath 	   = self.epics_cfg["DetDataPath"]
		self.fullExpDataPath   = f"{self.dataPath}/{self.fullExpFileName}"
		self.SEDTop			   = self.epics_cfg["Top"]
		self.spinner 		   = self.epics_names["Spinner"]

		self.epics_pvs["FullExpFileName"].put(self.fullExpFileName, wait=True)		# **

		self.detectorInit()

		signal.signal(signal.SIGINT, self.signal_handler)

	def init(self):

		# Prepare the PVs to be added to callback, with their attr.

		self.pauseErr = False
		self.pauseMsg = ""
		self.pauseTime = 0
		self.energy = 0
		self.beam = False				# flag for beam available
		self.shutterStatus = False		# flag for shutter status
		self.shutter1 = False			# flag for shutter one
		self.shutter2 = False			# flag for shutter two
		self.stopperShutter = False		# flag for stopper shutter
		self.pauseButton = False		# flag for pause button (Visualization)
		self.stopAction = False			# flag for stop button (Visualization)
		self.stopMsg = ""

		if self.epics_pvs["TestingMode"].get(timeout=self.timeout, use_monitor=False):
			log.warning("Testing mode")
			self.testingMode = True
		else:
			self.testingMode = False

		errCallbackPVs = [
			self.epics_pvs["Energy"],
			self.epics_pvs["DcctCurrent"],
			self.epics_pvs["ShutterStatus"],
			self.epics_pvs["ShutterOne"],
			self.epics_pvs["ShutterTwo"],
			self.epics_pvs["StopperStatus"],
			self.epics_pvs["ScanStatus"],
		]

		for pv in errCallbackPVs:
			pv.add_callback(self.pv_callback)

		exitAction = threading.Thread(target=self.stop, args=(), daemon=True)
		exitAction.start()

	def readPVsFile(self, PVFile):
		"""
		Read PVs file:
		- read .req file
		- get the PVs (endwith)
		- call sortPV() method
		"""

		pv_file = open(PVFile)
		lines = pv_file.read().splitlines()
		pv_file.close()

		for line in lines:
			line = line.lstrip()

			# ignore blank lines or lines starting with #
			if line.startswith("#") or line == "":
				continue

			self.sortPV(line)

	def sortPV(self, line):
		"""
		Sort PV:
		- sort the PV based on type:
			* endswith SupportName ==> epics_pvs
			* endswith PVName 	   ==> epics_pvs
			* endswith MotorName   ==> epics_motors
			* endswith ConfigName  ==> epics_cfg
			* endswith $(N)		   ==> data_pvs
		"""

		dictValue = line
		dictKey = line

		for key, value in self.macros.items():

			if dictValue.startswith(P) and dictValue.endswith("SupportName"):
				dictValue = dictValue.replace(key, f"{value}")
				pvValue = dictValue.replace(R, "Supp:")
				pvKey = dictKey.replace(key, "").replace(R, "").replace("SupportName", "")
				self.epics_pvs[pvKey] = PV(pvValue.replace("SupportName", ""))

			elif dictValue.startswith(P) and not dictValue.endswith(N):
				dictValue = dictValue.replace(key, f"{value}")
				val = dictValue.replace(R, self.scanSubs)

				if dictValue.find("PVName") != -1:
					pvValue = PV(val).value
					pvKey = dictKey.replace(key, "").replace(R, "").replace("PVName", "")
					self.epics_pvs[pvKey] = PV(pvValue)
					self.epics_names[pvKey] = pvValue

				elif dictValue.find("MotorName") != -1:
					motorValue = PV(val).value
					motorKey = dictKey.replace(key, "").replace(R, "").replace("MotorName", "")
					self.epics_motors[motorKey] = Motor(motorValue)
					self.epics_names[motorKey] = motorValue

				elif dictValue.find("ConfigName") != -1:
					configValue = PV(val).value
					configKey = dictKey.replace(key, "").replace(R, "").replace("ConfigName", "")
					self.epics_cfg[configKey] = configValue

				else:
					pvKey = dictKey.replace(key, "").replace(R, "")
					self.epics_pvs[pvKey] = PV(val)
					self.epics_names[pvKey] = val

			elif isinstance(value, list) and dictValue.endswith(N):
				for n in value:
					pvValue = dictValue.replace(P, "MS:").replace(key, f"{n}")
					pvKey = dictKey.replace(P, "").replace(key, f"{n}")
					self.data_pvs[pvKey] = PV(pvValue)

	def checkConnectedPVs(self):
		"""
		Check connected PVs:
		- check if all PVs are connected
		- exit & send email notification if one of the PVs not connected
		"""

		allPVsConnected = True
		for key in self.epics_pvs:
			if self.epics_pvs[key].get(timeout=self.timeout, use_monitor=False) is None:
				CLIMessage(f"PV {self.epics_pvs[key].pvname} is not connected", "E")
				log.error(f"PV {self.epics_pvs[key].pvname} is not connected")
				allPVsConnected = False
			else:
				CLIMessage(f"PV {self.epics_pvs[key].pvname} is connected", "I")

		return allPVsConnected

	def calcScanPoints(self):
		"""
		Calculate scan points:
		- return:
			* #Intervals
			* #Scans
			* Scan points (based on start point, end point, and steps size) for each interval
			* Exposure time for each interval
		"""

		intervals = self.epics_pvs["Intervals"].get(timeout=self.timeout, use_monitor=False)
		scans 	  = self.epics_pvs["Scans"].get(timeout=self.timeout, use_monitor=False)
		scanPoints = {}
		exposureTime = []

		for interval in range(intervals):
			scanpoints = self.drange(self.data_pvs[f"StartPoint{interval+1}"].get(timeout=self.timeout, use_monitor=False)
							,self.data_pvs[f"EndPoint{interval+1}"].get(timeout=self.timeout, use_monitor=False)
							,self.data_pvs[f"StepSize{interval+1}"].get(timeout=self.timeout, use_monitor=False))
			scanPoints[interval] = scanpoints
			exposureTime.append(self.data_pvs[f"ExposureTime{interval+1}"].get(timeout=self.timeout, use_monitor=False))

		return intervals, scans, scanPoints, exposureTime

	def drange(self, start, stop, step, prec=10):

		decimal.getcontext().prec = prec
		points = []
		val = decimal.Decimal(start)
		step = decimal.Decimal(step)

		if not step:
			points.append(float(start))
		else:
			while val <= stop:
				points.append(float(val))
				val += step

		return points

	def initDir(self, path):
		"""
		Initialize local directories:
		- create the experimental data folders
		- if robot in use:
			* if the initializing failed ==> skip
		- if robot not used:
			* if the initializing failed ==> exit & send email notification
		"""

		log.info(f"Initializing dir {path} ...")
		CLIMessage(f"mkdir -p {self.dataPath}/{path}", "M")

		if self.robotInUse:
			process = subprocess.run(f"mkdir -p {self.dataPath}/{path}", shell=True, stderr=subprocess.PIPE)
			return process.returncode
		else:
			result = os.system(f"mkdir -p {self.dataPath}/{path}")
			if result !=0:
				msg = f"Data path {path} init failed!"
				log.error(msg)
				self.epics_pvs["ScanStatus"].put(5, wait=True)		# **
				if not self.testingMode:
					email(self.experimentType, self.proposalID).sendEmail(type="pathFailed", msg=msg, DS=self.fullExpDataPath)
				sys.exit()

	def detectorInit(self):
		"""
		Detector initializing:
		- define the images path
		- define #Images = 1, this solution is temporary, it will be changed to AreaDetector when developing continuous scan
		"""

		log.info("Init detector ...")
		self.epics_pvs["ImagePath"].put(self.detDataPath, wait=True)
		self.epics_pvs["NImages"].put(1, wait=True)

	def startScan(self):
		"""
		Start scan:
		- check if there are pausing errors
		- start UI Visualization
		- send email notification
		"""

		if self.pauseErr:
			self.pause()

		log.info(f"Experiment type: {self.experimentType}{' ' if self.experimentType != 'Users' else ', ProposalID: ' + str(self.proposalID)}")
		self.epics_pvs["ScanStatus"].put(1, wait=True)		# **
		log.info("Start the scan")

		# start UI Visualization tool
		visualizationTool = os.path.expanduser(configFile["exe"]["visualization"][f"{self.epics_pvs['ScanningType'].get(timeout=self.timeout, use_monitor=False)}"])
		try:
			subprocess.Popen(visualizationTool, shell=True)
			log.info(f"Start UI Visualization tool {visualizationTool}")
		except:
			log.error(f"Can't start UI Visualization tool! {visualizationTool}")

		if not self.testingMode:
			email(self.experimentType, self.proposalID).sendEmail("startScan", DS=self.fullExpDataPath)

	def finishScan(self):
		"""
		Finish scan:
		- move log & config files to the defined experimental data path
		- call dataTransfer() method
		- send email notification
		"""

		self.epics_pvs["EndTime"].put(datetime.now().strftime("%H:%M:%S"), wait=True)		# **
		shutil.move("SED_MS_Scantool.log", f"{self.dataPath}/{self.fullExpFileName}/{self.fullExpFileName}.log")
		shutil.move("config.config", f"{self.dataPath}/{self.fullExpFileName}/{self.fullExpFileName}.config")
		self.dataTransfer()
		sys.exit()

	def dataTransfer(self):
		"""
		Data transfer:
		- determine the destination full experimental data path
		- transfer the data to the storage
		"""

		CLIMessage("Transferring data to the storage ...", "M")

		if self.experimentType == "Users":
			experimentalDataPath = path(self.SEDTop, beamline="MS", proposal=self.proposalID, semester=readFile(proposalsInfo).getProposalInfo(self.proposalID, type="sem")).getPropPath()
		else:
			experimentalDataPath = path(self.SEDTop, beamline="MS").getIHPath()

		try:
			SEDTransfer(self.fullExpDataPath, f"{self.DSUser}@{self.DS}:{experimentalDataPath}").scp()
			log.info(f"Data transfer to {experimentalDataPath} is done")
		except:
			log.error(f"problem transferring the data to ({experimentalDataPath})!")

	def pause(self):
		"""
		System error pause:
		- pause the program for any pausing error
		- send emails notifications for (pause/resume)
		"""

		startTime = time.time()
		log.warning(f"Scan is paused, {self.pauseMsg}")

		if not self.testingMode:
			email(self.experimentType, self.proposalID).sendEmail(type="scanPaused", msg=self.pauseMsg)

		while self.pauseErr:
			diffTime = time.time() - startTime
			mm, ss = divmod((int(diffTime)), 60)
			hh, mm = divmod(mm, 60)
			timeformat = f"{hh:02d}:{mm:02d}:{ss:02d}"
			CLIMessage(f"Scan is paused, {self.pauseMsg}, the scan will be resumed automatically | pausing time hh:mm:ss {timeformat}", "IO")
			time.sleep(0.05)
		log.warning(f"Pausing time (hh:mm:ss): {timeformat}")

		if not self.testingMode:
			email(self.experimentType, self.proposalID).sendEmail(type="scanResumed", msg=f"pausing time (hh:mm:ss) was: {timeformat}")

		self.pauseTime = diffTime

	def stop(self):
		"""
		Stop:
		- emit keyboard interrupt if stop button has been pressed
		"""
		
		check = 1
		while check:
			if self.stopAction:
				check = 0
				_thread.interrupt_main()			# exit from main thread (KeyInterrupt)
			time.sleep(0.1)

	def pv_callback(self, pvname=None, value=None, char_value=None, **kw):
			"""
			Callback function that is called by pyEpics when certain EPICS PVs are changed

			The PVs that are handled are:
			- Beam Energy
			- Machine Current
			- Shutter Status
			- Shutter One
			- Shutter Two
			- Stopper Status
			- User Action
			- to add stop, resume, start, pause pvs from data visualization
			"""
			# log.debug(f"pv_callback pvName={pvname}, value={value}, char_value={char_value}")

			if (pvname.find(self.epics_names["Energy"]) != -1 and not self.testingMode):
				self.energy = value

			elif (pvname.find(self.epics_names["DcctCurrent"]) != -1 and not self.testingMode):
				if not (20 <= value <= 300):
					self.beam = True
					self.pauseMsg = "No Beam Available!"
				else:
					self.beam = False

			elif (pvname.find(self.epics_names["ShutterStatus"]) != -1 and not self.testingMode):
				if (value != 3):
					self.shutterStatus = True
					self.pauseMsg = "The shutter is closed!"
				else:
					self.shutterStatus = False

			elif (pvname.find(self.epics_names["ShutterOne"]) != -1 and not self.testingMode):
				if (value != 3):
					self.shutter1 = True
					self.pauseMsg = "Shutter 1 is closed!"
				else:
					self.shutter1 = False

			elif (pvname.find(self.epics_names["ShutterTwo"]) != -1 and not self.testingMode):
				if (value != 3):
					self.shutter2 = True
					self.pauseMsg = "Shutter 2 is closed!"
				else:
					self.shutter2 = False

			elif (pvname.find(self.epics_names["StopperStatus"]) != -1 and not self.testingMode):
				if (value != 3):
					self.stopperShutter = True
					self.pauseMsg = "Stopper shutter is closed!"
				else:
					self.stopperShutter = False

			elif (pvname.find(self.epics_names["ScanStatus"]) != -1):
				if (value == 3):
					self.pauseButton = True
					self.pauseMsg = "Scan is paused by human action!"
				else:
					self.pauseButton = False
				if (value == 4):
					self.stopAction = True
					self.stopMsg = "Scan is stopped by human action!"

			if self.beam or self.shutterStatus or self.shutter1 or self.shutter2 or self.stopperShutter or self.pauseButton:
				self.pauseErr = True
			else:
				self.pauseErr = False

	def signal_handler(self, sig, frame):
		"""
		Signal Handler:
		- determine the source of interruption
		- stop spinner
		- call finishScan() method
		- send email notification
		- exit from the program
		"""

		if sig == signal.SIGINT:
			if self.epics_pvs["ProgInt"].get(timeout=self.timeout, use_monitor=False):
				log.warning("Running scan is terminated!!")
			else:
				intMSg = "User Action: (Ctrl + C (^C) / Stop Button) has been pressed, Running scan is terminated!!"
				log.warning(intMSg)
				if not self.testingMode:
					email(self.experimentType, self.proposalID).sendEmail(type="scanStopped", msg=intMSg, DS=self.fullExpDataPath)

			log.warning("stop spinner")
			PV(f"{self.spinner}.STOP").put(1)

			self.finishScan()
