#!/usr/bin/python3.9

import subprocess
import sys
import log
from time import sleep

from epics import PV
from SEDSS.CLIMessage import CLIMessage
from SEDSS.UIMessage import UIMessage
# try:
# 	from epics import PV
# 	from SEDSS.CLIMessage import CLIMessage
# 	from SEDSS.UIMessage import UIMessage

# except ImportError as error:
# 	print("Please ensure that the following packages are installed properly:\n ")
# 	print("pyepics\n")
# 	print("SEDSS package\n")
# 	sys.exit()

class XRD():

	def __init__(self, PVsFiles, macros):

		log.setup_custom_logger("./SED_MS_Scantool.log")
		log.info("Start scanning tool")

		self.PVsFiles = PVsFiles
		self.macros   = macros
		self.epics_pvs = {}
		self.data_pvs = {}

		if not isinstance(PVsFiles, list):
			pv_files = [PVsFiles]

		for pv_file in self.PVsFiles:
			self.readPVsFile(pv_file, self.macros)

		if self.checkConnectedPVs():
			pass
		else:
			CLIMessage("The scanning tool will not continue, please check the non connected PVs", "E")
			log.error("The The scanning tool will not continue, some PVs are not connected")
			sys.exit()
		
		subprocess.run(['sh', '-c', 'cd & /home/dcasu/MStest'])

		while not self.epics_pvs["StartScan"].get():
			CLIMessage("Press Finish to start the scan", "IO")
			sleep(0.2)
		
		self.preCheck()
		self.detectorInit()
		self.startScan()

	def readPVsFile(self, PVFile, macros):
		pv_file = open(PVFile)
		lines = pv_file.read().splitlines()
		pv_file.close()

		for line in lines:
			line = line.lstrip()

			# ignore blank lines or lines starting with #
			if line.startswith('#') or line == '':
				continue

			dictValue = line
			dictKey = line

			for key, value in macros.items():

				if dictValue.startswith("$(P)") and not dictValue.endswith("$(N)"):

					dictValue = dictValue.replace(key, f"{value}")
					pvValue = dictValue.replace("$(R)", "twoTheta:")
					dictKey = dictKey.replace("$(R)", "")
					pvKey = dictKey.replace(key, "")
					self.epics_pvs[pvKey] = PV(pvValue)

				elif isinstance(value, list) and dictValue.endswith("$(N)"):

					for n in value:

						dictValue = dictValue.replace("$(P)", "MS:")
						pvValue = dictValue.replace(key, f"{n}")

						dictKey = dictKey.replace("$(P)", "")
						pvKey = dictKey.replace(key, f"{n}")

						self.data_pvs[pvKey] = PV(pvValue)
				else:
					continue

	def checkConnectedPVs(self):

		allPVsConnected = True
		for key in self.epics_pvs:
			if self.epics_pvs[key].get() is None:
				CLIMessage(f"PV {self.epics_pvs[key].pvname} is not connected", "E")
				log.error(f"PV {self.epics_pvs[key].pvname} is not connected")
				allPVsConnected = False
			else:
				CLIMessage(f"PV {self.epics_pvs[key].pvname} is connected", "I")

		return allPVsConnected

	def startScan(self):

		log.info("Start the scan")

	def detectorInit(self):

		self.epics_pvs["detdatapath"].put(1) #ImgPath /home/det/images
		self.epics_pvs["NImages"].put(1) #NImages 1
		self.epics_pvs["detexptime"].put(1)

	def preCheck(self):

		for n in range(1, self.epics_pvs["Intervals"].get() + 1):
			self.check((self.data_pvs[f"EndPoint{n}"].get() >= self.data_pvs[f"StartPoint{n}"].get()),f"end angle{n} must be greater than start angle{n}")
			self.check((self.data_pvs[f"StepSize{n}"].get() > 0 and self.data_pvs[f"StepSize{n}"].get() <= self.data_pvs[f"EndPoint{n}"].get()),f"invalid angle step size{n}")
			self.check((self.data_pvs[f"StartPoint{n}"].get() >= 5 and self.data_pvs[f"EndPoint{n}"].get() <=90),f"angle{n} out of range")
		
		# self.check((self.pvs["current"].get() > 1 and self.pvs["energy"].get() > 2.49),"No Beam avaiable")
		# self.check((self.pvs["shutter"].get() == 3),"Photon shutter is closed")
		# self.check((self.motors["spinner"].done_moving == 0),"spinner motor is not rotating")

	def check(self,exp,msg,eval=False):

		if exp == eval:
			log.warning(msg)

			while True:
				reply = UIMessage("", msg, "Do you want to continue?(Y/N)\n").showYNQuestion()
				if reply:
					return
				else:
					sys.exit()
