import epics 
import os
import time
from SEDSS.SEDSupplements import CLIMessage
import fileinput
import sys
import numpy
import csv 

from matplotlib import pyplot as plt
import matplotlib.animation as animation
from matplotlib import style

class MSDataWriter: 
	"""
	rawData: raw data recevied from the scanning tool
	filePath: file path 
	fileName: file name 
	detChosen: a list contains the detector chosen. 
	expStartTime: Experiment start data and time to be part of the file name 
	"""
	def __init__(self, data, metadata ): 
		self.data 				 = data
		self.metadata 			 = metadata
		self.thetaAvailableFlage = 0
		self.IC01Flag			 = 0


		############ Meta Data collection from metadata dic ############

		self.creationTime 			= self.metadata["creationTime"]
		self.scanToolCFGFilePath 	= self.metadata["ScanToolCFGFile"]
		self.expStartAngle 			= self.metadata["expStartAngle"]
		self.expEndAngle 			= self.metadata["expEndAngle"]
		self.angleStepSize			= self.metadata["angleStepSize"]
		self.exposureTime			= self.metadata["exposureTime"]
		self.experimentType			= self.metadata["experimentType"]
		try:
			self.proposalNumber			= self.metadata["proposalNumber"]
		except:
			pass
		self.experimentName			= self.metadata["experimentName"]
		self.ringCurrent			= self.metadata["current"]
		self.machineEnergy			= self.metadata["energy"]
		self.expDir 				= self.metadata["expDir"]
		self.IDGap					= self.metadata["IDGap"]

		############ Data extraction from data dic ############

		self.slitID 				= self.data["slitID"]
		self.twoThetaOnSlit 		= self.data["twoThetaOnSlit"]
		self.slitsPixelIntinistyAvr = self.data["slitsPixelIntinistyAvr"]
		self.slitYPosition			= self.data["slitYPosition"]
		self.slitXPosition			= self.data["slitXPosition"]
		self.slitXRange 			= self.data["slitXRange"]
		try: 
			self.theta 				= self.data["theta"]
			self.thetaAvailableFlage= 1
		except: 
			pass 

		try: 
			self.IC01RBV 			= self.metadata["IC01RBV"]
			self.IC01Flag			= 1
		except: 
			pass 


		self.dataWriter()

	def dataWriter(self):
		"""
		this method does the follwoing: 
		- generat the data file 
		- dumps data and metadata in the data file
		- writes the data for ploting  
		"""
		self.fullFileName = self.expDir +"/" + self.experimentName + "_Slit" + str(self.slitID) + "_" + self.creationTime + ".dat"
		#print (self.fullFileName)
		self.createDataFile()
		self.expDataDumping()
		self.writePlottingData()

	def createDataFile (self):
		if not os.path.exists(self.fullFileName): 
			f = open(self.fullFileName, "w")
			f.write("# Experiment.name: {}\n".format(self.experimentName))
			f.write("# Experiment.type: {}\n".format(self.experimentType))
			try:
				f.write("# Experiment.proposal_number: {}\n".format(self.proposalNumber))
			except:
				pass 
			f.write("# Scan.start_time: {}\n".format(str(self.creationTime)))
			f.write("# Scan.start_angle: {}\n".format(str(self.expStartAngle)))
			f.write("# Scan.step_size: {}\n".format(str(self.angleStepSize)))
			f.write("# Scan.end_angle: {}\n".format(str(self.expEndAngle)))
			f.write("# Scan.exposure_time: {}\n".format(str(self.exposureTime)))
			f.write("# Scan.slit_id: {}\n".format(str(self.slitID)))
			f.write("# Scan.slit_Yposition: {}\n".format(str(self.slitYPosition)))
			f.write("# Scan.slit_Xposition: {}\n".format(str(self.slitXPosition)))
			f.write("# Scan.slit_XRange: {}\n".format(str(self.slitXRange)))

			f.write("# Detector: Pilatus 300K\n")
			f.write("# Facility.name: SESAME Synchrotron-light\n")
			f.write("# Facility.energy: 2.50 GeV\n")
			f.write("# Facility.current: {}\n".format(self.ringCurrent))
			f.write("# ID.Gap: {}\n".format(self.IDGap))
			f.write("# Beamline.name: MS Beamline (09-ID)\n")
			f.write("#-------------------------------\n")
			if self.thetaAvailableFlage == 1:
				if self.IC01Flag == 1:
					f.write("#(1)2theta(2ϴ)   (2)theta   (3)Intensity   (4)IC_ReadOut\n")
				else:
					f.write("#(1)2theta(2ϴ)   (2)theta   (3)Intensity\n")
			else:
				if self.IC01Flag == 1:
					f.write("#(1)2theta(2ϴ)   (2)Intensity   (3)IC_ReadOut\n")
				else:
					f.write("#(1)2theta(2ϴ)   (2)Intensity\n")
			f.close()
	
	def expDataDumping(self):
		f = open (self.fullFileName, "a")
		#f.write("%10.6e     %10.6e   \n" %(float(self.twoThetaOnSlit), float(self.slitsPixelIntinistyAvr), ))
		if self.thetaAvailableFlage == 1:
			if self.IC01Flag == 1: 
				f.write("{:.6f}         {:.6f}         {:.2f}         {:.6f}   \n".format(float(self.twoThetaOnSlit), float(self.theta), float(self.slitsPixelIntinistyAvr), float(self.metadata["IC01RBV"]) ))
			else:
				f.write("{:.6f}         {:.6f}         {:.2f}   \n".format(float(self.twoThetaOnSlit), float(self.theta), float(self.slitsPixelIntinistyAvr) ))
		else:
			if self.IC01Flag == 1: 
				f.write("{:.6f}         {:.2f}         {:.6f}   \n".format(float(self.twoThetaOnSlit), float(self.slitsPixelIntinistyAvr), float(self.metadata["IC01RBV"]) ))
			else: 
				f.write("{:.6f}         {:.2f}   \n".format(float(self.twoThetaOnSlit), float(self.slitsPixelIntinistyAvr) ))
		f.close()

	def onClose(self): 
		#f = open (self.fullFileName, "a")
		scanEndTime = "Scan.end_time: {}".format(str(time.strftime("%Y-%m-%dT%H:%M:%S")) )
		for line in fileinput.input(self.fullFileName, inplace=1):
			line = line.replace("Scan.end_time: xxx", scanEndTime)
			sys.stdout.write(line)

	def writePlottingData(self):
		"""
		This method writes 2ϴ and intensity in csv file 
		to make them available for plotting.
		"""
		fieldnames = ["twoTheta", "Intensity"]
		if not os.path.exists("plottingData.csv"):
			with open ("plottingData.csv", "w") as csv_file: 
				csv_writer = csv.DictWriter(csv_file, fieldnames = fieldnames)
				csv_writer.writeheader()

		with open("plottingData.csv", "a") as csv_file: 
			csv_writer = csv.DictWriter(csv_file, fieldnames=fieldnames)
			data = {
					"twoTheta":self.twoThetaOnSlit, 
					"Intensity": self.slitsPixelIntinistyAvr
					}
			# if self.thetaAvailableFlage == 1: 
			# 	data = {
			# 		"twoTheta":self.twoThetaOnSlit, 
			# 		"Intensity": self.slitsPixelIntinistyAvr
			# 		}

			# 	data = {
			# 		"twoTheta":self.theta, 
			# 		"Intensity": self.slitsPixelIntinistyAvr
			# 		}
			# else:
			# 	data = {
			# 		"twoTheta":self.twoThetaOnSlit, 
			# 		"Intensity": self.slitsPixelIntinistyAvr
			# 		}

			csv_writer.writerow(data)
