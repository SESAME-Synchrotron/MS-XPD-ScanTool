#< envPaths

epicsEnvSet("IOC","iocMS")
epicsEnvSet("TOP","/home/dcasu/XRD-Scan/IOCs/MS_DAQ")
epicsEnvSet("SUPPORT","/opt/epics/support")
epicsEnvSet("EPICS_BASE","/opt/epics/base")
epicsEnvSet("P", "MS:")


## Register all support components
dbLoadDatabase "dbd/MS.dbd"
MS_registerRecordDeviceDriver pdbbase

dbLoadTemplate("/home/dcasu/XRD-Scan/IOCs/MS_DAQ/iocBoot/iocMS_TwoThetaStep/MS_TwoThetaStep.substitutions")

iocInit
