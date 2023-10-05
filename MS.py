#!/usr/bin/python3.9

import os
import sys
import log
import time
import decimal
import signal

from epics import PV, Motor
from SEDSS.CLIMessage import CLIMessage

class XPD():
	def __init__(self, PVsFiles, macros, scanningSubs):

		log.setup_custom_logger("./SED_MS_Scantool.log")
		log.info("Start scanning tool")

		self.PVsFiles = PVsFiles
		self.macros   = macros
		self.scanSubs = scanningSubs
		self.epics_pvs = {}
		self.epics_motors = {}
		self.epics_cfg = {}
		self.data_pvs = {}
		self.timeout = 1

		for pv_file in self.PVsFiles:
			self.readPVsFile(pv_file)

		# if self.checkConnectedPVs():
		# 	pass
		# else:
		# 	CLIMessage("The scanning tool will not continue, please check the non connected PVs", "E")
		# 	log.error("The The scanning tool will not continue, some PVs are not connected")
		# 	sys.exit()

		if self.epics_pvs["CancelScan"].get(timeout=self.timeout, use_monitor=False):
			CLIMessage("Scan has been cancelled \n", "IO")
			log.warning("Scan has been cancelled")
			sys.exit()

		while not self.epics_pvs["StartScan"].get(timeout=self.timeout, use_monitor=False):
			CLIMessage("Press Finish to start the scan", "IO")
			time.sleep(0.2)

		signal.signal(signal.SIGINT, self.signal_handler)

	def readPVsFile(self, PVFile):

		pv_file = open(PVFile)
		lines = pv_file.read().splitlines()
		pv_file.close()

		for line in lines:
			line = line.lstrip()

			# ignore blank lines or lines starting with #
			if line.startswith('#') or line == '':
				continue

			self.sortPV(line)

	def sortPV(self, line):

		dictValue = line
		dictKey = line

		for key, value in self.macros.items():

			if dictValue.startswith("$(P)") and not dictValue.endswith("$(N)"):

				dictValue = dictValue.replace(key, f"{value}")
				val = dictValue.replace("$(R)", self.scanSubs)

				if dictValue.find('PVName') != -1:

					pvValue = PV(val).value
					pvKey = dictKey.replace(key, "").replace("$(R)", "").replace("PVName", "")
					self.epics_pvs[pvKey] = PV(pvValue)

				elif dictValue.find('MotorName') != -1:

					motorValue = PV(val).value
					motorKey = dictKey.replace(key, "").replace("$(R)", "").replace("MotorName", "")
					self.epics_motors[motorKey] = Motor(motorValue)

				elif dictValue.find('ConfigName') != -1:

					configValue = PV(val).value
					configKey = dictKey.replace(key, "").replace("$(R)", "").replace("ConfigName", "")
					self.epics_cfg[configKey] = configValue

				else:

					pvKey = dictKey.replace(key, "").replace("$(R)", "")
					self.epics_pvs[pvKey] = PV(val)

			elif isinstance(value, list) and dictValue.endswith("$(N)"):

				for n in value:

					pvValue = dictValue.replace("$(P)", "MS:").replace(key, f"{n}")
					pvKey = dictKey.replace("$(P)", "").replace(key, f"{n}")
					self.data_pvs[pvKey] = PV(pvValue)
			else:
				pass

	def checkConnectedPVs(self):

		allPVsConnected = True
		for key in self.epics_pvs:
			if self.epics_pvs[key].get(timeout=self.timeout, use_monitor=False) is None:
				CLIMessage(f"PV {self.epics_pvs[key].pvname} is not connected", "E")
				log.error(f"PV {self.epics_pvs[key].pvname} is not connected")
				allPVsConnected = False
			else:
				CLIMessage(f"PV {self.epics_pvs[key].pvname} is connected", "I")

		return allPVsConnected

	def drange(self,start,stop,step,prec=10):
		decimal.getcontext().prec = prec
		points = []
		r= decimal.Decimal(start)
		step = decimal.Decimal(step)
		if not step:
			points.append(float(start))
		else:
			while r <=stop:
				points.append(float(r))
				r += step
		return points

	def preCheck(self):
		if self.epics_pvs["TestingMode"].get(timeout=self.timeout):
			log.warning("Testing mode, so will not open shutter...")
		else:
			pass

	def initDir(self):

		log.info("Initializing dir on IOC server ...")
		CLIMessage(f"ssh -qt {self.epics_cfg['IocServerUser']}@{self.epics_cfg['IocServer']} 'mkdir -p {self.epics_pvs['ExperimentalFileName']}'", "M")
		result = os.system(f"ssh -qt {self.epics_cfg['IocServerUser']}@{self.epics_cfg['IocServer']} 'mkdir -p {self.epics_pvs['ExperimentalFileName']}'")
		if result !=0:
			log.error("Data Path init failed!")
			raise Exception("Data Path init failed!")

	def detectorInit(self):

		log.info("Init detector ...")
		self.epics_pvs["ImagePath"].put(self.epics_cfg["DetDataPath"], wait=True)
		self.epics_pvs["NImages"].put(1, wait=True)
		self.epics_pvs["DetExposureTime"].put(self.data_pvs["ExposureTime"], wait=True)

	def signal_handler(self, sig, frame):

		if sig == signal.SIGINT:
			log.warning("Ctrl + C (^C) has been pressed, running scan is terminated!!")
			# os.rename("SED_Scantool.log", "SEDScanTool_{}.log".format(self.creationTime))
			# shutil.move("SEDScanTool_{}.log".format(self.creationTime), "{}/SEDScanTool_{}.log".format(self.localDataPath, self.creationTime))
			# self.dataTransfer()
			sys.exit()
