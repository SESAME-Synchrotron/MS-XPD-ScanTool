#!/usr/bin/python3.9
# **: for UI Visualization tool use

import log
import time
from datetime import datetime
import threading

from step import step
from emailNotifications import email
from SEDSS.CLIMessage import CLIMessage

class thetaTwoThetaStepSlits(step):
	def __init__(self, PVsFiles, macros, scanningSubs):
		super().__init__(PVsFiles, macros, scanningSubs)

		log.info(f"start {self.epics_pvs['ScanningType'].get(timeout=self.timeout, use_monitor=False, as_string=True)}")
		self.startScan()

	def startScan(self):
		"""
		Start Scan:
		- initialize directory for the sample
		- call scan() method
		"""

		super().startScan()

		self.epics_pvs["StartTime"].put(datetime.now().strftime("%H:%M:%S"), wait=True)		# **

		sampleName = self.epics_pvs["Sample"].get(as_string=True, timeout=self.timeout, use_monitor=False)
		sampleName = "sample" if sampleName.strip() == "" else sampleName
		self.epics_pvs["CurrentSample"].put(1, wait=True)			# **
		self.epics_pvs["SampleName"].put(sampleName, wait=True)		# **
		path = f"{self.fullExpFileName}/{self.expFileName}_{sampleName}_{self.creationTime}"
		self.initDir(path)
		CLIMessage(f"Start scanning sample: {sampleName}", "I")
		self.scan(path, sampleName)
		log.info("The experiment has been finished")
		self.epics_pvs["ScanStatus"].put(2, wait=True)				# **
		if not self.testingMode and self.receiveNotifications:
			email(self.experimentType, self.proposalID).sendEmail(type="finishScan", msg="The experiment has been finished", DS=self.fullExpDataPath)
		self.finishScan()

		expEndTime = datetime.now().strftime("%d.%m.%Y %H:%M:%S")
		log.info(f"experiment end time: {expEndTime}")

	def moveTheta(self, point):

		twoTheta = 0

		CLIMessage(f"2theta moving to {point}", "IO")
		CLIMessage(f"theta moving to {point/2}", "IO")

		thetaMotor = threading.Thread(target=self.theta, args=(point,), daemon=True)
		twoThetaMotor = threading.Thread(target=self.twoTheta, args=(point,), daemon=True)

		thetaMotor.start()
		twoThetaMotor.start()

		thetaMotor.join()
		twoThetaMotor.join()

		return twoTheta

	def theta(self, point):

		twoTheta = 0
		# self.epics_motors["TwoTheta"].move(point, wait=True)
		# twoTheta = self.epics_motors["TwoTheta"].readback
		time.sleep(self.settlingTime)

	def twoTheta(self, point):
		pass

	def signal_handler(self, sig, frame):

		if not self.lock:
			self.lock = True
			self.exit = True		# force exit from the acquiring process
			self.epics_motors["Theta"].stop()		# stop theta motor
			super().signal_handler(sig, frame)
