Data Processing
================
.. note::User could use the desktop computer at the beamline (Not the main workstation) process his data by copying the raw files from the data Server and paste it on a new folder in the computer, then apply the following processing instructions
		 Never use USB portable pen drive to transfer data, Data can be shared with the users via SESAME drive. (cordinate with beamline scientist for getting your collected data)

This section is dedicated to users. Here, you can share notes and feedback, and contribute to any topics related to the MS-XPD Beamline.
.. ref::`Instructions on data processing software available at the beamline.`.
Several codes are avialable at the beamline for processing the colected data, switching between them is possible based on the case of study, the main codes are

	A. :ref:`Tool_1_MS-2D_converter_p`.
	B. :ref:`Tool_2_MS-2D_converter_s_(Spherical)`.
	C. :ref:`Tool_3_MS-2D converter_Image J software`.  

.. _Tool_1_MS-2D_converter_p:

Tool_1:MS-2D converter_p (pyFAI)
--------------------------------
**Overview**


This Python script processes TIFF images from a selected directory to perform azimuthal integration of X-ray diffraction data. It uses the pyFAI library for integration and generates output files containing 2θ (2-theta) and intensity data. The script also includes a GUI for user interaction, allowing users to select the directory, specify parameters, and start the processing.

.. note:: you can use this github link to download the necessary codes related to the current tool
	.. _external target: https://github.com/M1Abdellatief/2D-diffraction-image-converter-P-RT 

.. note:: Citing the pyFAI reference is recommended as MS-2D converter (either scriptable codes or GUI) is based on the pyFAI library.
	here is the reference to cite  " J Appl Crystallogr . 2015 Mar 24;48(Pt 2):510-519. doi: 10.1107/S1600576715004 " 
	
**Dependencies**


- os
- tkinter
- pyFAI
- fabio
- numpy
- matplotlib
- re
- PIL (Pillow)

**Functions**


Processes TIFF images in the specified directory.

**GUI Parameters**

.. note::The physical meaning of the following parameters are linked to the pyFAI geometry definations, visit the following link for more details
    .. _external target: https://pyfai.readthedocs.io/en/stable/ 

- **directory**: Path to the directory containing TIFF images.
- **sample_name**: Name for the output file.
- **binning_no** (optional): Number of radial bins for integration (default is 4000).
- **lamda** (optional): Wavelength of X-ray in Angstroms (default is 0.82708).
- **poni1** (optional): Position of the detector center (x) in meters (default is 0.041), refer to pyFAI geometry.
- **poni2** (optional): Position of the detector center (y) in meters (default is 0.0525), refer to pyFAI geometry.
- **tth_zero** (float, optional): Zero shift for 2θ in degrees (recommended default value is 0.03 based on testing experiments).



**Description**


- Reads TIFF images from the specified directory.
- Extracts 2θ and intensity data by applying azimuthal integration.
- Filters the data based on the rotation angle extracted from the filename.
- Saves the processed data to a file and calculates the average intensity.
- Generates and displays a plot of the averaged 2θ vs intensity data with a logarithmic scale.

Opens a file dialog to select a directory and updates the GUI with the selected directory. 'start processing' validates user inputs and starts the image processing when the "Start Processing" button is clicked.

**How to Run**


1. Ensure all dependencies are installed.
2. Run the script. The GUI window will open.
3. Use the GUI to select a directory, specify parameters, and start processing.


**Note**


Ensure that your TIFF filenames contain the necessary angle information as expected by the parsing logic (Use Si TIFF images in the Demo folder for a test).

Example of using MS-2D converter to process Si standard diffraction Tiff images:: 
----------------------------------------------------------------------------------

The collected diffraction images for an experiment will be automatically stored on the users data server, where users can take a copy to their own computer and process the images to obtain the diffraction files. An example below shows set of images for Si_640f NIST standard measured at 15 keV at various 2theta values (starting from 15.00 deg. to 69.00 deg.)

	.. figure:: /images/processing-2.png
		:align: center
		:alt: first popup GUI
		:scale: 80%

		*Figure 1: set of tiff images collected for Silicon (NIST 640 f standard) at the MS-XPD beamline at 15 keV*

