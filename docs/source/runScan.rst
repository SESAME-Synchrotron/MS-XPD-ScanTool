Run Experiment and Collect Experimental Data
============================================

.. note::
	In order to run the scanning tool, you need to:
		1. Activate python environment that you have already setup by typing ``p3``.
		2. Make sure all beamline EPICS IOCs should be up and running before using the scanning tool.


The scanning tool directory is located in the home directory of the **control user**. To access it:

::

	$ cd ~
	$ cd MS-XPD-ScanTool
	$ python main.py


The main function will validate and execute some procedures and functions, if all is fine GUI will appear:

	.. figure:: /images/start.png
		:align: center
		:alt: first popup GUI
		:scale: 80%

	   	*Figure 1: First popup that allows you to choose experiment type*

.. warning::

	In case if the scanning tool does not start:
		- if one of UI PVs is disconnected, the scanning tool will show, in the main terminal, an error message in "red" color ("Scanning IOC is not running!!").
		- if UI path does not exist, the scanning tool will show, in the main terminal, an error message in "red" color ("Can't start the scanning tool!").
		- trying to start the scanning tool if it has already started, the scanning tool will show, in the main terminal, an error message in "red" color ("Can't start DAQ tool, the DAQ system is already running").

From the GUI above you can choose the experiment type:

	A. Choose **Users Experiment** if there is a scheduled beamtime for an accepted proposal.
	Upon choosing Users Experiment, you will be asked to provide scheduled proposal ID as shown in figure.2 below:

	.. figure:: /images/proposalID.png
		:align: center
		:alt: proposal ID GUI
		:scale: 80%

		*Figure 2: Proposal ID GUI*

	By choosing "Users Experiment", the scan tool will:
		* validate whether the provided proposal number is correct and valid for this beam time.
		* if the validation result is okay, the scanning tool will import the proposal metadata and include them in the experimental file. If not, user will be alerted and the tool will not be able to continue!!

	.. note:: The scanning tool is already integrated with the users database. All validation and metadata importing processes are done through such integration. metadata of a validated proposal includes but not limited to proposal title, principal investigator information, number of allocated shifts, proposal review committee.

	B. Choose **Local Experiment** to run in-house experiment that is not associated with a proposal.
	This scan mode is intended to run “not proposal based” experiments, example of such experiments:

	* Director general beamtime.
	* In-house research experiment.
	* Testing / commissioning new components at the Beamline.

	.. warning:: Normally, this option is restricted to beamline scientists.
	.. warning:: Access to experimental data generated out of this kind of experiment is restricted to beamline scientists and authorized SESAME staff only. On the other hand, the generated data will not be **mapped/linked** with any proposal or PI work.


The scanning tool offers four scan modes as shown in figure.3:

	A. :ref:`TwoTheta_Step_Scan`.
	B. :ref:`TwoTheta_Step_Scan_with_Temperature`.
	C. :ref:`TwoTheta_Step_Scan_with_Slits_Configurations`.
	D. :ref:`Theta-TwoTheta_Step_Scan`.

	.. figure:: /images/scanModes.png
		:align: center
		:alt: scan modes
		:scale: 80%

		*Figure 3: Available scan modes*

By choosing one of the scan modes, you have the option either create a configuration file and thus generate a new configuration file or load an already existed configuration file.

.. figure:: /images/configFile.png
   :align: center
   :alt: configuration file GUI
   :scale: 80%

   *Figure 4: Configuration mode choosing GUI, either to create new config file or load already existed one*

.. warning::

	In the second option (load configuration file) is chosen, you have to make sure that:
		- the configuration file should be ended with ".config" extension.
		- the loaded configuration file should be corresponded with chosen scan mode.
		- the configuration file format is **JSON** format, if the file or one of the above conditions is not correct, you will be alerted.

Next GUI is meant to enter new experiment configurations or see/edit a loaded one, based on the chosen scan mode.

.. _TwoTheta_Step_Scan:

