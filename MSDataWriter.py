import epics 
import os
import time
from SEDSS.SEDSupplements import CLIMessage
import fileinput
import sys
import numpy

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
		self.data = data
		self.metadata = metadata

		############ Meta Data collection from metadata dic ############

		self.creationTime 			= self.metadata["creationTime"]
		self.scanToolCFGFilePath 	= self.metadata["ScanToolCFGFile"]
		self.expStartAngle 			= self.metadata["expStartAngle"]
		self.expEndAngle 			= self.metadata["expEndAngle"]
		self.angleStepSize			= self.metadata["angleStepSize"]
		self.exposureTime			= self.metadata["exposureTime"]
		self.experimentType			= self.metadata["experimentType"]
		self.proposalNumber			= self.metadata["proposalNumber"]
		self.experimentName			= self.metadata["experimentName"]
		self.ringCurrent			= self.metadata["current"]
		self.machineEnergy			= self.metadata["energy"]
		self.expDir 				= self.metadata["expDir"]

		############ Data extraction from data dic ############

		self.slitID 				= self.data["slitID"]
		self.twoThetaOnSlit 		= self.data["twoThetaOnSlit"]
		self.slitsPixelIntinistyAvr = self.data["slitsPixelIntinistyAvr"]
		self.slitYPosition			= self.data["slitYPosition"]
		self.slitXPosition			= self.data["slitXPosition"]
		self.slitXRange 			= self.data["slitXRange"]

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
			f.write("# Experiment.proposal_number: {}\n".format(self.proposalNumber))
			f.write("# Scan.start_time: {}\n".format(str(self.creationTime)))
			f.write("# Scan.start_angle: {}\n".format(str(self.expStartAngle)))
			f.write("# Scan.step_size: {}\n".format(str(self.angleStepSize)))
			f.write("# Scan.end_angle: {}\n".format(str(self.expEndAngle)))
			f.write("# Scan.exposure_time: {}\n".format(str(self.exposureTime)))
			f.write("# Scan.slit_ID: {}\n".format(str(self.slitID)))
			f.write("# Scan.slit_Yposition: {}\n".format(str(self.slitYPosition)))
			f.write("# Scan.slit_Xposition: {}\n".format(str(self.slitXPosition)))
			f.write("# Scan.slit_XRange: {}\n".format(str(self.slitXRange)))

			f.write("# Detector: Pilatus 300K\n")
			f.write("# Facility.name: SESAME Synchrotron-light\n")
			f.write("# Facility.energy: 2.50 GeV\n")
			f.write("# Facility.current: {}\n".format(self.ringCurrent))
			f.write("# Beamline.name: MS Beamline (09-ID)\n")
			f.write("#-------------------------------\n")
			f.write("#(1)2theta(2ϴ)   (2)Intensity\n")
			f.close()
	
	def expDataDumping(self):
		f = open (self.fullFileName, "a")
		#f.write("%10.6e     %10.6e   \n" %(float(self.twoThetaOnSlit), float(self.slitsPixelIntinistyAvr), ))
		f.write("{:.6f}         {:.2f}   \n".format(float(self.twoThetaOnSlit), float(self.slitsPixelIntinistyAvr) ))
		f.close()

	def onClose(self): 
		#f = open (self.fullFileName, "a")
		scanEndTime = "Scan.end_time: {}".format(str(time.strftime("%Y-%m-%dT%H:%M:%S")) )
		for line in fileinput.input(self.fullFileName, inplace=1):
			line = line.replace("Scan.end_time: xxx", scanEndTime)
			sys.stdout.write(line)

	def writePlottingData(self):
		twoThetaPlottingDataFile = open("twoTheta.txt","a")
		twoThetaPlottingDataFile.write("{}\n".format(self.twoThetaOnSlit))
		intensityPlottingDataFile = open("intensity.txt","a")
		intensityPlottingDataFile.write("{}\n".format(self.slitsPixelIntinistyAvr))
		twoThetaPlottingDataFile.close()
		intensityPlottingDataFile.close()

		self.dataPlotting()

	def dataPlotting(self): 
		twoThetaPlottingDataFile = open("twoTheta.txt","r")
		intensityPlottingDataFile = open("intensity.txt","r")
		twoTheta = numpy.array (twoThetaPlottingDataFile.readlines())
		intensity = intensityPlottingDataFile.readlines()
		plt.cla()
		plt.plot(twoTheta, intensity)
		plt.draw()
		plt.pause(0.001)

		
