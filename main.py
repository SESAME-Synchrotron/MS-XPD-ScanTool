#!/usr/bin/python3.9

import epics
import os
import sys
from twoThetaStep import twoThetaStep
from time import sleep
from SEDSS.CLIMessage import CLIMessage

if __name__ == "__main__":

    # command = 'tmux new -d -s MS_TwoThetaStep && tmux send-keys -t MS_TwoThetaStep "cd IOCs/MS_DAQ; ./bin/linux-x86_64/MS iocBoot/iocMS/st.cmd" ENTER'

    # os.system(command)
    # sleep(0.5)
    
    pvlist = ["/home/dcasu/XRD-Scan/IOCs/MS_DAQ/db/MS_UI_settings.req", "/home/dcasu/XRD-Scan/IOCs/MS_DAQ/db/MS_settings.req"]
    macros = {"$(P)":"MS:", "$(N)":list(range(1, 41))}

    os.system('cd & /home/dcasu/MStest -qt')

    if epics.PV("MS:ScanningType").get() == 1:

        command = 'tmux new -d -s MS_TwoThetaStep && tmux send-keys -t MS_TwoThetaStep "cd IOCs/MS_DAQ; ./bin/linux-x86_64/MS iocBoot/iocMS_TwoThetaStep/st.cmd" ENTER'
        os.system(command)
        sleep(0.5)
        pvlist.append("/home/dcasu/XRD-Scan/IOCs/MS_DAQ/db/MS_TwoThetaStep_settings.req")
        twoThetaStep(pvlist, macros)

    else:
        CLIMessage("Scanning type not provided!!", "E")
        sys.exit()
