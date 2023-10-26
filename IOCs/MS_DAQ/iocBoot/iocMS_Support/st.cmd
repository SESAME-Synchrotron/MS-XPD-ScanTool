#!../../bin/linux-x86_64/MS

< iocBoot/iocMS/envPaths

epicsEnvSet("P", "MS:")
epicsEnvSet("R", "Supp:")

dbLoadDatabase "dbd/MS.dbd"
MS_registerRecordDeviceDriver pdbbase

dbLoadRecords("db/MS_Support.db", "P=$(P), R=$(R)")

iocInit
