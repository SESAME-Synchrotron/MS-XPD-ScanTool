import argparse
import log 
import decimal 
import epics
import time 
import pandas as pd

monoM1 = 'I09R1-MO-MC3:OH-DCM-SRV-ROTX1'
monoM2 = 'I09R1-MO-MC3:OH-DCM-STP-TRSZ1'
monoM3 = 'I09R1-MO-MC3:OH-DCM-STP-TRSY1'
monoEngSp = 'OH-DCM:Energy_SP'
monoEngRbv = 'OH-DCM:Energy_RBV'
ampDetector = 'I09-DI-AMP-1:getVoltage'
photoDiode = 'I09EH-ES-PD:getVoltage'



parser = argparse.ArgumentParser(description="XAFS Scanning Tool "\
 "is a software developed by DCA at SESAME to collect exprimintal data from XAFS / XRF Beamline at SESAME ")
parser.add_argument('--engStart', type=float,default = 7.7)
parser.add_argument('--engEnd', type=float,default = 7.8 )
parser.add_argument('--stepSize', type=float,default = 0.05 )
parser.add_argument ('--expTime', type=float, default=2)
parser.add_argument('--fileName', type=str, default='results.xlsx')


#########################################################
args = parser.parse_args()
engStart = args.engStart
engEnd = args.engEnd
stepSize = args.stepSize
expTime = args.expTime
fileName = args.fileName

def drange(start,stop,step,prec=10):
		log.info("Calculating energy points")
		decimal.getcontext().prec = prec
		points = []
		r= decimal.Decimal(start)
		step = decimal.Decimal(step)
		while r <=stop:
			points.append(float(r))
			r += step
		return points


def moveMono(SP):

	# self.PVs["PGM:Energy:Reached"].put(0, wait=True) # set the energy reached pv to False before start moving the PGM
	epics.PV(monoEngSp).put(SP, wait=True) # set the energy to the PGM 
	time.sleep(.15) # adding some delay to let the motor stat moving.
	log.info("Move mono to energy: {}".format(SP)) 
	"""
	the following loop tries to put the scan tool in wait state untill the PGM energy is reached by: 
		1. Keep checking the Grating & M2 motors status (DMOV)
		2. Keep checking the energy reached PV 
	Notes: 
		1. loop conditioning must be satisfied because energy PV is set to 0 before start moving the PGM.
		2. checkToleranceEvery variable can be changed in limites.josn file 
	"""

	while not epics.PV(monoM1+".DMOV").get() or not epics.PV(monoM2+".DMOV").get() or not epics.PV(monoM3+".DMOV").get():
		print ('*')
		time.sleep(.5)

	print('Energy reached:: ', epics.PV(monoEngRbv).get())
	"""
	the loop below has been added because the one above was not enough to get energy RBV within the allowed tolerances. The main issue is that energy RBV is a PROC PV 
	relies on many parameters to be calculated, this means, after reaching the target prositions of the PGM motors the final energy RBV needs some time to be calculated. 
	however, the loop does the following: 
		1. Periodically checks the energy RBV if it is within the given tolerances, if yes breaks the loop 
		2. if not, waits until the maximum wait time condition is met. 

	Notes: 
		1. energyRBVTolerance, checkToleranceEvery & maxTime2MeetTolerance variables can be changed/defined in the "configrations/limites.json" file 
		2. the three variables above have a big impact on the energy precision and scan time. 
	"""
	# CLIMessage("Energy : {}".format (self.PVs["PGM:Energy:RBV"].get(use_monitor = False)))
	
	# print("\n")
	# timeCounter = 0 
	# while not (float(SP) - self.scanLimites["energyRBVTolerance"]) <= float (self.PVs["PGM:Energy:RBV"].get()) <= (float(SP) + self.scanLimites["energyRBVTolerance"]):
	# 	#CLIMessage("Trying to reach the energy SP within the given tolerance", "IG")
	# 	self.PVs["PGM:Energy:SP"].put(SP, wait=True)
	# 	time.sleep(self.scanLimites["checkToleranceEvery"])
	# 	timeCounter = timeCounter + 1
	# 	if timeCounter * self.scanLimites["checkToleranceEvery"] >= self.scanLimites["maxTime2MeetTolerance"]:
	# 		log.warning("Reaching maximum wait time to reach the target energy")
	# 		break

	#self.PVs["PGM:Energy:Reached"].put(1, wait=True)
	# time.sleep(self.cfg["settlingTime"])


if __name__ == "__main__":

	# epics.PV("SCAN:S/TOP").put(0)		#### in order to enable voltage source####
	# paths	= Common.loadjson("configrations/paths.json")
	# cfg		= config.ConfigGUI(paths).cfg

	# cfg['scanType'] = 'stepEngScan' # temprory hard codded untill adding Mapping scan 

	# if cfg['scanType'] == 'stepEngScan':
	# 	ENGSCAN(paths = paths, cfg = cfg, testingMode = tMode)
	# elif cfg['scanType'] == 'stepMapScan':
	# 	MAPSCAN(paths = paths, cfg = cfg, testingMode = tMode)

	# sys.exit(app.exit())
	Data = []
	points = drange(engStart,engEnd,stepSize)
	for sp in points:
		print ('Moving sp to: ',sp)
		moveMono(sp)
		time.sleep(expTime)
		# print (, )?
		data = [epics.PV(monoEngRbv).get(), epics.PV(ampDetector).get(), epics.PV(photoDiode).get()] 
		Data.append(data)


# print (Data)
df = pd.DataFrame(Data, columns=['Energy', 'Amplifier RBV', 'Photon Diode'])
# print (df)
df.to_csv (fileName, index=False)

