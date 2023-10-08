#!/usr/bin/python3.9

import log
import time
from step import step
from robot import robot
from SEDSS.CLIMessage import CLIMessage

class twoThetaTemp(step):
	def __init__(self, PVsFiles, macros, scanningSubs):
		super().__init__(PVsFiles, macros, scanningSubs)