TwoTheta Step Scan Mode
------------------------

	The next step after creating or loading the configuration file is to decide whether to use an arm robot.

	.. note:: The arm robot is only supported for these scan modes: **TwoTheta Step Scan** and **TwoTheta Step Scan with Slits Configurations**.

	* **Use Robot**: The DAQ system offers an Arm Robot, it has been designed to handle the samples in a container that holds up to **40** samples.
	.. figure:: /images/robot.png
		:align: center
		:alt: use robot GUI
		:scale: 80%

		*Figure 5: Using robot GUI*

	By choosing **Yes**, you will see/edit the main experiment parameters GUI for robot use.

	.. figure:: /images/twoThetaStepRobot.png
		:align: center
		:alt: TwoTheta Step Scan Robot in use GUI
		:scale: 80%

		*Figure 6: Main experiment parameters (TwoTheta Step Scan Using Robot)*

	The user can enter many intervals, each interval has diffractometer start angle(deg), end angle(deg), step size, and Pilatus detector exposure time(s).

	.. figure:: /images/intervals.png
		:align: center
		:alt: intervals table

		*Figure 7: Intervals*

	.. warning:: 

		The DAQ System checks the user inputs parameters instantly, and emits warning indications (red borders, red background, red flash LEDs, and exclamation marks) for incorrect inputs.
		
		.. figure:: /images/warnings.png
			:align: center
			:alt: warnings

			*Figure 8: Warnings types*

	The user can define many samples and align them with respect to the container (depending on the number of samples are being defined). Through this GUI, the user can select the pickup positions and define the picking order either serial (ascending sampling) or random (user defined pattern based on elected positions). Also, for each sample you must assign name where it will be used as part of the experimental file name.

	.. figure:: /images/samples.png
		:align: center
		:alt: samples GUI

		*Figure 9: Samples positions GUI*

	.. note:: Holding the cursor over the input fields emits an info tool tip.
	.. note:: Testing mode allows you to start a scan regardless the shutters status.

	* **Without Use Robot**: In case of proceeding without using robot, the main experiment parameters GUI will be as figure.10, the default NSamples is 1. 

	One of the scanning options for MS-XPD is **GIXRD** (Grazing Incidence X-ray Diffraction), which is intended for flat sample set up.

	.. figure:: /images/twoThetaStepWithoutRobot.png
		:align: center
		:alt: TwoTheta Step Scan Robot not in use GUI
		:scale: 80%

		*Figure 10: Main experiment parameters (TwoTheta Step Scan Without Using Robot)*

	By clicking **“Next”**, if all is fine, the last GUI will pop up as shown below:

	The DAQ system also offers **notifications feature**, it is an email service for any new scan-related updates.

	.. figure:: /images/finish.png
		:align: center
		:alt: finish GUI
		:scale: 80%

		*Figure 11: Last GUI before triggering the scan to start*

	Once scan is started, interactive logs will be printed on the main terminal showing exactly what is being processed. Also, an interactive data visualization tool UI will be started as shown below in figure.12.
	This interactive UI tool is designed to make it easy to monitor the scan status, it offers many features:
		- Scan Status represented with interactive colors ({Running:Green, Finished:Blue, Paused:Yellow, Stopped/Terminated:Red}).
		- Immediate Scan Actions (Pause, Resume, Stop).
		- Time Parameters (Experiment start time, end time, elapsed time, and expected remaining time).
		- Experiment Info.
		- Beamline Status (related to scan).
		- Browsing Data locally or remotely on `ICAT <https://icatproject.org>`_.
		- Current Experiment Parameters.
		- Scan Logs.

	.. figure:: /images/UI_Vis_TwoThetaStep.png
		:align: center
		:alt: TwoThetaStep visualization UI

		*Figure 12: Interactive data visualization GUI (TwoThetaStep Scan Mode)*

	.. warning:: All methods of closing are disabled intentionally.To exit, press **Cancel** for Scanning Tool, and **Close** for Interactive UI tool.


.. _TwoTheta_Step_Scan_with_Temperature:

TwoTheta Step Scan with Temperature Mode
-----------------------------------------

	The second scan mode offered by DAQ system is **TwoTheta Step Scan with Temperature**. This mode allows you to start experiments by exposing the capillary samples to high temperatures (up to 1000 °C).

	Following the same procedure, after creating or loading the configuration file, you will see/edit the main experiment parameters.

	.. figure:: /images/twoThetaStepTemp.png
		:align: center
		:alt: TwoTheta Step Scan Temp
		:scale: 80%

		*Figure 13: Main experiment parameters (TwoTheta Step Scan with Temperature)*

	The user as well can enter many intervals, twoTheta intervals and temperature intervals (start target temperature(°C), end target temperature(°C), step size, scans, and waiting/settling time(s)).
	
	.. figure:: /images/temperatureIntervals.png
		:align: center
		:alt: temperature intervals table

		*Figure 14: Intervals table with temperature*

	After filling the fields and clicking **Finish**, the interactive data visualization tool UI for this scan mode will be started as shown below in figure.15.
	
	This scan mode offers an additional feature: a **graph plot** that shows the temperature changes over time.

	.. figure:: /images/UI_Vis_TwoThetaStepTemp.png
		:align: center
		:alt: TwoThetaStep temp visualization UI

		*Figure 15: Interactive data visualization GUI (TwoThetaStep Scan with Temperature Mode)*

