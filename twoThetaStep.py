#!/usr/bin/python3.9

import epics
from MS import XRD
from SEDSS.CLIMessage import CLIMessage
import log

class twoThetaStep(XRD):

    def __init__(self, PVsFiles, macros):
        super().__init__(PVsFiles, macros)
    
    def startScan(self):
        
        CLIMessage("ss","e")
        log.info(f"start {self.epics_pvs['ScanningType'].get(as_string=True)}")

        if self.epics_pvs["UseRobot"].get():
            self.robot()
        super().startScan()

    def robot(self):
        CLIMessage("robot in use","E")

