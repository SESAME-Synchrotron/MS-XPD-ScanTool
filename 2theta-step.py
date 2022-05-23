#!/usr/bin/python3.4

import argparse
import sys
import os
import time
import decimal
import json

from datetime import datetime

try:
	import epics
except ImportError as error:
	print("Please ensure that the following packages are installed properly:\n ")
	print("pyepics\n")
	sys.exit()

class XRD:
	def __init__(self):
		self.expname = "xrd_{}".format(datetime.now().strftime("%Y-%m-%d--%H-%M-%S"))

		self.parser = argparse.ArgumentParser(description="2theta-step is a DAQ script for MS beamline used to do step scanning for 2theta with pialtus 300k detector ")
		self.parser.add_argument('-start', 		type=float, default=10.0,        	help='2theta start angle (degree)')
		self.parser.add_argument('-end',   		type=float, default=90.0,			help='2theta end angle (degree)')
		self.parser.add_argument('-size',  		type=float, default=5.0,        	help='2theta angle step size (degree)')
		self.parser.add_argument('-exp',		type=float, default=5.0,        	help='exposure time (seconds)')
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

		self.clear()

		##########################
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
		print("\n")

		print("scan will start in 3 seconds ...")
		time.sleep(3)
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
		filefd = open("2theta-step.json","r")
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
		print("ssh -qt {}@{} 'mkdir -p {}' ".format(self.pcs["iocserver.user"],self.pcs["iocserver"],self.expdir))
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

if __name__ == '__main__':
	XRD()
