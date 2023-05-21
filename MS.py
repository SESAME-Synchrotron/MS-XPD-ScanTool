#!/usr/bin/python3.9

from epics import PV
import subprocess
from SEDSS.CLIMessage import CLIMessage

class XRD():

    def __init__(self, PVsFiles, macros):

        self.epics_pvs = {}
        self.data_pvs = {}

        if not isinstance(PVsFiles, list):
            pv_files = [PVsFiles]

        for pv_file in PVsFiles:
            self.readPVsFile(pv_file, macros)
        
        self.checkConnectedPVs()

    def readPVsFile(self, PVFile, macros):
        pv_file = open(PVFile)
        lines = pv_file.read().splitlines()
        pv_file.close()

        for line in lines:
            line = line.lstrip()

            # ignore blank lines or lines starting with #
            if line.startswith('#') or line == '':
                continue

            dictValue = line
            dictKey = line

            for key, value in macros.items():

                if dictValue.startswith("$(P)") and not dictValue.endswith("$(N)"):

                    dictValue = dictValue.replace(key, f"{value}")
                    pvKey = dictKey.replace(key, "")
                    self.epics_pvs[pvKey] = PV(dictValue)

                elif isinstance(value, list) and dictValue.endswith("$(N)"):

                    for n in value:

                        dictValue = dictValue.replace("$(P)", "MS:")
                        pvValue = dictValue.replace(key, f"{n}")

                        dictKey = dictKey.replace("$(P)", "")
                        pvKey = dictKey.replace(key, f"{n}")

                        self.data_pvs[pvKey] = PV(pvValue)
                else:
                    continue

    def checkConnectedPVs(self):

        for key in self.epics_pvs:
            if self.epics_pvs[key].get() is None:
                CLIMessage(f"PV {self.epics_pvs[key].pvname} is not connected", "E")
            else:
                CLIMessage(f"PV {self.epics_pvs[key].pvname} is connected", "I")

