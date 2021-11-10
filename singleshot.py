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
		self.expname = "preview_{}.tiff".format(datetime.now().strftime("%Y-%m-%d--%H-%M-%S"))
		self.rootpath = os.getcwd()
		
		self.parser = argparse.ArgumentParser(description="singleshot is a DAQ script for taking single image frompialtus 300k detector")
		self.parser.add_argument('-angle', 		type=float, default=10.0,        	help='2theta angle (degree)')
		self.parser.add_argument('-exp',		type=float, default=5.0,        	help='exposure time (seconds)')

		self.args = self.parser.parse_args()
		self.angle = self.args.angle
		self.exptime	= self.args.exp
		
		self.clear()

		print("\n")
		print("#######################")
		print("#Experiment Parameters#")
		print("#######################")
		print("\n")
		print("exposure time (seconds) :",self.exptime)
		print("angle :",self.angle)


		print("\n")

		##########################
		self.loadconfig()
		self.prechech()
		self.detectorInit()
		self.scan()
		##########################
	
	def scan(self):
		for t in range(4):
			self.motors["2theta"].move(self.angle)
			time.sleep(0.5)
			while not self.motors["2theta"].done_moving:
				self.print("2theta moving {}".format(self.motors["2theta"].readback))
			
		current2theta = self.motors["2theta"].readback
		self.pvs["ImgName"].put(self.expname)
		self.pvs["acq"].put(1)
			
		# wait until acq completion
		for i in range(int(self.exptime*10+1)):
			print("acquiring {}: ".format(self.expname)+"*"*i)
			sys.stdout.write("\033[F")
			time.sleep(0.1)
		sys.stdout.write("\033[K")
		self.tranfser() # transfer images from detector server(10.3.3.8) to ioc server(10.3.3.8) into samba sahre folder
		self.clear() # clear screen

		print("DONE !!!")

	def loadconfig(self):
		filefd = open(self.rootpath+"/config.json","r")
		cfgfiel = json.load(filefd)
		pvlist = cfgfiel["pv"]
		motorlist = cfgfiel["motor"]
		paths = cfgfiel["paths"]
		pcs = cfgfiel["pc"]

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
			#status = str(PvObj)
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
		self.check((self.angle >0),"invalid 2theta angle")
		self.check((self.exptime >0),"invalid exposure time")
		self.check((self.exptime >0),"invalid exposure time")
		self.check((self.angle >= 5 and self.angle <=90),"angle out of range")
		self.check((self.pvs["current"].get() > 1 and self.pvs["energy"].get() > 2.49),"No Beam avaiable")
		self.check((self.pvs["shutter"].get() == 3),"Photon shutter is closed")

	def detectorInit(self):
		self.pvs["detdatapath"].put(self.paths["detdatapath"]) #ImgPath /home/det/images
		self.pvs["NImages"].put(1) #NImages 1
		self.pvs["detexptime"].put(self.exptime)

	def print(self,*args):
		os.system("clear")
		print(*args)
		sys.stdout.write("\033[F")
	
	def tranfser(self):
		self.expdir = "{}/{}".format(self.paths["datapath"],"preview")
		os.system("ssh -qt {}@{} 'rsync --remove-source-files -aqc {}@{}:{}/* {}' ".format(self.pcs["iocserver.user"],self.pcs["iocserver"],self.pcs["pilatusserver.user"],self.pcs["pilatusserver"],self.paths["detdatapath"],self.expdir))

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
