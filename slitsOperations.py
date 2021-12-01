from SEDSS.SEDSupplements import CLIMessage
from SEDSS.SEDSupport import readFile
from PIL import Image 
import numpy as np 
import glob 
import os
import re
import log 
import ntpath


class slitsOperations: 

	def __init__(self, imgPath, tTheta, configFile): 
		path, fileName = ntpath.split(imgPath)
		log.info("Initalizing slitsOperations class for image: {}".format(fileName))
		self.imgPath = imgPath
		self.tTheta = tTheta
		
		
		self.configFile = readFile(configFile).readJSON() 

		self.XAxisRange = self.configFile["slitsConfigration"]["XAxisRange"]
		self.X = self.configFile["slitsConfigration"]["X"]
		self.Y = self.configFile["slitsConfigration"]["Y"]
		#print ("Type Y", type(self.Y))
		#for i in range(len(self.Y)): 
		#	print (self.Y[i])
		self.slitsPixelIntinisty = []
		self.slitsPixelIntinistyAvr = 0

		
		CLIMessage("tiff image path {}".format(self.imgPath), "I")
		self.readImage()

	def readImage(self):

		CLIMessage("Opening the file: {}".format(self.imgPath), "I")
		log.info("Reading the image ...")
		im=Image.open(self.imgPath)
		CLIMessage ("{}".format(im), "I")
		CLIMessage("Image format : {}".format(im.format), "I")
		CLIMessage ("Image size: {}".format(im.mode), "I")
		log.info("Converting image to nparray")
		self.imageArray = np.asarray(im, dtype=np.int32)
		CLIMessage ("nparray shape: {}".format(self.imageArray.shape), "I")
		"""
		image dimintions: 487x619 (x,y)
		after converting to nparray it is 619x487 (y,x)
		the detector is rotated 90 degrees (y,x)
		"""
		log.info("Slit X position: {}, X Range: {}-{}".format(self.X, self.X - self.XAxisRange,
			self.X + self.XAxisRange))
		for i in range(len(self.Y)):
			self.slitsPixelIntinisty = []
			for j in range((self.X - self.XAxisRange), (self.X + self.XAxisRange)+1): # range starts from (-x to x )
				#print ("Y axis:",self.Y[i], " X axis:",j, " Pixel:",  self.imageArray[j, self.Y[i]])
				self.slitsPixelIntinisty.append(self.imageArray[j, self.Y[i]])

			self.slitsPixelIntinistyAvr = sum(self.slitsPixelIntinisty)/len(self.slitsPixelIntinisty)
			self.twoThetaOnSlit = self.tTheta + (3.170 - (self.Y[i] * 0.0133))
			log.info("SlitID#: {}, Y position: {},"\
			 " Slit pixels intinsity: {}, pixels intinsity averege: {}, 2ϴ on slit: {}".
			format(i, self.Y[i],self.slitsPixelIntinisty, self.slitsPixelIntinistyAvr, self.twoThetaOnSlit))





	def writeData(self, filename):
		"""
		this method does the follwoing: 
		-	put the two np arrays namely "two theta arm" and "pixels intincity (intRow)" into one np array.
		-	removes the sscientific representation of the numbers (i.e. e+02)
		-	write the data in .dat files.

		"""
		datFileName = filename.replace(".tiff", "")
		hearderText = "#2Theta, #Intinsity"
		data = np.array([self.twoThetaArm,self.intRow])
		np.set_printoptions(suppress=True)
		data = np.column_stack((data))
		# fmt='%f' is used to remove the scientific representation of the numbers
		np.savetxt(datFileName+".dat", data, delimiter=',', header = hearderText, fmt="%f")
