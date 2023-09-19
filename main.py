#!/usr/bin/python3.9

import os
import sys
from time import sleep
import epics

from twoThetaStep import twoThetaStep
from twoThetaTemp import twoThetaTemp
from twoThetaStepSlits import twoThetaStepSlits
from SEDSS.CLIMessage import CLIMessage
from SEDSS.SEDFileManager import readFile

configFileName = "configurations/main.json"
configFile = readFile(configFileName).readJSON()

_PATH = configFile["paths"]
_TOP = _PATH["_TOP"]
_IOC = _PATH["_IOC"]

_MACROS = configFile["macros"]
prefix               = _MACROS["Prefix"]
MS_TwoThetaStep      = _MACROS["MS_TwoThetaStep"]
MS_TwoThetaTemp      = _MACROS["MS_TwoThetaTemp"]
MS_TwoThetaStepSlits = _MACROS["MS_TwoThetaStepSlits"]
scanningTool_PV      = _MACROS["scanningToolPV"]
macrosList           = _MACROS["macrosList"]
P = macrosList["P"]
N = macrosList["N"]

scanningSubs = configFile["scanningSubs"]
_1 = scanningSubs["_1"]
_2 = scanningSubs["_2"]
_3 = scanningSubs["_3"]

reqFiles = configFile["files"]["reqFiles"]
MS_req                   = reqFiles["MS"]
MS_UI_req                = reqFiles["MS_UI"]
MS_TwoThetaStep_req      = reqFiles[MS_TwoThetaStep]
MS_TwoThetaTemp_req      = reqFiles[MS_TwoThetaTemp]
MS_TwoThetaStepSlits_req = reqFiles[MS_TwoThetaStepSlits]

_EXE = configFile["exe"]
DAQ_Tool                 = _EXE["DAQ_Tool"]
MS_TwoThetaStep_exe      = _EXE[MS_TwoThetaStep]
MS_TwoThetaTemp_exe      = _EXE[MS_TwoThetaTemp]
MS_TwoThetaStepSlits_exe = _EXE[MS_TwoThetaStepSlits]

pvlist = [_TOP + MS_UI_req, _TOP + MS_req]
macros = {P:prefix, N:list(range(1, 41))}

if __name__ == "__main__":

	os.system(f'cd & {DAQ_Tool} -qt')

	scanningToolPV = epics.PV(scanningTool_PV).get()

	if scanningToolPV == 1:

		command = f'tmux new -d -s {MS_TwoThetaStep} && tmux send-keys -t {MS_TwoThetaStep} "cd {_IOC}; {MS_TwoThetaStep_exe}" ENTER'
		os.system(command)
		sleep(0.5)
		pvlist.append(_TOP + MS_TwoThetaStep_req)
		twoThetaStep(pvlist, macros, _1)

	elif scanningToolPV == 2:

		command = f'tmux new -d -s {MS_TwoThetaTemp} && tmux send-keys -t {MS_TwoThetaTemp} "cd {_IOC}; {MS_TwoThetaTemp_exe}" ENTER'
		os.system(command)
		sleep(0.5)
		pvlist.append(_TOP + MS_TwoThetaTemp_req)
		twoThetaTemp(pvlist, macros, _2)

	elif scanningToolPV == 3:

		command = f'tmux new -d -s {MS_TwoThetaStepSlits} && tmux send-keys -t {MS_TwoThetaStepSlits} "cd {_IOC}; {MS_TwoThetaStepSlits_exe}" ENTER'
		os.system(command)
		sleep(0.5)
		pvlist.append(_TOP + MS_TwoThetaStepSlits_req)
		twoThetaStepSlits(pvlist, macros, _3)

	else:
		CLIMessage("Scanning type not provided!!", "E")
		sys.exit()
