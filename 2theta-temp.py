#!/usr/bin/python3.4

import argparse
import sys
import os
import time
import decimal
import json
import math
import log

from datetime import datetime

floatingPointCompensation = 0.001

try:
	import epics
except ImportError as error:
	print("Please ensure that the following packages are installed properly:\n ")
	print("pyepics\n")
	sys.exit()

class XRD:
	def __init__(self):
		self.expname = "xrd_{}".format(datetime.now().strftime("%Y-%m-%d--%H-%M-%S"))
		#self.rootpath = os.path.dirname(__file__)
		self.rootpath = "/home/control/XRD-Scan"
		log.setup_custom_logger("./xrd_scan_SED_Scantool.log")
		log.info("Start scanning tool")
		self.parser = argparse.ArgumentParser(description="2theta-temp is a DAQ script for MS beamline used to do step scanning for 2theta with pialtus 300k detector with tempreture control using Gas Blower ")
		self.parser.add_argument('-start', 		type=float, default=10.0,        	help='2theta start angle (degree)')
		self.parser.add_argument('-end',   		type=float, default=90.0,			help='2theta end angle (degree)')
		self.parser.add_argument('-size',  		type=float, default=5.0,        	help='2theta angle step size (degree)')
		self.parser.add_argument('-exp',		type=float, default=5.0,        	help='exposure time (seconds)')
		self.parser.add_argument('-name',  		type=str,   default=self.expname,	help='experiment  name')
		self.parser.add_argument('-exptype',  	type=str,   default="local",		help='experiment  type (local,users)')
		self.parser.add_argument('-proposal',	type=int,	default=99999999,		help='experiment  proposal number')     
		self.parser.add_argument('-temp',       type=str,   default="",             help='comma seperated temperture steps ')
		self.parser.add_argument('-wait',       type=str,   default="",             help='comma seperated wait intervals after reaching target temperture')
		self.parser.add_argument('-Nscans',     type=str,   default="",				help='comma seperated number of scans for each tempreture point')      
		self.parser.add_argument('-deadband',   type=float, default=0.1,			help='temperature deadband')      

		self.args = self.parser.parse_args()

		self.start		= self.args.start
		self.end		= self.args.end
		self.stepsize	= self.args.size
		self.exptime	= self.args.exp
		self.expname	= self.args.name
		self.exptype	= self.args.exptype
		self.proposal	= self.args.proposal
		self.deadband 	= self.args.deadband + floatingPointCompensation ## to ignore floating point issue.. 



		self.clear()

		##########################
		self.parseTemp()
		self.loadconfig()
		self.prechech()
		self.initDir()
		self.detectorInit()
		self.scan()
		##########################

	def scan(self):
		self.clear()

		print("\n")
		print("#######################")
		print("#Experiment Parameters#")
		print("#######################")
		print("\n")
		print("2theta start angle (degree) :",self.start)
		print("2theta end angle (degree) :",self.end)
		print("2theta angle step size (degree) :",self.stepsize)
		print("exposure time (seconds) :",self.exptime)
		print("experiment name :",self.expname)
		print("experiment type (local,users) :",self.exptype)
		print("experiment proposal number :",self.proposal)
		print("temperture steps:",self.temp_steps_raw)
		print("wait steps :",self.wait_steps_raw)
		print("\n")

		print("scan will start in 3 seconds ...")
		time.sleep(3)
		try:
			self.scanpoints = self.drange(self.start,self.end,self.stepsize)
			for temp,wait,nscan in zip(self.temp_steps,self.wait_steps,self.Nscans):
				
				self.pvs["temp_sp"].put(temp)
				while math.fabs(self.pvs["temp_rb"].get()-temp)>=self.deadband:
					time.sleep(0.1)
					self.print("sample temperture {}".format(self.pvs["temp_rb"].get()))
				
				print("wait {} seconds after sample reached target tempreture".format(wait))

				for scan in range(1,nscan+1):
					time.sleep(wait)
					for index,point in enumerate(self.scanpoints,start=1):
						for p in range(4): # Number of trials to get exactly to target position
							self.motors["2theta"].move(point) # move 2 theta (detector arm)
							time.sleep(0.5)
							while not self.motors["2theta"].done_moving:
								self.print("2theta moving {}".format(self.motors["2theta"].readback))

						current2theta = self.motors["2theta"].readback
						currentImgName = "{}_{:.4f}_{}_{}.tiff".format(self.expname,current2theta,temp,scan)
						try: 
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
						except:
							print("PROPLEM happend acquiring image from detector")
							log.error("PROPLEM happend acquiring image from detector")
							log.error("temp: {}".format(temp))
							log.error("nscan: {}".format(nscan))
							log.error("current2theta: {}".format(current2theta))
							log.error("currentImgName: {}".format(currentImgName))
							pass 
						try: 
							self.tranfser() # transfer images from detector server(10.3.3.8) to ioc server(10.3.3.8) into samba sahre folder
							self.clear() # clear screen
						except:
							print("PROPLEM happend tranfsering image from IOC or detector!!")
							log.error("PROPLEM happend tranfsering image from IOC or detector!!")
							log.error("temp: {}".format(temp))
							log.error("nscan: {}".format(nscan))
							log.error("current2theta: {}".format(current2theta))
							log.error("currentImgName: {}".format(currentImgName))
							pass
					

			print("DONE !!!")
			log.info("End scanning tool")
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
		print("+++++++++++++++++++++++", self.rootpath)
		filefd = open(self.rootpath+"/2theta-temp.json","r")
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
				print("{} : Connected".format(name))
				self.pvs[entry] = PvObj
			else:
				print("{} : is not connected\n".format(name))
				sys.exit()
		
		for entry,name in motorlist.items():
			PvObj = epics.Motor(name)
			if PvObj:
				print("{} : Connected".format(name))
				self.motors[entry] = PvObj
			else:
				print("{} : is not connected\n".format(name))
				sys.exit()
		
		for entry,path in paths.items():
			self.paths[entry] = path
		
		for entry,pc in pcs.items():
			self.pcs[entry] = pc
				
		filefd.close()

	def prechech(self):
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
		self.pvs["detdatapath"].put(self.paths["detdatapath"]) #ImgPath /home/det/images
		self.pvs["NImages"].put(1) #NImages 1
		self.pvs["detexptime"].put(self.exptime)

	def print(self,*args):
		os.system("clear")
		print(*args)
		sys.stdout.write("\033[F")
	
	def tranfser(self):
		os.system("ssh -qt {}@{} 'rsync --remove-source-files -aqc {}@{}:{}/* {}' ".format(self.pcs["iocserver.user"],self.pcs["iocserver"],self.pcs["pilatusserver.user"],self.pcs["pilatusserver"],self.paths["detdatapath"],self.expdir))

	def initDir(self):
		lt = time.localtime()
		exptime = "{}-{}-{}".format(lt[3],lt[4],lt[5])
		if self.exptype == "local":
			self.expdir = "{}/{}/{}/{}/{}/{}/{}".format(self.paths["datapath"], self.exptype, lt[0],lt[1],lt[2],self.expname,exptime)
		elif self.exptype == "users":
			self.expdir = "{}/{}/{}/{}/{}/{}/{}/{}".format(self.paths["datapath"], self.exptype, str(self.proposal) ,lt[0],lt[1],lt[2],self.expname,exptime)

		print("experimnet data path: ",self.expdir)
		result = os.system("ssh -qt {}@{} 'mkdir -p {}' ".format(self.pcs["iocserver.user"],self.pcs["iocserver"],self.expdir))
		if result !=0:
			raise Exception("Data Path init failed")

	def clear(self):
		os.system("clear")
	
	def check(self,exp,msg,eval=False):
		if exp == eval:
			print(msg)
			while True:
				reply = input("Do you want to continue?(Y/N)\n")
				if reply in ["y","n","Y","N"]:
					reply = str(reply).lower()                
					if reply =='y':
						return
					elif reply == "n":
						sys.exit()
	def isfloat(self,fval):
		try:
			return True,float(fval)
		except:
			return False,None
	
	def isInt(self,ival):
		try:
			return True,int(ival)
		except:
			return False,None
	
	def parseTemp(self):
		self.temp_steps_raw = self.args.temp.split(",")
		self.wait_steps_raw = self.args.wait.split(",")
		self.Nscans_raw		= self.args.Nscans.split(",")

		self.temp_steps	=	[]
		self.wait_steps	=	[]
		self.Nscans		=	[]

		self.check((len(self.temp_steps_raw)==len(self.wait_steps_raw)==len(self.Nscans_raw)),"temperture , wait or Nscans  number mismatch")

		for temp,wait,Nscan in zip(self.temp_steps_raw,self.wait_steps_raw,self.Nscans_raw):		
			if self.isfloat(temp)[0]:
				self.temp_steps.append(float(temp))
			else:
				raise Exception('invalid temperture input')
			
			if self.isfloat(wait)[0]:
				self.wait_steps.append(float(wait))
			else:
				raise Exception('invalid wait input')

			if self.isInt(Nscan)[0]:
				self.Nscans.append(int(Nscan))
			else:
				raise Exception('invalid Nscan input')
if __name__ == '__main__':
	XRD()
