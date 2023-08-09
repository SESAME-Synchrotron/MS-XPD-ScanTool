#!../../bin/linux-x86_64/MS

< iocBoot/iocMS/envPaths

epicsEnvSet("P", "MS:")

dbLoadDatabase "dbd/MS.dbd"
MS_registerRecordDeviceDriver pdbbase

dbLoadTemplate("$(TOP)/iocBoot/iocMS_TwoThetaStep/MS_TwoThetaStep.substitutions")

iocInit