Run the MS-2D converter program, this will activate the software window 

	.. figure:: /images/processing-1.png
		:align: center
		:alt: first popup GUI
		:scale: 80%

		*Figure 2: GUI winodw for the MS-2D converter (P) tool aimed for tiff images integration*

**Required Parameters:**

•	Select the directory containing the TIFF images.
•	Enter a sample name.


**Optional Parameters:**

•	Adjust the binning number (affects the final 2Θ step size).
•	Change the wavelength (default value is set for 15 keV X-rays).
•	The poni1 and poni2 values are set to a well-calibrated default. Modify these only if coordinated with the beamline scientist.
•	The default 2θ zero offset is 0.03. This can be adjusted if a different value is observed.
After entering the parameters in the GUI, confirm the scanning mode selected for the measurements. The default mode is Room Temperature unless Temperature Scan Mode is selected. Click "Start Processing" to initiate the process. A figure showing the processed diffraction images will appear for visual inspection.

	.. figure:: /images/processing-3.jpg
		:align: center
		:alt: first popup GUI
		:scale: 80%

		*Figure 3: equivalent diffraction pattern after processing the Silicon tiff images *

A close look for the processed peaks of Si_640f NIST for visual inspection 

	.. figure:: /images/processing-4.jpg
		:align: center
		:alt: first popup GUI
		:scale: 80%

		*Figure 4:  Diffraction peaks for Silicon at the MS-XPD beamline *

.. note:: Once the processing is finished, a notification message will appear telling " processing complete " as shown in the following figure
	
	.. figure:: /images/processing-5.jpg
		:align: center
		:alt: first popup GUI
		:scale: 80%

    	*Figure 5:  A notification message after completing the integration process *


.. _Tool_2_MS-2D_converter_s_(Spherical):

Tool 2: MS-2D Converter_s (Spherical Model)
---------------------------------------------

**Overview**


The main tasks include reading the images, performing specific calculations based on pixel intensities, and generating output files with the results.

.. note:: you can use this github link to download the necessary codes related to the current tool
	.. _external target: https://github.com/M1Abdellatief/2D-Diffraction-images-Converter-S 

**Dependencies**


- os :Helps with file and directory handling.
- tkinter :Used for creating the GUI components.
- numpy : For numerical operations on image arrays.
- matplotlib: For plotting and visualizing the processed data.
- PIL (Pillow): Used for opening and processing image files
- scipy.signal
- pandas :  Used for organizing and saving data in tabular form.


**Gui parameters for MS-2D Converter_s (Spherical Model):**


	.. figure:: /images/processing-spherical.png
		:align: center
		:alt: first popup GUI
		:scale: 80%

**Inputs:**

	- directory: Path to the directory containing TIFF images.
	- output_filename: Name for the output file where results will be saved.
	- y_start, y_end, x_min, x_max: Pixel ranges used to crop the image.
	- Ro, yy0, xx0: Parameters for calculating diffraction angles (Q vector).
	- use_custom_parsing: A flag to indicate whether custom parsing logic should be applied based on temperature scan or not.

**Processing and Functions:**

	- Loads all `.tiff` files in the specified directory.
	- Parses each image and extracts the pixel intensity data within the specified range.
	- Applies specific mathematical calculations to determine the diffraction angles based on the pixel intensity and beam position.
	- Saves the processed data in a tabular format and applies smoothing with the Savitzky-Golay filter.
	- Generates a plot of the processed data.



**How to run**


- Directory Selection: The user selects the directory containing the TIFF images using the "Browse" button.
- Parameter Input: The user inputs the required parameters such as the output filename, pixel ranges, and other calculation parameters.
- Optional Settings: The user can check the "Temperature Scan" box to enable custom parsing logic for filenames.
- Run Processing: The user clicks the "Run" button to start processing the images. The results will be saved in the specified output file and displayed as a plot.

**Outputs**


- A `.dat` file with sorted 2theta and intensity values.
- A smoothed data file and a plot of the intensity vs. 2theta.