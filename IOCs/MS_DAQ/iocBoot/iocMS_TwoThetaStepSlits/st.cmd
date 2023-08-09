#!../../bin/linux-x86_64/MS

< iocBoot/iocMS/envPaths

epicsEnvSet("P", "MS:")

dbLoadDatabase "dbd/MS.dbd"
MS_registerRecordDeviceDriver pdbbase

dbLoadTemplate("$(TOP)/iocBoot/iocMS_TwoThetaStepSlits/MS_TwoThetaStepSlits.substitutions")

iocInit
