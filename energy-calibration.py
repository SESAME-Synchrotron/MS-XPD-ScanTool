#!/usr/bin/python3.4

import argparse
import sys
import os
import time
import decimal
import json
import csv

try:
	import epics
except ImportError as error:
	print("Please ensure that the following packages are installed properly:\n ")
	print("pyepics\n")
	sys.exit()

class Energy:
	def __init__(self):
		self.parser = argparse.ArgumentParser(description="Energy calibration script")
		self.parser.add_argument('-start', 		type=float, default=15,        	help='Energy start angle (KeV)')
		self.parser.add_argument('-end',   		type=float, default=16,			help='Energy end angle (KeV)')
		self.parser.add_argument('-size',  		type=float, default=1,        	help='Energy angle step size (KeV)')
	 

		self.args = self.parser.parse_args()

		self.start		= self.args.start
		self.end		= self.args.end
		self.stepsize	= self.args.size

		self.clear()

		##########################
		self.loadconfig()
		self.prechech()
		self.initDir()
		self.scan()
		##########################

	def scan(self):
		self.clear()

		print("\n")
		print("#######################")
		print("#Experiment Parameters#")
		print("#######################")
		print("\n")
		print("Energy start angle (degree) :",self.start)
		print("Energy end angle (degree) :",self.end)
		print("Energy angle step size (degree) :",self.stepsize)

		print("Data path: ",self.expdir)
		print("Filename: ",self.filename)
		print("Filepath: ",self.filepath)
		print("\n")

		print("scan will start in 3 seconds ...\n")
		time.sleep(3)
		try:
			self.scanpoints = self.drange(self.start,self.end,self.stepsize)
			for energy in self.scanpoints:
				self.pvs["energy_sp"].put(energy)
				time.sleep(5)
				while not (self.motors["theta"].done_moving and self.motors["Z"].done_moving or self.motors["Y"].done_moving):
					self.print("Energy moving: {}".format(self.pvs["energy_rb"].get()))
					time.sleep(2)
				
				print("Energy: {} | IC: {}".format(self.pvs["energy_rb"].get(),self.pvs["IcVoltage"].get()))

				self.writeDataPoint()
					
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
		filefd = open("enery-calibration.json","r")
		cfgfile = json.load(filefd)
		pvlist = cfgfile["pv"]
		paths = cfgfile["paths"]
		motorlist = cfgfile["motor"]

		self.pvs = {}
		self.paths = {}
		self.motors = {}
		
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
		
				
		filefd.close()

	def prechech(self):
		self.check((self.end >= self.start),"end angle must be greater than start angle")
		self.check((self.stepsize > 0 and self.stepsize <= self.end),"invalid angle step size")

	def print(self,*args):
		os.system("clear")
		print(*args)
		sys.stdout.write("\033[F")
	
	def initDir(self):
		lt = time.localtime()	
		self.expdir = "{}/{}/{}/{}".format(self.paths["datapath"], lt[0],lt[1],lt[2])

		os.makedirs(self.expdir,exist_ok=True)

		exptime = "{}-{}-{}".format(lt[3],lt[4],lt[5])
		self.filename = "energy-{}.csv".format(exptime)
		self.filepath = "{}/{}".format(self.expdir,self.filename)

		with open(self.filepath , "w") as datafile:
			writer = csv.DictWriter(datafile, fieldnames=["Energy[Kev]", "IC[VOLT]", "Theta[Deg]", "Z[mm]", "Y[mm]"])
			writer.writeheader()
			datafile.close()
	
	def writeDataPoint(self):
		dp = {}
		dp["Energy[Kev]"]	=	self.pvs["energy_rb"].get()
		dp["IC[VOLT]"]		=	self.pvs["IcVoltage"].get()
		dp["Theta[Deg]"]	=	self.motors["theta"].readback
		dp["Z[mm]"]			= 	self.motors["Z"].readback
		dp["Y[mm]"]			= 	self.motors["Y"].readback

		with open(self.filepath , "a") as datafile:
			writer = csv.DictWriter(datafile, fieldnames=["Energy[Kev]", "IC[VOLT]", "Theta[Deg]", "Z[mm]", "Y[mm]"])
			writer.writerow(dp)
			datafile.close()

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
	
if __name__ == '__main__':
	Energy()
