import epics 
import os
import time
from SEDSS.SEDSupplements import CLIMessage
import fileinput
import sys

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



		self.generateDataFileName()

	def generateDataFileName(self):
		"""
		this method does the follwoing: 
		- generats the file name 
		"""
		self.fullFileName = self.expDir +"/" + self.experimentName + "_Slit" + str(self.slitID) + "_" + self.creationTime + ".dat"
		#print (self.fullFileName)
		self.createDataFile()
		self.expDataDumping()

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
		f.write("{:.6f}     {:.6f}   \n".format(float(self.twoThetaOnSlit), float(self.slitsPixelIntinistyAvr) ))
		f.close()






	
	def createICKFXDIFile(self): # Create IC, Ketek and FICUS xdi file 

		if not os.path.exists(self.fullFileName): 
			f = open (self.fullFileName, "w")
			f.write("# XDI/1.0 SED_XAFS/0.9\n")
			f.write("# Column.1: energy eV\n")
			f.write("# Column.2: I0\n")
			f.write("# Column.3: Itrans\n")
			f.write("# Column.4: Irefer\n")
			f.write("# Column.5: mutrans (log(I0/Itrans))\n")
			f.write("# Column.6: murefer (log(Itrans/Irefer))\n")
			f.write("# Column.7: KETEK-Ifluor\n")
			f.write("# Column.8: KETEK-mufluor\n")
			f.write("# Column.9: KETEK-ROI_0[c/s]\n")
			f.write("# Column.10: KETEK-ROI_1[c/s]\n")
			f.write("# Column.11: KETEK-ROI_2[c/s]\n")
			f.write("# Column.12: KETEK-e-time[sec]\n")
			f.write("# Column.13: KETEK-DEADTIME[%]\n")
			f.write("# Column.14: KETEK-INT_TIME[sec]\n")
			f.write("# Column.15: KETEK-OCR\n")
			f.write("# Column.16: KETEK-ICR\n")
			f.write("# Column.17: FICUS-Ifluor\n")
			f.write("# Column.18: FICUS-mufluor\n")
			f.write("# Column.19: FICUS-ROI_0[c/s]\n")
			f.write("# Column.20: FICUS-ROI_1[c/s]\n")
			f.write("# Column.21: FICUS-ROI_2[c/s]\n")
			f.write("# Column.22: FICUS-e-time[sec]\n")
			f.write("# Column.23: FICUS-DEADTIME[%]\n")
			f.write("# Column.24: FICUS-INT_TIME[sec]\n")
			f.write("# Base.file_name: {}\n".format(self.fileName))
			f.write("# Element.edge: {}\n".format(self.edge))
			f.write("# Mono.name: {}\n".format(self.Mono))
			f.write("# Mono.d_spacing: {}\n".format(self.d_spacing))
			f.write("# Mono.settling_time: {}\n".format(self.settlingTime))
			f.write("# Beamline.name: XAFS/XRF Beamline (08-BM)\n")
			f.write("# Beamline.collimation: slits\n")
			f.write("# Beamline.focusing: no\n")
			f.write("# Beamline.harmonic_rejection: mirror coating VCM: {}, VFM: {}\n".format(self.vcm, self.vfm))
			f.write("# Facility.name: SESAME Synchrotron-light\n")
			f.write("# Facility.energy: 2.50 GeV\n")
			f.write("# Facility.current: {}\n".format(self.RINGCurrent))
			f.write("# Facility.xray_source: SESAME Bending Magnet\n")
			f.write("# Scan.start_time: {}\n".format(str(self.expStartTimeDF) ))
			f.write("# Scan.end_time: xxx\n")
			f.write("# Scan.edge_energy: {}\n".format(self.energy))
			f.write("# Scan.number: {}/{} -- intervals: {}, samples: {}\n".format(self.scanNum, self.numScans, self.numIntervals, self.numSamples))
			f.write("# Detector.IC1: 15cm  {}\n".format(self.IC1GasMix))
			f.write("# Detector.IC2: 30cm  {}\n".format(self.IC2GasMix))
			f.write("# Detector.IC3: 15cm  {}\n".format(self.IC3GasMix))
			f.write("# Detector.flour: KETEK\n")
			f.write("# Detector.flour: FICUS\n")
			f.write("# Element.symbol: {}\n".format(self.sampleName))
			f.write("# Sample.stoichiometry: {}\n".format(self.stoichiometry))
			f.write("# Sample.prep: {}\n".format(self.samplePrep))
			f.write("# ///\n")
			f.write("# Experiment comments and remarks: {}\n".format(self.expCom))
			f.write("# User comments and remarks: {}\n".format(self.userCom))
			f.write("#----\n")
			f.write("#(1)energy   (2)I0   (3)Itrans   (4)Irefer   (5)mutrans   (6)murefer   (7)KETEK-Ifluor   (8)KETEK-mufluor   (9)KETEK-ROI_0[c/s]   (10)KETEK-ROI_1[c/s]   (11)KETEK-ROI_2[c/s]   (12)KETEK-e-time[sec]   (13)KETEK-DEADTIME[%]   (14)KETEK-INT_TIME[sec]   (15)KETEK-OCR   (16)KETEK-ICR"\
				"   (17)FICUS-Ifluor   (18)FICUS-mufluor   (19)FICUS-ROI_0[c/s]   (20)FICUS-ROI_1[c/s]   (21)FICUS-ROI_2[c/s]   (22)FICUS-e-time[sec]   (23)FICUS-DEADTIME[%]   (24)FICUS-INT_TIME[sec]\n")
			f.close()

	def fillICKFDataTable(self): # Fill IC, Ketek and FICUS collected data. 
		f = open (self.fullFileName, "a")
		f.write("%10.6e  %10.6e  %10.6e  %10.6e  %10.6e  %10.6e  %10.6e  %10.6e  %10.6e  %10.6e  %10.6e  %10.6e  %10.6e  %10.6e  %10.6e  %10.6e  %10.6e  %10.6e  %10.6e  %10.6e  %10.6e  %10.6e  %10.6e  %10.6e \n" 
		%(float(self.data["ENERGY-RBK"]), float(self.data["IC1[V]"]), float(self.data["IC2[V]"]), float(self.data["IC3[V]"]), 
			float(self.data["TRANS"]), float(self.data["TransRef"]), float(self.data["KETEK-If"]), float(self.data["KETEK-FLUOR"]), float(self.data["KETEK-ROI_0[c/s]"]), float(self.data["KETEK-ROI_1[c/s]"]), float(self.data["KETEK-ROI_2[c/s]"]),
			float(self.data["KETEK-e-time[sec]"]), float(self.data["KETEK-DEADTIME[%]"]),
			float(self.data["KETEK-INT_TIME[sec]"]), float(self.data["KETEK-OCR"]), float(self.data["KETEK-ICR"]),
			float(self.data["FICUS-If"]), float(self.data["FICUS-FLUOR"]), float(self.data["FICUS-ROI_0[c/s]"]), float(self.data["FICUS-ROI_1[c/s]"]), float(self.data["FICUS-ROI_2[c/s]"]),
			float(self.data["FICUS-e-time[sec]"]), float(self.data["FICUS-DEADTIME[%]"]), float(self.data["FICUS-INT_TIME[sec]"])  ))
		f.close()

	def createICKXDIFile(self):
		
		if not os.path.exists(self.fullFileName): 
			f = open (self.fullFileName, "w")
			f.write("# XDI/1.0 SED_XAFS/0.9\n")
			f.write("# Column.1: energy eV\n")
			f.write("# Column.2: I0\n")
			f.write("# Column.3: Itrans\n")
			f.write("# Column.4: Irefer\n")
			f.write("# Column.5: mutrans (log(I0/Itrans))\n")
			f.write("# Column.6: murefer (log(Itrans/Irefer))\n")
			f.write("# Column.7: KETEK-Ifluor\n")
			f.write("# Column.8: KETEK-mufluor\n")
			f.write("# Column.9: KETEK-ROI_0[c/s]\n")
			f.write("# Column.10: KETEK-ROI_1[c/s]\n")
			f.write("# Column.11: KETEK-ROI_2[c/s]\n")
			f.write("# Column.12: KETEK-e-time[sec]\n")
			f.write("# Column.13: KETEK-DEADTIME[%]\n")
			f.write("# Column.14: KETEK-INT_TIME[sec]\n")
			f.write("# Column.15: KETEK-OCR\n")
			f.write("# Column.16: KETEK-ICR\n")
			f.write("# Base.file_name: {}\n".format(self.fileName))
			f.write("# Element.edge: {}\n".format(self.edge))
			f.write("# Mono.name: {}\n".format(self.Mono))
			f.write("# Mono.d_spacing: {}\n".format(self.d_spacing))
			f.write("# Mono.settling_time: {}\n".format(self.settlingTime))
			f.write("# Beamline.name: XAFS/XRF Beamline (08-BM)\n")
			f.write("# Beamline.collimation: slits\n")
			f.write("# Beamline.focusing: no\n")
			f.write("# Beamline.harmonic_rejection: mirror coating VCM: {}, VFM: {}\n".format(self.vcm, self.vfm))
			f.write("# Facility.name: SESAME Synchrotron-light\n")
			f.write("# Facility.energy: 2.50 GeV\n")
			f.write("# Facility.current: {}\n".format(self.RINGCurrent))
			f.write("# Facility.xray_source: SESAME Bending Magnet\n")
			f.write("# Scan.start_time: {}\n".format(str(self.expStartTimeDF) ))
			f.write("# Scan.end_time: xxx\n")
			f.write("# Scan.edge_energy: {}\n".format(self.energy))
			f.write("# Scan.number: {}/{} -- intervals: {}, samples: {}\n".format(self.scanNum, self.numScans, self.numIntervals, self.numSamples))
			f.write("# Detector.IC1: 15cm  {}\n".format(self.IC1GasMix))
			f.write("# Detector.IC2: 30cm  {}\n".format(self.IC2GasMix))
			f.write("# Detector.IC3: 15cm  {}\n".format(self.IC3GasMix))
			f.write("# Detector.flour: KETEK\n")
			f.write("# Element.symbol: {}\n".format(self.sampleName))
			f.write("# Sample.stoichiometry: {}\n".format(self.stoichiometry))
			f.write("# Sample.prep: {}\n".format(self.samplePrep))
			f.write("# ///\n")
			f.write("# Experiment comments and remarks: {}\n".format(self.expCom))
			f.write("# User comments and remarks: {}\n".format(self.userCom))
			f.write("#----\n")
			f.write("#(1)energy   (2)I0   (3)Itrans   (4)Irefer   (5)mutrans   (6)murefer   (7)KETEK-Ifluor   (8)KETEK-mufluor   (9)KETEK-ROI_0[c/s]   (10)KETEK-ROI_1[c/s]   (11)KETEK-ROI_2[c/s]   (12)KETEK-e-time[sec]   (13)KETEK-DEADTIME[%]   (14)KETEK-INT_TIME[sec]   (15)KETEK-OCR   (16)KETEK-ICR\n")
			f.close()

	def fillICKDataTable(self):
		f = open (self.fullFileName, "a")
		f.write("%10.6e  %10.6e  %10.6e  %10.6e  %10.6e  %10.6e  %10.6e  %10.6e  %10.6e  %10.6e  %10.6e  %10.6e  %10.6e  %10.6e  %10.6e  %10.6e \n" 
		%(float(self.data["ENERGY-RBK"]), float(self.data["IC1[V]"]), float(self.data["IC2[V]"]), float(self.data["IC3[V]"]), 
			float(self.data["TRANS"]), float(self.data["TransRef"]), float(self.data["KETEK-If"]), float(self.data["KETEK-FLUOR"]), float(self.data["KETEK-ROI_0[c/s]"]), float(self.data["KETEK-ROI_1[c/s]"]), float(self.data["KETEK-ROI_2[c/s]"]),
			float(self.data["KETEK-e-time[sec]"]), float(self.data["KETEK-DEADTIME[%]"]),
			float(self.data["KETEK-INT_TIME[sec]"]), float(self.data["KETEK-OCR"]), float(self.data["KETEK-ICR"])))
		f.close()

	def createICXDIFile(self):
		
		if not os.path.exists(self.fullFileName): 
			f = open (self.fullFileName, "w")
			f.write("# XDI/1.0 SED_XAFS/0.9\n")
			f.write("# Column.1: energy eV\n")
			f.write("# Column.2: I0\n")
			f.write("# Column.3: Itrans\n")
			f.write("# Column.4: Irefer\n")
			f.write("# Column.5: mutrans (log(I0/Itrans))\n")
			f.write("# Column.6: murefer (log(Itrans/Irefer))\n")
			f.write("# Base.file_name: {}\n".format(self.fileName))
			f.write("# Element.edge: {}\n".format(self.edge))
			f.write("# Mono.name: {}\n".format(self.Mono))
			f.write("# Mono.d_spacing: {}\n".format(self.d_spacing))
			f.write("# Mono.settling_time: {}\n".format(self.settlingTime))
			f.write("# Beamline.name: XAFS/XRF Beamline (08-BM)\n")
			f.write("# Beamline.collimation: slits\n")
			f.write("# Beamline.focusing: no\n")
			f.write("# Beamline.harmonic_rejection: mirror coating VCM: {}, VFM: {}\n".format(self.vcm, self.vfm))
			f.write("# Facility.name: SESAME Synchrotron-light\n")
			f.write("# Facility.energy: 2.50 GeV\n")
			f.write("# Facility.current: {}\n".format(self.RINGCurrent))
			f.write("# Facility.xray_source: SESAME Bending Magnet\n")
			f.write("# Scan.start_time: {}\n".format(str(self.expStartTimeDF) ))
			f.write("# Scan.end_time: xxx\n")
			f.write("# Scan.edge_energy: {}\n".format(self.energy))
			f.write("# Scan.number: {}/{} -- intervals: {}, samples: {}\n".format(self.scanNum, self.numScans, self.numIntervals, self.numSamples))
			f.write("# Detector.IC1: 15cm  {}\n".format(self.IC1GasMix))
			f.write("# Detector.IC2: 30cm  {}\n".format(self.IC2GasMix))
			f.write("# Detector.IC3: 15cm  {}\n".format(self.IC3GasMix))
			f.write("# Element.symbol: {}\n".format(self.sampleName))
			f.write("# Sample.stoichiometry: {}\n".format(self.stoichiometry))
			f.write("# Sample.prep: {}\n".format(self.samplePrep))
			f.write("# ///\n")
			f.write("# Experiment comments and remarks: {}\n".format(self.expCom))
			f.write("# User comments and remarks: {}\n".format(self.userCom))
			f.write("#----\n")
			f.write("#(1)energy   (2)I0   (3)Itrans   (4)Irefer   (5)mutrans   (6)murefer\n")
			f.close()


	def fillICDataTable(self):
		f = open (self.fullFileName, "a")
		f.write("%10.6e  %10.6e  %10.6e  %10.6e  %10.6e  %10.6e \n" 
		%(float(self.data["ENERGY-RBK"]), float(self.data["IC1[V]"]), float(self.data["IC2[V]"]), float(self.data["IC3[V]"]), 
			float(self.data["TRANS"]), float(self.data["TransRef"])))
		f.close()


	def createICFXDIFile(self): 
		if not os.path.exists(self.fullFileName): 
			f = open (self.fullFileName, "w")
			f.write("# XDI/1.0 SED_XAFS/0.9\n")
			f.write("# Column.1: energy eV\n")
			f.write("# Column.2: I0\n")
			f.write("# Column.3: Itrans\n")
			f.write("# Column.4: Irefer\n")
			f.write("# Column.5: mutrans (log(I0/Itrans))\n")
			f.write("# Column.6: murefer (log(Itrans/Irefer))\n")
			f.write("# Column.7: FICUS-Ifluor\n")
			f.write("# Column.8: FICUS-mufluor\n")
			f.write("# Column.9: FICUS-ROI_0[c/s]\n")
			f.write("# Column.10: FICUS-ROI_1[c/s]\n")
			f.write("# Column.11: FICUS-ROI_2[c/s]\n")
			f.write("# Column.12: FICUS-e-time[sec]\n")
			f.write("# Column.13: FICUS-DEADTIME[%]\n")
			f.write("# Column.14: FICUS-INT_TIME[sec]\n")
			f.write("# Base.file_name: {}\n".format(self.fileName))
			f.write("# Element.edge: {}\n".format(self.edge))
			f.write("# Mono.name: {}\n".format(self.Mono))
			f.write("# Mono.d_spacing: {}\n".format(self.d_spacing))
			f.write("# Mono.settling_time: {}\n".format(self.settlingTime))
			f.write("# Beamline.name: XAFS/XRF Beamline (08-BM)\n")
			f.write("# Beamline.collimation: slits\n")
			f.write("# Beamline.focusing: no\n")
			f.write("# Beamline.harmonic_rejection: mirror coating VCM: {}, VFM: {}\n".format(self.vcm, self.vfm))
			f.write("# Facility.name: SESAME Synchrotron-light\n")
			f.write("# Facility.energy: 2.50 GeV\n")
			f.write("# Facility.current: {}\n".format(self.RINGCurrent))
			f.write("# Facility.xray_source: SESAME Bending Magnet\n")
			f.write("# Scan.start_time: {}\n".format(str(self.expStartTimeDF) ))
			f.write("# Scan.end_time: xxx\n")
			f.write("# Scan.edge_energy: {}\n".format(self.energy))
			f.write("# Scan.number: {}/{} -- intervals: {}, samples: {}\n".format(self.scanNum, self.numScans, self.numIntervals, self.numSamples))
			f.write("# Detector.IC1: 15cm  {}\n".format(self.IC1GasMix))
			f.write("# Detector.IC2: 30cm  {}\n".format(self.IC2GasMix))
			f.write("# Detector.IC3: 15cm  {}\n".format(self.IC3GasMix))
			f.write("# Detector.flour: FICUS\n")
			f.write("# Element.symbol: {}\n".format(self.sampleName))
			f.write("# Sample.stoichiometry: {}\n".format(self.stoichiometry))
			f.write("# Sample.prep: {}\n".format(self.samplePrep))
			f.write("# ///\n")
			f.write("# Experiment comments and remarks: {}\n".format(self.expCom))
			f.write("# User comments and remarks: {}\n".format(self.userCom))
			f.write("#----\n")
			f.write("#(1)energy   (2)I0   (3)Itrans   (4)Irefer   (5)mutrans   (6)murefer   "\
				"(7)FICUS-Ifluor   (8)FICUS-mufluor (9)FICUS-ROI_0[c/s]   (10)FICUS-ROI_1[c/s]   (11)FICUS-ROI_2[c/s]   "\
				"(12)FICUS-e-time[sec]   (13)FICUS-DEADTIME[%]   (14)FICUS-INT_TIME[sec]\n")
			f.close()

	def fillICFDataTable(self): # create IC KETEk xdi data file 
		f = open (self.fullFileName, "a")
		f.write("%10.6e  %10.6e  %10.6e  %10.6e  %10.6e  %10.6e  %10.6e  %10.6e  %10.6e  %10.6e  %10.6e  %10.6e  %10.6e  %10.6e \n" 
		%(float(self.data["ENERGY-RBK"]), float(self.data["IC1[V]"]), float(self.data["IC2[V]"]), float(self.data["IC3[V]"]), 
			float(self.data["TRANS"]), float(self.data["TransRef"]), 
			float(self.data["FICUS-If"]), float(self.data["FICUS-FLUOR"]), float(self.data["FICUS-ROI_0[c/s]"]), float(self.data["FICUS-ROI_1[c/s]"]), float(self.data["FICUS-ROI_2[c/s]"]),
			float(self.data["FICUS-e-time[sec]"]), float(self.data["FICUS-DEADTIME[%]"]), float(self.data["FICUS-INT_TIME[sec]"]) ))
		f.close()

	def onClose(self): 
		#f = open (self.fullFileName, "a")
		scanEndTime = "Scan.end_time: {}".format(str(time.strftime("%Y-%m-%dT%H:%M:%S")) )
		for line in fileinput.input(self.fullFileName, inplace=1):
			line = line.replace("Scan.end_time: xxx", scanEndTime)
			sys.stdout.write(line)