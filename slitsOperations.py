from SEDSS.SEDSupplements import CLIMessage
from PIL import Image 
import numpy as np 
import glob 
import os
import re
import log 


class slitsOperations: 

	def __init__(self, imgPath, tTheta): 

		self.imgPath = imgPath
		self.tTheta = tTheta
		log.info("TEST")
		
		CLIMessage("Looking for tiff image in this path {}".format(self.imgPath), "I")
		self.readImage()

	def readImage(self):

		# Sort the list of files that includes numbers 
		#self.listImages = sorted( glob.glob(self.sourceDataPath + "/*.tiff")) 
		#self.listImages.sort(key=lambda f: int(re.sub('\D', '', f)))

		CLIMessage("Opening the file: {}".format(filename), "I")
		im=Image.open(filename)
		print (im)

		"""
		the follwoing pice of code reads the tiff images and does the follwoing: 

		-	select the intigration row based on the pre-defined user input (intPixPos)
		-	calculate two theta on detector 
		- 	calculate two theta arm 
		- 	call the function that writes the data 
		"""

		#for filename in self.listImages: 
		#	CLIMessage("Opening the file: {}".format(filename), "I")
		#	im=Image.open(filename)
		#	print (im)
		#	print("Image format : {}".format(im.format))
		#	print("Image size: {}".format(im.size))
		#	print ("Image size: {}".format(im.mode))
		#	self.imageArray = np.asarray(im, dtype=np.int32)
		#	CLIMessage("Converting image to array....","W")
		#	for xx in range(400): 
		#		for yy in range(400): 
		#			print(self.imageArray[xx,yy])
		#	print("Image array size: {}".format(self.imageArray.shape))
		#	print ("Integrating at pixel: {}".format(self.intPixPos))
		#	CLIMessage("Applying ROI selection....","W")
		#	self.intRow = self.imageArray[self.intPixPos,self.ROIS:self.ROIE] # integration row 
		#	self.indexArray = np.arange(self.ROIS, self.ROIE) 
		#	print ("Integration row size after applying ROI: {}".format(self.intRow.size))
		#	self.twoThetaOnDetector = (3.170 - np.multiply(self.indexArray, 0.0133))
		#	self.twoThetaArm = self.twoThetaOnDetector + self.tTheta
		#	self.tTheta = self.tTheta + self.stepSize
		#	#self.writeData(filename)
		#	CLIMessage("the image {} has been successfully processed".format(filename), "I")
		#	print ("############################################\n")
		#	break

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
