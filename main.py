#!/usr/bin/python3.9

import os
import sys
import subprocess
from time import sleep
from tendo import singleton
import epics

from twoThetaStep import twoThetaStep
from twoThetaTemp import twoThetaTemp
from twoThetaStepSlits import twoThetaStepSlits
from thetaTwoThetaStepSlits import thetaTwoThetaStepSlits
from emailNotifications import email
from SEDSS.CLIMessage import CLIMessage
from SEDSS.SEDFileManager import readFile

configFileName = "configurations/main.json"
configFile = readFile(configFileName).readJSON()

_PATH = configFile["paths"]
_TOP = _PATH["_TOP"]
_IOC = _PATH["_IOC"]

_MACROS = configFile["macros"]
prefix               	  = _MACROS["Prefix"]
MS_TwoThetaStep      	  = _MACROS["MS_TwoThetaStep"]
MS_TwoThetaTemp      	  = _MACROS["MS_TwoThetaTemp"]
MS_TwoThetaStepSlits 	  = _MACROS["MS_TwoThetaStepSlits"]
MS_ThetaTwoThetaStepSlits = _MACROS["MS_ThetaTwoThetaStepSlits"]
scanningTool_PV      	  = _MACROS["scanningToolPV"]
cancel				 	  = _MACROS["cancelScanPV"]
macrosList           	  = _MACROS["macrosList"]
P = macrosList["P"]
N = macrosList["N"]

scanningSubs = configFile["scanningSubs"]
_1 = scanningSubs["_1"]
_2 = scanningSubs["_2"]
_3 = scanningSubs["_3"]
_4 = scanningSubs["_4"]

reqFiles = configFile["files"]["reqFiles"]
MS_req                   	  = reqFiles["MS"]
MS_UI_req                	  = reqFiles["MS_UI"]
MS_supp_req              	  = reqFiles["MS_Support"]
MS_TwoThetaStep_req      	  = reqFiles[MS_TwoThetaStep]
MS_TwoThetaTemp_req      	  = reqFiles[MS_TwoThetaTemp]
MS_TwoThetaStepSlits_req 	  = reqFiles[MS_TwoThetaStepSlits]
MS_ThetaTwoThetaStepSlits_req = reqFiles[MS_ThetaTwoThetaStepSlits]

_EXE = configFile["exe"]
DAQ_Tool                 	  = os.path.expanduser(_EXE["DAQ_Tool"])
MS_TwoThetaStep_exe      	  = _EXE[MS_TwoThetaStep]
MS_TwoThetaTemp_exe      	  = _EXE[MS_TwoThetaTemp]
MS_TwoThetaStepSlits_exe 	  = _EXE[MS_TwoThetaStepSlits]
MS_ThetaTwoThetaStepSlits_exe = _EXE[MS_ThetaTwoThetaStepSlits]

pvlist = [_TOP + MS_UI_req, _TOP + MS_req, _TOP + MS_supp_req]
macros = {P:prefix, N:list(range(1, 41))}

try:
	me = singleton.SingleInstance()
except:
	CLIMessage("Can't start DAQ tool, the DAQ system is already running", "E")
	sys.exit()

if __name__ == "__main__":

	scanningToolPV = epics.PV(scanningTool_PV).get(timeout=1, use_monitor=False)

	if scanningToolPV is None:
		CLIMessage("Scanning IOC is not running!!", "E")
		email("").sendEmail("UI_IOC")
		sys.exit()

	if os.path.exists(DAQ_Tool):
		try:
			process = subprocess.run([DAQ_Tool, '-qt'], check=True)
		except:
			CLIMessage("Scan has been cancelled!", "W")
			sys.exit()
	else:
		CLIMessage(f"Can't start the scanning tool! {DAQ_Tool}", "E")
		email("").sendEmail(type="UI", msg=f"UI path: {DAQ_Tool}")
		sys.exit()

	if epics.PV(cancel).get(timeout=1, use_monitor=False):
		CLIMessage("Scan has been cancelled!", "W")
		sys.exit()

	scanningToolPV = epics.PV(scanningTool_PV).get(timeout=1, use_monitor=False)

	if scanningToolPV == 1:
		if os.system(f"tmux has-session -t {MS_TwoThetaStep}") != 0:
			command = f'tmux new -d -s {MS_TwoThetaStep} && tmux send-keys -t {MS_TwoThetaStep} "cd {_IOC}; {MS_TwoThetaStep_exe}" ENTER'
			os.system(command)
			sleep(0.5)
		pvlist.append(_TOP + MS_TwoThetaStep_req)
		twoThetaStep(pvlist, macros, _1)

	elif scanningToolPV == 2:
		if os.system(f"tmux has-session -t {MS_TwoThetaTemp}") != 0:
			command = f'tmux new -d -s {MS_TwoThetaTemp} && tmux send-keys -t {MS_TwoThetaTemp} "cd {_IOC}; {MS_TwoThetaTemp_exe}" ENTER'
			os.system(command)
			sleep(0.5)
		pvlist.append(_TOP + MS_TwoThetaTemp_req)
		twoThetaTemp(pvlist, macros, _2)

	elif scanningToolPV == 3:
		if os.system(f"tmux has-session -t {MS_TwoThetaStepSlits}") != 0:
			command = f'tmux new -d -s {MS_TwoThetaStepSlits} && tmux send-keys -t {MS_TwoThetaStepSlits} "cd {_IOC}; {MS_TwoThetaStepSlits_exe}" ENTER'
			os.system(command)
			sleep(0.5)
		pvlist.append(_TOP + MS_TwoThetaStepSlits_req)
		twoThetaStepSlits(pvlist, macros, _3)

	elif scanningToolPV == 4:
		if os.system(f"tmux has-session -t {MS_ThetaTwoThetaStepSlits}") != 0:
			command = f'tmux new -d -s {MS_ThetaTwoThetaStepSlits} && tmux send-keys -t {MS_ThetaTwoThetaStepSlits} "cd {_IOC}; {MS_ThetaTwoThetaStepSlits_exe}" ENTER'
			os.system(command)
			sleep(0.5)
		pvlist.append(_TOP + MS_ThetaTwoThetaStepSlits_req)
		thetaTwoThetaStepSlits(pvlist, macros, _4)

	else:
		CLIMessage("Scanning type not provided!!", "E")
		sys.exit()
