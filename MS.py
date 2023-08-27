#!/usr/bin/python3.9

import sys
import log
import time 
import decimal

from epics import PV, Motor
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

		for pv_file in self.PVsFiles:
			self.readPVsFile(pv_file)

		# if self.checkConnectedPVs():
		# 	pass
		# else:
		# 	CLIMessage("The scanning tool will not continue, please check the non connected PVs", "E")
		# 	log.error("The The scanning tool will not continue, some PVs are not connected")
		# 	sys.exit()
		
		if self.epics_pvs["TestingMode"].get():
			log.warning("Testing mode")
			self.preCheck()
			
		if self.epics_pvs["CancelScan"].get():
			CLIMessage("Scan has been cancelled \n", "IO")
			log.warning("Scan has been cancelled")
			sys.exit()
			
		while not self.epics_pvs["StartScan"].get():
			CLIMessage("Press Finish to start the scan", "IO")
			time.sleep(0.2)

		# self.detectorInit()
		self.startScan()

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
			if self.epics_pvs[key].get() is None:
				CLIMessage(f"PV {self.epics_pvs[key].pvname} is not connected", "E")
				log.error(f"PV {self.epics_pvs[key].pvname} is not connected")
				allPVsConnected = False
			else:
				CLIMessage(f"PV {self.epics_pvs[key].pvname} is connected", "I")

		return allPVsConnected

	def startScan(self):

		log.info("Start the scan")

		self.scanpoints = self.drange(self.data_pvs["StartPoint1"].get(),self.data_pvs["EndPoint1"].get(),self.data_pvs["StepSize1"].get())
		print(self.scanpoints)
		for index,point in enumerate(self.scanpoints,start=1):
			for t in range(4): # Number of trials to get exactly to target position
				self.epics_motors["TwoTheta"].move(point) # move 2 theta (detector arm)
				time.sleep(0.5)
				# while not self.epics_motors["TwoTheta"].done_moving:
				# 	CLIMessage(f"2theta moving {self.epics_motors['TwoTheta'].readback}", "IO")

			current2theta = self.epics_motors["TwoTheta"].readback
			currentImgName = f"{self.epics_pvs['ExperimentalFileName']}_{index}_{current2theta:.4f}.tiff"
			# self.epics_pvs["ImageName"].put(str(currentImgName)) # set Image Name
			# self.epics_pvs["isAcquiring"].put(1) # disable temp measurment
			# self.epics_pvs["Acquiring"].put(1)
			# self.epics_pvs["isAcquiring"].put(0) # re-enable temp measurment

	def drange(self,start,stop,step,prec=10):
		decimal.getcontext().prec = prec
		points = []
		r= decimal.Decimal(start)
		step = decimal.Decimal(step)
		while r <=stop:
			points.append(float(r))
			r += step
		return points
	
	def detectorInit(self):

		self.epics_pvs["DetDataPath"].put(1) #ImgPath /home/det/images
		self.epics_pvs["NImages"].put(1) #NImages 1
		self.epics_pvs["DetExpTime"].put(1)

	def preCheck(self):
		pass
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

	def initDir(self):

		lt = time.localtime()
		exptime = f"{lt[3]}-{lt[4]}-{lt[5]}"

		if self.epics_pvs["ExperimentType"] == "Local":
			self.expdir = f"{self.epics_pvs['DataPath']}/{self.epics_pvs['ExperimentType']}/{lt[0]}/{lt[1]}/{lt[2]}/{self.epics_pvs['ExperimentalFileName']}/{exptime}"
		elif self.epics_pvs["ExperimentType"] == "Users":
			self.expdir = f"{self.epics_pvs['DataPath']}/{self.epics_pvs['ExperimentType']}/{self.epics_pvs['proposalID']}/{lt[0]}/{lt[1]}/{lt[2]}/{self.epics_pvs['ExperimentalFileName']}/{exptime}""{}/{}/{}/{}/{}/{}/{}/{}"

		CLIMessage(f"experimnet data path: {self.expdir}", "I")
		# print("ssh -qt {}@{} 'mkdir -p {}' ".format(self.pcs["iocserver.user"],self.pcs["iocserver"],self.expdir))
		# result = os.system("ssh -qt {}@{} 'mkdir -p {}' ".format(self.pcs["iocserver.user"],self.pcs["iocserver"],self.expdir))
		# if result !=0:
		# 	raise Exception("Data Path init failed")
