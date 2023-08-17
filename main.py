#!/usr/bin/python3.9

import epics
import os
import sys
from time import sleep
from enum import Enum

from twoThetaStep import twoThetaStep
from twoThetaStepSlits import twoThetaStepSlits
from SEDSS.CLIMessage import CLIMessage

_TOP = "IOCs/MS_DAQ/db/"
class ScanningSubs(Enum):
    
    _1 = "twoTheta:"
    _3 = "twoThetaSlits:"

if __name__ == "__main__":
    
    pvlist = [_TOP + "MS_UI_settings.req", _TOP + "MS_settings.req"]
    macros = {"$(P)":"MS:", "$(N)":list(range(1, 41))}

    os.system('cd & /home/dcasu/MStest -qt')

    x = epics.PV("MS:ScanningType").get()

    if x == 1:

        command = 'tmux new -d -s MS_TwoThetaStep && tmux send-keys -t MS_TwoThetaStep "cd IOCs/MS_DAQ; ./bin/linux-x86_64/MS iocBoot/iocMS_TwoThetaStep/st.cmd" ENTER'
        os.system(command)
        sleep(0.5)
        pvlist.append(_TOP + "MS_TwoThetaStep_settings.req")
        twoThetaStep(pvlist, macros, ScanningSubs._1.value)

    elif x == 3:

        command = 'tmux new -d -s MS_TwoThetaStepSlits && tmux send-keys -t MS_TwoThetaStepSlits "cd IOCs/MS_DAQ; ./bin/linux-x86_64/MS iocBoot/iocMS_TwoThetaStepSlits/st.cmd" ENTER'
        os.system(command)
        sleep(0.5)
        pvlist.append(_TOP + "MS_TwoThetaStepSlits_settings.req")
        twoThetaStepSlits(pvlist, macros, ScanningSubs._3.value)

    else:
        CLIMessage("Scanning type not provided!!", "E")
        sys.exit()
