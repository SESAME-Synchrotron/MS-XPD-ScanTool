from SEDSS.SEDSupplements import CLIMessage
from SEDSS.SEDSupport import readFile
from MSDataWriter import MSDataWriter
from PIL import Image 
import numpy as np 
import glob 
import os
import re
import log 
import ntpath

import matplotlib.pyplot as plt
import matplotlib.animation as animation


class slitsOperations: 

	def __init__(self, imgFullPath, tTheta, metadata): 

		"""
		This class does the follwoing: 
		- reads configration file 
		- initiate some parameters 
		- read the image collected from detector 
		- calls the function that calculates 2ϴ on the detector 
		- calls the function that calculates the intinsity avrage of the slites on the detector 
		"""
		self.metadata = metadata
		#CLIMessage("{}".format(self.metadata))
		path, fileName = ntpath.split(imgFullPath) # extract image file name and path
		log.info("Initalizing slitsOperations class for image: {}".format(fileName))
		self.imgFullPath = imgFullPath # image full path 
		self.tTheta = tTheta # 2ϴ
		scanToolconfigFile = self.metadata["ScanToolCFGFile"]
		self.configFile = readFile(scanToolconfigFile).readJSON() # reading conigration file
		self.XAxisRange = self.configFile["slitsConfigration"]["XAxisRange"] # range value on x axis of the detector 
		self.X = self.configFile["slitsConfigration"]["X"] # Center of the Slit on X axis  
		self.Y = self.configFile["slitsConfigration"]["Y"] # Slits positions on Y axis 
		self.data = {}

		self.slitsPixelIntinisty = []
		self.slitsPixelIntinistyAvr = 0
		self.twoThetaOnSlit = 0 
		
		log.info("Local image path: {}".format(self.imgFullPath))

		try: 
			self.readImage()
			#self.initPlotting()
			self.calc2ThetaSlitIntinsity()
		except:
			log.error("unable to read or handel the image: {}".format(self.imgFullPath))
			log.warning("one image has been ignored!!")
			CLIMessage("Unable to collect image from the source or handling it!!", "E")
			pass

	def initPlotting(self):
		plt.ion() 
		self.fig = plt.figure()
		self.ax1 = self.fig.add_subplot(1,1,1)
		self.line1 = self.ax1.plot(self.twoThetaOnSlit, self.slitsPixelIntinistyAvr)

	def readImage(self):
		log.info("Reading the image ...")
		im=Image.open(self.imgFullPath)
		#CLIMessage ("{}".format(im), "I")
		#CLIMessage("Image format : {}".format(im.format), "I")
		#CLIMessage ("Image size: {}".format(im.mode), "I")
		log.info("Converting image to nparray")
		self.imageArray = np.asarray(im, dtype=np.int32)
		log.info("Deleting the raw image")
		try: 
			os.remove(self.imgFullPath)
		except:
			CLIMessage("unable to delete the raw image {}".format(imgFullPath), "W")
		"""
		image dimintions: 487x619 (x,y)
		after converting to nparray it is 619x487 (y,x)
		the detector is rotated 90 degrees (y,x)
		"""
		log.info("Slit X position: {}, X Range: {}-{}".format(self.X, self.X - self.XAxisRange,
			self.X + self.XAxisRange))
	
	def calc2ThetaSlitIntinsity(self): 
		"""
		This method calcultes: 
		- the two theta on the detector 
		- the avrage intinsity of a givien slit
		"""
		self.data = {}
		for i in range(len(self.Y)):
			self.slitsPixelIntinisty = []
			for j in range((self.X - self.XAxisRange), (self.X + self.XAxisRange)+1): # range starts from (-x to x )
				self.slitsPixelIntinisty.append(self.imageArray[j, self.Y[i]])
			self.slitsPixelIntinistyAvr = sum(self.slitsPixelIntinisty)/len(self.slitsPixelIntinisty)
			self.twoThetaOnSlit = self.tTheta + (3.170 - (self.Y[i] * 0.0133))
			
			self.data["slitID"] = i 
			self.data["slitYPosition"] 			= self.Y[i]
			self.data["slitXPosition"] 			= self.X
			self.data["slitXRange"] 			= self.XAxisRange
			self.data["twoThetaOnSlit"] 		= self.twoThetaOnSlit
			self.data["slitsPixelIntinistyAvr"] = self.slitsPixelIntinistyAvr
			log.info("Writing collected data in the experimental file.")

			#self.set_xdata(self.twoThetaOnSlit)
			#self.set_ydata(self.slitsPixelIntinistyAvr)
			#self.fig.canvas.draw()
			#self.fig.canvas.flush_events()




			MSDataWriter(self.data, self.metadata)

			log.info("SlitID#: {}, Y position: {},"\
			 " Slit pixels intinsity: {}, pixels intinsity averege: {}, 2ϴ on slit: {}".
			format(i, self.Y[i],self.slitsPixelIntinisty, self.slitsPixelIntinistyAvr, self.twoThetaOnSlit))