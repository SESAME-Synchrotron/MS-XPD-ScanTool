#!/usr/local/bin/python3.9

import argparse
import sys
import os
import time
import decimal
import json

import log 
from SEDSS.SEDSupplements import CLIMessage, CLIInputReq
from SEDSS.SEDSupport import readFile, dataTransfer, timeModule 

from datetime import datetime

try:
	import epics
except ImportError as error:
	CLIMessage("Please ensure that the following packages are installed properly", "W")
	CLIMessage("pyepics")
	sys.exit()

class XRD:
	def __init__(self):
		self.clear()
		log.setup_custom_logger("./SED_MS_Scantool.log")
		log.info("Start scanning tool")

		self.expname = "xrd_{}".format(datetime.now().strftime("%Y-%m-%d--%H-%M-%S"))
		log.info("Experiment name: ".format(self.expname))

		self.parser = argparse.ArgumentParser(description="2theta-step is a DAQ script for MS beamline used to do step scanning for 2theta with pialtus 300k detector ")
		self.parser.add_argument('-start', 		type=float, default=10.0,        	help='2theta start angle (degree)')
		self.parser.add_argument('-end',   		type=float, default=11.0,			help='2theta end angle (degree)')
		self.parser.add_argument('-size',  		type=float, default=1.0,        	help='2theta angle step size (degree)')
		self.parser.add_argument('-exp',		type=float, default=1.0,        	help='exposure time (seconds)')
		self.parser.add_argument('-name',  		type=str,   default=self.expname,	help='experiment  name')
		self.parser.add_argument('-exptype',  	type=str,   default="local",		help='experiment  type (local,users)')
		self.parser.add_argument('-proposal',	type=int,	default=99999999,		help='experiment  proposal number')      

		self.args = self.parser.parse_args()

		self.start		= self.args.start
		self.end		= self.args.end
		self.stepsize	= self.args.size
		self.exptime	= self.args.exp
		self.expname	= self.args.name
		self.exptype	= self.args.exptype
		self.proposal	= self.args.proposal

		##########################
		self.loadconfig()
		self.preCheck()
		self.initDir()
		self.detectorInit()
		self.scan()
		##########################
	
	def scan(self):
		#self.clear()
		log.info("Showing scan parameters to be confirmed before scan starts")

		print("\n")
		
		CLIMessage(" --> Experiment Parameters <-- ")
		CLIMessage("2theta | start angle: {}".format(self.start),"M")
		CLIMessage("2theta | stop angle: {}".format(self.end),"M")
		CLIMessage("2theta | angle step: {}".format(self.stepsize),"M")
		CLIMessage("Exposure time: {}".format(self.exptime),"M")
		CLIMessage("Experiment name: {}".format(self.expname),"M")
		CLIMessage("Experiment type: {}".format(self.exptype),"M")
		CLIMessage("experiment proposal number: {}".format(self.proposal),"M")
		CLIMessage("experimnet data path: {}".format(self.expdir), "M")
		print("\n")

		if CLIInputReq("Do you want to continue?(Y/N)").YNQuestion():
			log.info("Confirm starting the scan") 
			return
		else:
			log.worning("Decline starting the scan")
			sys.exit()

		try:
			self.scanpoints = self.drange(self.start,self.end,self.stepsize)
			for index,point in enumerate(self.scanpoints,start=1):
				for t in range(4): # Number of trials to get exactly to target position
					self.motors["2theta"].move(point) # move 2 theta (detector arm)
					time.sleep(0.5)
					while not self.motors["2theta"].done_moving:
						self.print("2theta moving {}".format(self.motors["2theta"].readback))

				current2theta = self.motors["2theta"].readback
				currentImgName = "{}_{}_{:.4f}.tiff".format(self.expname,index,current2theta)
				self.pvs["ImgName"].put(str(currentImgName)) # set Image Name
				self.pvs["isacq"].put(1) # disable temp measurment
				self.pvs["acq"].put(1)
				self.pvs["isacq"].put(0) # re-enable temp measurment

				# wait until acq completion
				for i in range(int(self.exptime*10+1)):
					print("acquiring {}: ".format(currentImgName)+"*"*i)
					sys.stdout.write("\033[F")
					time.sleep(0.1)
				sys.stdout.write("\033[K")

				self.tranfser() # transfer images from detector server(10.3.3.8) to ioc server(10.3.3.8) into samba sahre folder
				self.clear() # clear screen

			print("DONE !!!")
		except KeyboardInterrupt as kint:
			print("scan ended :(")
			sys.exit()

	def drange(self,start,stop,step,prec=10):
		decimal.getcontext().prec = prec
		points = []
		r= decimal.Decimal(start)
		step = decimal.Decimal(step)
		while r <=stop:
			points.append(float(r))
			r += step
		return points
	
	def loadconfig(self):
		filefd = open("configrations/2theta-Slits-Step.json","r")
		log.info("Load configrations from 2theta-Slits-Step.json file")
		cfgfile = json.load(filefd)
		pvlist = cfgfile["pv"]
		motorlist = cfgfile["motor"]
		paths = cfgfile["paths"]
		pcs = cfgfile["pc"]

		self.pvs = {}
		self.motors = {}
		self.paths = {}
		self.pcs = {}
		
		for entry,name in pvlist.items():
			PvObj = epics.PV(name)
			status = str(PvObj.get())
			if not status == 'None':
				CLIMessage ("The PV {} is connected".format(name), "I")
				self.pvs[entry] = PvObj
			else:
				CLIMessage ("The PV {} is not connected".format(name), "E")
				sys.exit()
		
		for entry,name in motorlist.items():
			PvObj = epics.Motor(name)
			if PvObj:
				CLIMessage ("The PV {} is connected".format(name), "I")
				self.motors[entry] = PvObj
			else:
				CLIMessage ("The PV {} is not connected".format(name), "E")
				sys.exit()
		
		for entry,path in paths.items():
			self.paths[entry] = path
		
		for entry,pc in pcs.items():
			self.pcs[entry] = pc
				
		filefd.close()

	def preCheck(self):
		log.info("Pre start and input parameters checking ...")
		self.check((self.end >= self.start),"end angle must be greater than start angle")
		self.check((self.stepsize > 0 and self.stepsize <= self.end),"invalid angle step size")
		self.check((self.exptime >0),"invalid exposure time")
		self.check((self.exptype in ["local", "users"]),"invalid experiment type (local, users)")
		self.check((len(str(self.proposal))== 8),"invalid proposal number")
		self.check((self.start >= 5 and self.end <=90),"angle out of range")
		self.check((self.pvs["current"].get() > 1 and self.pvs["energy"].get() > 2.49),"No Beam avaiable")
		self.check((self.pvs["shutter"].get() == 3),"Photon shutter is closed")
		self.check((self.motors["spinner"].done_moving == 0),"spinner motor is not rotating")

	def detectorInit(self):
		log.info("Detector initialization")
		self.pvs["detdatapath"].put(self.paths["detdatapath"]) #ImgPath /home/det/images
		self.pvs["NImages"].put(1) #NImages 1
		self.pvs["detexptime"].put(self.exptime)

	def print(self,*args):
		os.system("clear")
		print(*args)
		sys.stdout.write("\033[F")
	
	def tranfser(self):
		log.info("Transfering detector data to XXX")
		os.system("ssh -qt {}@{} 'rsync --remove-source-files -aqc {}@{}:{}/* {}' ".format(self.pcs["iocserver.user"],self.pcs["iocserver"],self.pcs["pilatusserver.user"],self.pcs["pilatusserver"],self.paths["detdatapath"],self.expdir))

	def initDir(self):
		lt = time.localtime()
		exptime = "{}-{}-{}".format(lt[3],lt[4],lt[5])
		if self.exptype == "local":
			self.expdir = "{}/{}/{}/{}/{}/{}/{}".format(self.paths["datapath"], self.exptype, lt[0],lt[1],lt[2],self.expname,exptime)
		elif self.exptype == "users":
			self.expdir = "{}/{}/{}/{}/{}/{}/{}/{}".format(self.paths["datapath"], self.exptype, str(self.proposal) ,lt[0],lt[1],lt[2],self.expname,exptime)

		result = os.system("ssh -qt {}@{} 'mkdir -p {}' ".format(self.pcs["iocserver.user"],self.pcs["iocserver"],self.expdir))
		if result !=0:
			raise Exception("Data Path init failed")

	def clear(self):
		os.system("clear")
	
	def check(self,exp,msg,eval=False):
		if exp == eval:
			CLIMessage("{}".format(msg), "E")
			while True:
				#reply = input("Do you want to continue?(Y/N)\n")
				reply = CLIInputReq("Do you want to continue?(Y/N)").YNQuestion()
				#if reply in ["y","n","Y","N"]:
				if reply:
					return
				else: 
					sys.exit()

if __name__ == '__main__':
	XRD()
