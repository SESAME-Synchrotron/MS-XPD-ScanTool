from slitsOperations import slitsOperations

import log

log.setup_custom_logger("./SED_MS_Scantool.log")
log.info("Start scanning tool")
x= slitsOperations(imgPath="/Users/mustafaalzubi/Desktop/DCA/_Dev/2thetaCalculator/testDataset/CAF32_18k_10s_3_20.0000.tiff", tTheta=3, configFile="/Users/mustafaalzubi/Desktop/DCA/Beamlines/MS/DAQ/XRD-Scan/configrations/2theta-Slits-Step.json")
print (*x.slitsPixelIntinisty)