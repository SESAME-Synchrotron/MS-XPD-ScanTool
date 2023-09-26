#!/usr/bin/python3.9

import log
import time
from step import step
from SEDSS.CLIMessage import CLIMessage

class twoThetaStepSlits(step):

	def __init__(self, PVsFiles, macros, scanningSubs):
		super().__init__(PVsFiles, macros, scanningSubs)

	def startScan(self):

		self.scan()

	def robot(self):
		CLIMessage("robot in use","E")

	def drange(self, start, stop, step, prec=10):
		return super().drange(start, stop, step, prec)
