TOP=../..

include $(TOP)/configure/CONFIG
#----------------------------------------
#  ADD MACRO DEFINITIONS AFTER THIS LINE
#=============================

#=============================
# Build the IOC application

PROD_IOC = MS
# MS.dbd will be created and installed
DBD += MS.dbd

# MS.dbd will be made up from these files:
MS_DBD += base.dbd

# Include dbd files from all support applications:
#MS_DBD += xxx.dbd

# Add all the support libraries needed by this IOC
#MS_LIBS += xxx

# MS_registerRecordDeviceDriver.cpp derives from MS.dbd
MS_SRCS += MS_registerRecordDeviceDriver.cpp

# Build the main IOC entry point on workstation OSs.
MS_SRCS_DEFAULT += MSMain.cpp
MS_SRCS_vxWorks += -nil-

# Add support from base/src/vxWorks if needed
#MS_OBJS_vxWorks += $(EPICS_BASE_BIN)/vxComLibrary

# Finally link to the EPICS Base libraries
MS_LIBS += $(EPICS_BASE_IOC_LIBS)

#===========================

include $(TOP)/configure/RULES
#----------------------------------------
#  ADD RULES AFTER THIS LINE

