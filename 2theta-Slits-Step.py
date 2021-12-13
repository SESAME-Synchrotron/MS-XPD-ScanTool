#!/opt/SW/venv/bin/python

import argparse
import sys
import os
import time
import decimal
import json
import shutil
import signal
import threading 
from tqdm import tqdm
import numpy

import log 
from SEDSS.SEDSupplements import CLIMessage, CLIInputReq
from SEDSS.SEDSupport import readFile, dataTransfer, timeModule 
from slitsOperations import slitsOperations

from datetime import datetime
import datetime

from matplotlib import pyplot as plt
from matplotlib.ticker import MaxNLocator

import matplotlib.animation as animation
from matplotlib import style

from multiprocessing import Process

try:
	import epics
except ImportError as error:
	CLIMessage("Please ensure that the following packages are installed properly", "W")
	CLIMessage("pyepics")
	sys.exit()

class XRD:
	def __init__(self):
		self.clear()
		# Set ^C interrupt to abort the scan
		signal.signal(signal.SIGINT, self.signal_handler)
		self.expCFG = {} # exp. configrations dic 
		self.metadata = {} # exp. metadata dic 
		self.creationTime = str(time.strftime("%Y%m%dT%H%M%S"))
		self.metadata["creationTime"] = self.creationTime

		log.setup_custom_logger("./SED_MS_Scantool.log")
		log.info("Start scanning tool")
		self.ScanToolCFGFile = "configrations/2theta-Slits-Step.json" # 2ϴ Slits config file 
		self.metadata["ScanToolCFGFile"] = self.ScanToolCFGFile
		self.expname = "xrd_{}".format(self.creationTime)

		self.parser = argparse.ArgumentParser(description="2theta-step is a DAQ script for MS beamline used to do step scanning for 2theta with pialtus 300k detector ")
		self.parser.add_argument('-start', 		type=float, default=10.0,        	help='2theta start angle (degree)')
		self.parser.add_argument('-end',   		type=float, default=11.0,			help='2theta end angle (degree)')
		self.parser.add_argument('-size',  		type=float, default=1.0,        	help='2theta angle step size (degree)')
		self.parser.add_argument('-exp',		type=float, default=1.0,        	help='exposure time (seconds)')
		self.parser.add_argument('-expTitle',  	type=str,   default="XXXX",			help='Experiment  name')
		#self.parser.add_argument('-name',  		type=str,  	help='Experiment  name')
		self.parser.add_argument('-exptype',  	type=str,   default="local",		help='Experiment  type (local,users)')
		self.parser.add_argument('-proposal',	type=int,	default=99999999,		help='Experiment  proposal number')      

		self.args = self.parser.parse_args()

		self.start		= 	self.args.start
		self.end		= 	self.args.end
		self.stepsize	= 	self.args.size
		self.exptime	= 	self.args.exp
		self.expname	= 	self.args.expTitle
		self.exptype	= 	self.args.exptype
		self.proposal	= 	self.args.proposal

		log.info("Experiment name: {}".format(self.expname))

		#self.startTime = str(time.strftime("%Y%m%dT%H%M%S"))

		##########################
		"""
		The order here is important 
		"""
		self.loadconfig()
		self.preCheck()
		self.initDir()
		self.createDir() # creates exp directory and update the self.expdir with errror handiling
		self.detectorInit()
		self.writeExpCFGFile() # this method writes the exp. configration file 
		self.collectExtraMetadata() # a method to collects metadata 
		self.initPlotting()
		self.scan()
		##########################
	def initPlotting(self):
		"""
		deleting ploting data files in order to let MSDataWriter create new ones 
		"""
		try:
			os.remove("intensity.txt")
			os.remove("twoTheta.txt")
		except:
			pass
		#plotingProcess = Process(target=self.dataPlotting)
		#plotingProcess.daemon = True
		#plotingProcess.start()

		#plt.figure()
		#plt.rcParams["figure.figsize"] = [7.00, 3.50]
		#plt.rcParams["figure.autolayout"] = True
		#plt.margins(x=0, y=0)
		#plt.gca().xaxis.set_major_locator(MaxNLocator(prune='lower'))
		#plt.gca().yaxis.set_major_locator(MaxNLocator(prune='lower'))
		#plt.ion()
		#plt.show()
		
		N=int((self.end - self.start)/self.stepsize) * 3
		#CLIMessage("{}".format(N), "W")
		#plt.xticks(range(N)) # add loads of ticks
		#plt.grid()
		#plt.gca().margins(x=0)
		#plt.gcf().canvas.draw()
		#tl = plt.gca().get_xticklabels()
		#maxsize = max([t.get_window_extent().width for t in tl])
		#m = 0.2 # inch margin
		#s = maxsize/plt.gcf().dpi*N+2*m
		#margin = m/plt.gcf().get_size_inches()[0]
		#plt.gcf().subplots_adjust(left=margin, right=1.-margin)
		#plt.gcf().set_size_inches(s, plt.gcf().get_size_inches()[1])
		#plt.ion()
		#plt.show()

		self.xdata = []
		self.ydata = []
		plt.show()
		self.axes = plt.gca()
		self.axes.set_xlim(0, N)
		self.axes.set_ylim(-50, +500)
		self.line, = self.axes.plot(self.xdata, self.ydata, 'r-')





	def scan(self):
		#self.clear()
		log.info("Showing scan parameters to be confirmed before scan starts")
		startTime = time.time()
		self.metadata["startTime"] = startTime

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
			#return
		else:
			log.warning("Decline starting the scan")
			sys.exit()

		try:
			self.scanpoints = self.drange(self.start,self.end,self.stepsize)
			for index,point in enumerate(self.scanpoints,start=1):
				CLIMessage("Mvoing to step index number {} for step value {}".format(index, point), "I")
				self.motors["2theta"].move(point, wait=True) # move 2 theta (detector arm)
				CLIMessage("2ϴ encoder readout: {}".format(self.motors["2theta"].readback), "I")
				
				
				#for t in range(4): # Number of trials to get exactly to target position
				#	self.motors["2theta"].move(point, wait=True) # move 2 theta (detector arm)
				#	while not self.motors["2theta"].done_moving:
				#		CLIMessage("2theta moving {}".format(self.motors["2theta"].readback), "IG")
				#time.sleep(0.2)
				current2theta = self.motors["2theta"].readback
				currentImgName = "{}_{}_{:.4f}.tiff".format(self.expname,index,current2theta)
				self.pvs["ImgName"].put(str(currentImgName)) # set Image Name
				self.pvs["isacq"].put(1) # disable temp measurment
				self.pvs["acq"].put(1)
				self.pvs["isacq"].put(0) # re-enable temp measurment
				log.info("Collecting image \"{}\" from detector (camserver)".format(currentImgName))

				for i in tqdm(range(int(self.exptime*10+1)), desc = "Collecting image {}: ".format(currentImgName),
					ascii=False, ncols=100):
					time.sleep(0.1)

				self.tranfser() # transfer images from detector server(10.3.3.8) to ioc server(10.3.3.8) into samba sahre folder
				#imgPath = self.paths["localTmpData"] + "/" + currentImgName
				imgPath = self.expdir + "/" + currentImgName
				
				slitsOperations(imgFullPath = imgPath,tTheta = current2theta, metadata=self.metadata)
				dataTransfer(self.expdir, self.paths["remoteDataServer"]).scp()
				#self.clear() # clear screen
				self.dataPlotting()


			self.scanTime = timeModule.timer(startTime)
			shutil.move("SED_MS_Scantool.log", self.expdir+"/"+"SED_MS_Scantool.log")
			dataTransfer(self.expdir, self.paths["remoteDataServer"]).scp()
			print ("###########################################################")
			CLIMessage("Scan is finished !!", "I")
			CLIMessage("Actual scan time is: {} hours".format(self.scanTime), "I")
			print ("###########################################################")
			input("Press [enter] to continue.")

		except KeyboardInterrupt as kint:
			CLIMessage("Scan has been interubted by user input", "E")
			sys.exit()
	
	def dataPlotting(self):

		intensity = open("intensity.txt", "r")
		intensity = numpy.array (intensity.readlines())
		
		twoTheta = open("twoTheta.txt", "r")
		twoTheta = numpy.array (twoTheta.readlines())

		for i in range(len(twoTheta)): 
			#append(lists[i].rstrip('\n').split(','))
			self.xdata.append(twoTheta[i].rstrip('\n').split(','))
			self.ydata.append(intensity[i].rstrip('\n').split(','))
			print(self.xdata)
			print(self.ydata)
			self.line.set_xdata(self.xdata)
			self.line.set_ydata(self.ydata)
			plt.draw()
			plt.pause(1e-17)
			time.sleep(0.1)

		#CLIMessage("{}---{}".format(twoTheta, intensity))

		#self.xdata.append(twoTheta)
		#self.ydata.append(intensity)
		

		os.remove("intensity.txt")
		os.remove("twoTheta.txt")

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

		filefd = open(self.ScanToolCFGFile,"r")
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

		# write the scan parameters to experimient confige file. 
		self.metadata["expStartAngle"]	= 	self.expCFG["start"] 			= self.start
		self.metadata["expEndAngle"]	= 	self.expCFG["end"] 				= self.end
		self.metadata["angleStepSize"] 	= 	self.expCFG["stepSize"] 		= self.stepsize
		self.metadata["exposureTime"] 	= 	self.expCFG["exposureTime"] 	= self.exptime
		self.metadata["experimentType"]	=	self.expCFG["experimentType"] 	= self.exptype
		self.metadata["proposalNumber"] =	self.expCFG["proposal"] 		= self.proposal
		self.metadata["experimentName"] =	self.expCFG["expName"] 			= self.expname

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
		try: 
			os.system("rsync --remove-source-files -aqc {}@{}:{}/* {} ".format(
				self.pcs["pilatusserver.user"],self.pcs["pilatusserver"],
				self.paths["detdatapath"],self.expdir))
		except: 
			time.sleep(1)
			os.system("rsync --remove-source-files -aqc {}@{}:{}/* {} ".format(
				self.pcs["pilatusserver.user"],self.pcs["pilatusserver"],
				self.paths["detdatapath"],self.expdir))


	def initDir(self):
		if self.exptype == "local":
			self.expdir = "{}".format(self.paths["localTmpData"])
		elif self.exptype == "users":
			self.expdir = "{}".format(self.paths["localTmpData"])

	def createDir(self):
		"""
		This method:
		- cteats the experimint directory
		- updates the expiriment directory
		"""
		expDir = self.expdir + "/" + self.expname + "_" +self.creationTime
		try: 
			os.mkdir(expDir)
			self.expdir = expDir
			self.metadata["expDir"] = self.expdir
		except OSError as error: 
			CLIMessage("{}".format(error), "E")
			sys.exit()

	def writeExpCFGFile(self):
		self.exCFGFile = self.expdir + "/" + self.expname + "_config_" + self.creationTime + ".cfg"

		with open(self.exCFGFile,'w') as cfgfile:
			json.dump(self.expCFG,cfgfile)
			cfgfile.close()

	def collectExtraMetadata(self): 
		self.metadata["current"] = self.pvs["current"].get()
		self.metadata["energy"] = self.pvs["energy"].get()
		#self.metadata["expBaseName"] = self.expname

	def signal_handler(self, sig, frame):
		"""Calls abort_scan when ^C is typed"""
		if sig == signal.SIGINT:
			log.warning("Ctrl + C (^C) has been pressed, runinig scan is terminated !!")
			#os.rename("SED_Scantool.log", "SEDScanTool_{}.log".format(self.creationTime))
			shutil.move("SED_MS_Scantool.log", self.expdir+"/"+"SED_MS_Scantool.log")
			dataTransfer(self.expdir, self.paths["remoteDataServer"]).scp()
			sys.exit()

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

	def runPauseMonitor(self):
		log.info("start pause trigger monitor") 
		PauseMonitorThread = threading.Thread(target=self.pauseTrigger, args=(), daemon=True)
		PauseMonitorThread.start()


if __name__ == '__main__':
	XRD()
