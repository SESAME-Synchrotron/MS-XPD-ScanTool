#!/usr/bin/python3.9

import epics
import subprocess
from twoThetaStep import twoThetaStep
from time import sleep

if __name__ == "__main__":

    command = 'tmux new -d -s MS_TwoThetaStep && tmux send-keys -t MS_TwoThetaStep "cd IOCs/MS_DAQ; ./bin/linux-x86_64/MS iocBoot/iocMS/st.cmd" ENTER'

    subprocess.run(['sh', '-c', command])
    sleep(0.5)
    twoThetaStep(["IOCs/MS_DAQ/db/MS_UI_settings.req", "IOCs/MS_DAQ/db/MS_settings.req", "IOCs/MS_DAQ/db/MS_TwoThetaStep_settings.req"], {"$(P)":"MS:", "$(N)":list(range(1, 41))})
