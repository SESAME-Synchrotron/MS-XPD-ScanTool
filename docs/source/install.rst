Installing MS/XPD Scanning Tool
===============================

This page includes information about the needed packages to run the scanning tool.

Prerequisites
--------------

The following should be installed before running the scanning tool:

- OS: Linux RedHat based OS, officially supported by *Scientific Computing & System Communication Team*.
- Control System & Qt5: EPICS control system, officially supported by *Control Team*.
- Python: Python3.9.
- RPM & PIP packages:

	::

		$ yum install git
		$ yum install tmux
		$ yum install wmctrl
		$ pip3.9 install virtualenv


	Install the following from SESAME-local-repo:
	::

		$ yum install *epics*
		$ yum install *qt5*
		$ yum install python3.9

- QtCreator: Having QtCreator on your PC is recommended. To install it:
	1. Download QtCreator from SESAME-drive: https://drive.sesame.org.jo/owncloud/index.php/s/LO3GLyDkPMWZKU9.
	2. After downloading, install qt-creator-opensource-linux-x86_64-4.13.3.run, and make sure to install it on ``/opt/`` directory.
	3. After installing the above packages & QtCreator, go to ``~/.bashrc`` and copy the following:
	::
		export EPICS_BASE='/opt/epics/base'
		export EPICS_HOST_ARCH=linux-x86_64
		export PATH=${PATH}:/opt/qtcreator-4.13.3/bin/
		export QWT_ROOT=/usr/local/qwt-6.1.3
		export QWT_INCLUDE_PATH=${QWT_ROOT}/include
		export QE_TARGET_DIR=/usr/local/epics-qt
		export PATH=${EPICS_BASE}/bin/$EPICS_HOST_ARCH:${QE_TARGET_DIR}/bin/${EPICS_HOST_ARCH}:/usr/lib64/qt5/bin:${PATH}
		export LD_LIBRARY_PATH=${EPICS_BASE}/lib/${EPICS_HOST_ARCH}:/usr/local/qwt-6.1.3/lib:${QE_TARGET_DIR}/lib/${EPICS_HOST_ARCH}:${QE_TARGET_DIR}/lib/${EPICS_HOST_ARCH}/designer
		export QT_PLUGIN_PATH=${QT_PLUGIN_PATH}:${QWT_ROOT}/plugins:$QE_TARGET_DIR/lib/$EPICS_HOST_ARCH
	* It is preferable to create an alias for QtCreator, go to ``~/.bashrc``, and type this line: ``alias qtcreator='cd && /opt/qtcreator-4.13.3/bin/qtcreator'``.
	4. ``$ source ~/.bashrc``
	5. To validate your setup, open QtCreator and create a new project, you should be able to open QtCreator and browse (Qwt and epics-qt widgets) successfully.

.. note::

	The DAQ System is developed under this environment:
		- Rocky Linux 8.9. However, there should be no reason to not work on other distributions.
		- EPICS V3.14,. However, there should be no reason to not work on above versions.
		- Python 3.9.16. However, there should be no reason to not work on 3.9 & above.
		- Qt5 & QtCreator 4.13.3 based on 5.15.2. However, there should be no reason to not work on Qt5 & QtCreator 4.13 based on 5.15 & above.


Installing DAQ System
---------------------
After completing the prerequisites, follow these steps to install the DAQ System:

- Python virtual environment: venv module of Python is being used as a virtual environment for this setup.

	The venv module of python provides support for creating virtual environments that is isolated from system site directories. Normally, each virtual environment has its own Python binary (which matches the version of the binary that was used to create this environment) and can have its own independent set of installed Python packages in its site directories.

- Create a virtual environment:
	::

		$ python3.9 -m venv ${dir}/venv3.9

	It is preferable to create an alias for the environment:
	Go to ``~/.bashrc``, and type this line: ``alias p3='source ${dir}/venv3.9/bin/activate'``.

	::

		source ~/.bashrc

- Cloning DAQ repo: The scanning tool (MS/XPD) is available on github. The most recent version can be found on this link: https://github.com/SESAME-Synchrotron/MS-XPD-ScanTool.

	.. note::
		Make sure that the python environment is activated before proceeding with this section.

	.. note::
		Make sure you have ``control`` user on your system.

	::

		$ cd ~
		$ git clone https://github.com/SESAME-Synchrotron/MS-XPD-ScanTool.git


Clone *SEDSS Package* (https://github.com/SESAME-Synchrotron/SEDSS.git) into ``MS-XPD-ScanTool``.
	::

		$ git clone https://github.com/SESAME-Synchrotron/SEDSS.git

Install pip packages:
	::

		$ pip install -r requirements.txt

Compile the IOCs:
	::

		$ cd IOCs/MS_DAQ
		$ make distclean
		$ make

Compile the GUIs:

	- DAQ Tool:
	::

		$ cd UI/DAQ_Tool/MS
		$ make distclean
		$ qmake
		$ make

	- TwoThetaStep GUI:
	::

		$ cd UI/Visualization/twoThetaStep
		$ make distclean
		$ qmake
		$ make

	- TwoThetaStepSlits GUI:
	::

		$ cd UI/Visualization/twoThetaSlits
		$ make distclean
		$ qmake
		$ make

	- TwoThetaStepTemp GUI:
	::

		$ cd UI/Visualization/twoThetaTemp
		$ make distclean
		$ qmake
		$ make

	- ThetaTwoThetaStep GUI:
	::

		$ cd thetaTwoTheta
		$ make distclean
		$ qmake
		$ make


Run MS/XPD IOCs:

	- UI IOC:
	::

		$ tmux new -s UI_IOC
		$ cd IOCs/MS_DAQ
		$ ./bin/linux-x86_64/MS iocBoot/iocMS/st.cmd

	- Support IOC:
	::

		$ tmux new -s Support_IOC
		$ cd IOCs/MS_DAQ
		$ ./bin/linux-x86_64/MS iocBoot/iocMS_Support/

.. note::

	Very important!

	Ask *Data Collection & Analysis* team to do the following:
		- provide emails template.
		- prepare ``metadata`` & ``DATA`` folders.
		- prepare ssh public-private keys.

.. warning::
	To validate the installation, type in the main dir ``python main.py``. If everything is set up correctly, you should see the GUI pops up. Otherwise, error messages and alerts should be shown in the terminal.
