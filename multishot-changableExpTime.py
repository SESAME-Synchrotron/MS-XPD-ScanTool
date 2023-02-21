#!/usr/bin/python3.4

import argparse
import sys
import os
import time
import decimal
import json

from datetime import datetime
from decimal import Decimal

try:
	import epics
except ImportError as error:
	print("Please ensure that the following packages are installed properly:\n ")
	print("pyepics\n")
	sys.exit()

class XRD:
	def __init__(self):
		self.rootpath = os.getcwd()
		
		self.parser = argparse.ArgumentParser(description="multi_shot.py is a DAQ script for acquiring multi image from pialtus 300k detector over diffrent exposure times")
		self.parser.add_argument('-name', 		type=str, 	   				help='Scan name')
		self.parser.add_argument('-angle', 		type=float, 				help='2theta angle (degree)')
		self.parser.add_argument('-N',			type=int, 	default=1,	    help='Number of images to be collected')
		self.parser.add_argument('-exp',		type=float, default=1.0,    help='Initial exposure time (seconds)')
		self.parser.add_argument('-expInc',		type=float, default=0.1,    help='Exposure time increment size')


		self.args 	 	= self.parser.parse_args()
		self.name 		= self.args.name
		self.angle 	 	= self.args.angle
		self.numImages	= self.args.N
		self.expTime 	= self.args.exp
		self.expInc	 	= self.args.expInc

		
		self.clear()

		print("\n")
		print("#######################")
		print("#Experiment Parameters#")
		print("#######################")
		print("\n")
		print("exposure time (seconds) :",self.expTime)
		print("angle :",self.angle)


		print("\n")

		##########################
		self.loadconfig()
		self.preCheck()
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
		self.expname = "IMG_{}_E{}_N{}.tiff".format(datetime.now().strftime("%H%M%S.%f"), str(self.expTime), str(0))
		self.pvs["ImgName"].put(self.expname)

		for img in range(self.numImages):
			self.pvs["detexptime"].put(self.expTime)
			time.sleep(0.1) # give enough time to send the exp time
			self.pvs["acq"].put(1) # trigger tthe detector. 
			# wait until acq completion
			for i in range(int(self.pvs["detexptime"].get()*10+1)):
				print("acquiring {}: ".format(self.expname)+"*"*i)
				sys.stdout.write("\033[F")
				time.sleep(0.1) # 0.000001 is the minimum exp. time of the detector 
			sys.stdout.write("\033[K")
			self.transfer() # transfer images from detector server(10.3.3.8) to ioc server(10.3.3.12) into samba sahre folder
			nextExpTime = Decimal(self.expTime)+Decimal(self.expInc)
			self.expTime = "{:.6f}".format(float(nextExpTime))
			print(self.expTime)
			self.expname = "IMG_{}_E{}_N{}.tiff".format(datetime.now().strftime("%H%M%S.%f"), str(self.expTime), str(img+1))
			print (self.expname)
			self.pvs["ImgName"].put(self.expname)

		#self.clear() # clear screen

		print("DONE !!!")

	def loadconfig(self):
		filefd = open(self.rootpath+"/configrations/multi_shot.json","r")
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

	def preCheck(self):
		self.check((self.angle >0),"invalid 2theta angle")
		self.check((self.expTime >0),"invalid exposure time")
		self.check((self.expTime >0),"invalid exposure time")
		self.check((self.angle >= 5 and self.angle <=90),"angle out of range")
		self.check((self.pvs["current"].get() > 1 and self.pvs["energy"].get() > 2.49),"No Beam avaiable")
		self.check((self.pvs["shutter"].get() == 3),"Photon shutter is closed")

	def detectorInit(self):
		self.pvs["detdatapath"].put(self.paths["detdatapath"]) #ImgPath /home/det/images
		self.pvs["NImages"].put(1) #NImages 1
		#self.pvs["detexptime"].put(self.expTime)

	def print(self,*args):
		os.system("clear")
		print(*args)
		sys.stdout.write("\033[F")
	
	def transfer(self):
		self.expdir = "{}/{}".format(self.paths["datapath"],"preview")
		os.system("ssh -qt {}@{} 'rsync --remove-source-files -aqc {}@{}:{}/* {}/{}/' ".format(self.pcs["iocserver.user"],self.pcs["iocserver"],self.pcs["pilatusserver.user"],self.pcs["pilatusserver"],self.paths["detdatapath"],self.expdir,self.name))

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
