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
		:scale: 70%

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
		:scale: 70%

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

	:ref:`TwoTheta_Step_Scan`.
	:ref:`TwoTheta_Step_Scan_with_Temperature`.
	:ref:`TwoTheta_Step_Scan_with_Slits_Configurations`.
	:ref:`Theta-TwoTheta_Step_Scan`.

	.. figure:: /images/scanModes.png
		:align: center
		:alt: scan modes
		:scale: 70%

		*Figure 3: Available scan modes*

By choosing on of the scan modes, you have the option either create a configuration file and thus generate a new configuration file or load an already existed configuration file.

.. figure:: /images/configFile.png
   :align: center
   :alt: configuration file GUI
   :scale: 70%

   *Figure 4: Configuration mode choosing GUI, either to create new config file or load already existed one*

.. warning::

	In the second option (load configuration file) is chosen, you have to make sure that:
		- the configuration file should be ended with ".config" extension.
		- the loaded configuration file should be corresponded with chosen scan mode.
		- the configuration file format is **JSON** format, if the file or one of the above conditions is not correct, you will be alerted.

Next GUI is meant to enter new experiment configurations or see/edit a loaded one, based on the chosen scan mode.

.. _TwoTheta_Step_Scan:

A. TwoTheta Step Scan Mode
---------------------------

	The next step after creating or loading the configuration file is to decide whether to use an arm robot.

	.. note:: The arm robot is only supported for these scan modes: **TwoTheta Step Scan** and **TwoTheta Step Scan with Slits Configurations**.

	* Use Robot: The DAQ system offers an Arm Robot, it has been designed to handle the samples in a container that holds up to **40** samples.
	.. figure:: /images/robot.png
		:align: center
		:alt: use robot GUI
		:scale: 70%

		*Figure 5: Using robot GUI*

	By choosing **Yes**, you will see/edit the main experiment parameters GUI for robot use.

	.. figure:: /images/twoThetaStepRobot.png
		:align: center
		:alt: TwoTheta Step Scan Robot in use GUI
		:scale: 70%

		*Figure 6: Main experiment parameters (TwoTheta Step Scan Using Robot)*

	The user can enter many intervals, each interval has diffractometer start angle(deg), end angle(deg), step size, Pilatus detector exposure time(s).

	.. .. figure:: /images/intervals.png
	.. 	:align: center
	.. 	:alt: proposal ID

	.. 	*Figure 5: DCM energy equations with K step unit*

.. warning:: The DAQ System checks the user inputs parameters instantly, and emits warning indications (red borders, red background, red flash LEDs, and exclamation marks) for incorrect inputs.

	The user can define many samples and align them with respect to the container (depending on the number of samples are being defined). Through this GUI, the user can select the pickup positions and define the picking order either serial (ascending sampling) or random (user defined pattern based on elected positions). Also, for each sample you must assign name where it will be used as part of the experimental file name.

	.. .. figure:: /images/sampleName.png
	.. 	:align: center
	.. 	:alt: proposal ID

	.. 	*Figure 7: Sample position & name GUI*


.. note:: Holding the cursor over the input fields emits an info tool tip.

	By clicking “Next”, if all is fine, the last GUI will pop up as shown below:

		.. .. figure:: /images/finish.png
		.. 	:align: center
		.. 	:alt: proposal ID

		.. *Figure 10: Last GUI before triggering the scan to start*

	The DAQ system also offers notifications feature, it is an email service for any new scan-related updates.

Once scan is started, interactive logs will be printed on the main terminal showing exactly what is being processed. Also, an interactive data visualization tool will start plotting the experimental data.

.. .. figure:: /images/plot.png
..    :align: center
..    :alt: proposal ID

..    *Figure 11: Interactive data visualization GUI*
