"""
This is a simple program that plots the 2ϴ and intesity 
of the MS data 

"""
import pandas as pd 
import matplotlib.pyplot as plt 
from matplotlib.animation import FuncAnimation 
import epics

plt.style.use("ggplot")
Axes = plt.gca() # get x and y axeses of the current plot 
Fig = plt.gcf() # get current figure of the current plot 
Fig.set_size_inches(15,8) # sets figure size in inches 


def animate(i):
	try: # this try allow stopping the graph updating if the file is not there 
		data = pd.read_csv ("plottingData.csv")
		twoTheta = data["twoTheta"]
		Intensity = data["Intensity"]
		#y2 = data["total_2"]

		plt.cla()

		plt.plot(twoTheta,Intensity, label="Diffraction")
		#Fig.set_size_inches(15,8) # sets figure size in inches 
		if epics.PV("PLOTTING:XLable").get() == 0:
			Axes.set_xlabel("TwoTheta (2ϴ)",fontsize=20) 
		else:
			Axes.set_xlabel("Theta(ϴ)",fontsize=20) 

		Axes.set_ylabel("Intensity", fontsize=20)
		Axes.set_title("SESAME MS Beamline | Live Data Visualisation",fontsize=30)
		#plt.plot(x,y2, label="Channel 2")

		plt.legend(loc="upper left")
		plt.tight_layout() # tight layout 
	except:
		pass

ani =FuncAnimation(plt.gcf(), animate, interval=1000) # animation function runs every 1 second 

plt.tight_layout()
plt.show()

