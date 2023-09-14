from epics import PV
from SEDSS.CLIMessage import CLIMessage
import time
from SEDSS.SEDFileManager import readFile
import sys

config = "configurations/robot.json"

class robot():
    def __init__(self):
        self.cfg = readFile(config).readJSON()
        
        self.samplePosition = list(PV("MS:SamplesPositions").get())
        self.robotPVs = {}
        allPVsConnected = True
        for category, subdata in self.cfg.items():
            self.robotPVs[category] = {}
            if isinstance(subdata, dict):
                for key, value in subdata.items():
                    if PV(value).get() is None:
                        CLIMessage(f"PV {value} in category ({category}, {key}) is not connected", "E")
                        allPVsConnected = False
                    else:
                        self.robotPVs[category][key] = PV(value)
                        CLIMessage(f"PV {value} in category ({category}, {key}) is connected", "I")

        if not allPVsConnected:
            CLIMessage("Robot PVs not connected, the program won't continue", "E")
            sys.exit()

    def waitPVVal(self, PV, val):

        timeout = 5  
        startTime = time.time()
        while time.time() - startTime < timeout:
            checkVal = PV.get(as_string=True)
            
            if checkVal == val:
                return True  

            mins, secs = divmod(int(timeout - (time.time() - startTime)), 60)
            timeformat = f"{mins:02d}:{secs:02d}"
            CLIMessage(f"Retrying check the value, time left: {timeformat}", "W")
            time.sleep(1)

        CLIMessage(f"Timeout reached {timeout} sec. Value not reached.", "E")
        return False  

    def setup(self):
        
        if self.robotPVs["controllerErrorPVs"]["errorNumber"].get() !=0 or self.robotPVs["processErrorPVs"]["errorType"].get(as_string=True) != "No Error":
            CLIMessage(f"The program won't continue!!! please check the errors, and run try again.", "E")
            sys.exit()

        CLIMessage("Set Sample Container to 0 ...", "I")
        self.robotPVs["environmentPVs"]["sampleContainer"].put(0, wait=True)

        CLIMessage("Set Sample Stage to 0 ...", "I")
        self.robotPVs["environmentPVs"]["sampleStage"].put(0, wait=True)

        CLIMessage("Set Geipper Status to 1 ...", "I")
        self.robotPVs["environmentPVs"]["gripperStatus"].put(1, wait=True)

        # CLIMessage("Crucial Experiment? {}", "I")
        # self.robotPVs["environmentPVs"]["crucialExperiment"].put(1, wait=True)

        CLIMessage("Enable operation ...", "I")
        self.robotPVs["operationPVs"]["Enable"].put(1, wait=True)

        if self.waitPVVal(self.robotPVs["operationPVs"]["Status"], "Enabled"):
            CLIMessage("Servo On ...", "I")
            self.robotPVs["servoPVs"]["On"].put(1, wait=True)
        else:
            CLIMessage(f"Can't Enable the Robot!", "E")
            sys.exit()
            
        if self.waitPVVal(self.robotPVs["servoPVs"]["Status"], "Servo On"):
            CLIMessage("Set Automatic Mode ...", "I")
            self.robotPVs["statePVs"]["Mode"].put(0, wait=True)
        else:
            CLIMessage(f"Can't Enable the Servo!", "E")
            sys.exit()

        if not self.waitPVVal(self.robotPVs["statePVs"]["operationMode"], "Automatic"):
            CLIMessage(f"Can't Set Automatic Mode!", "E")
            sys.exit()

        CLIMessage("Run the Program ...", "I")
        self.robotPVs["programPVs"]["Run"].put(1, wait=True)


    def startExperiment(self):              # temporary function, it will be moved to main class
        
        CLIMessage("move sample container to position 1")
        time.sleep(2)

        CLIMessage("sample in operation, the robot is ready to pickup the sample ...", "W")
        self.robotPVs["environmentPVs"]["sampleInOperation"].put(1, wait=True)

        while not self.robotPVs["statePVs"]["currentState"].get(as_string=True) == "Wait For Scan Done":
            CLIMessage("waiting for scan done ...", "IR")

        
        CLIMessage("experiment in progress ...", "I")
        time.sleep(10)
        CLIMessage("experiment has been finished ...", "I")
        CLIMessage("scan has been done, the robot is ready to return the sample to sample container ...", "W")
        self.robotPVs["environmentPVs"]["scanStatus"].put(0, wait=True)

        while not self.robotPVs["statePVs"]["currentState"].get(as_string=True) == "TRANSITION TO SC Done":
            CLIMessage("waiting for drop the sample to sample container ...", "IR")

        CLIMessage("the sample is dropped, the scan has been finished sucssesfully ...", "I")

