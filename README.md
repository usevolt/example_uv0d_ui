# example_uv0d_ui
A basic template project for designing a graphical user interface with UV0D display


Although the compiling instructions here are given for Linux, they should work on other operating systems given that the operating system specific parts are modified accordingly.

##Compiling the source code
* Download the GNU toolchain for ARM from [](https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-rm/downloads) **OR** copy the necessary compiler binaries from uv_hal/lpc_chip_15xx/bin and make sure they are found in your PATH.
	* On linux copy the compilers to ~/bin directory
* Download the most recent **uvcan** binary from [](https://usevolt.fi/images/uvcan/) **OR** build it from source [](https://github.com/usevolt/uv03_can). 
	* Install the prerequisites for building by executing the command (on Ubuntu): 

sudo apt-get install build-essentials

* Make sure the **uvcan** binary can be found in your PATH. Again, ~/bin directory is a good place.
* Make sure that the uv_hal library is fetched from the version control system:

git submodule update --init

* Execute command: 

make

##Flashing the UV0D
* Make sure you have CAN-USB connector connected to your computer. On Windows PEAK PCAN-USB is supported, on Linux any SocketCAN compatible adapter is OK.
* Power up the UV0D and connect it to the CAN-USB adapter.
* Make sure to have at least one 120 Ohm terminating resistor in the CAN-bus, between CANH and CANL.
* To test the CAN-bus, type a command: 

uvcan --listen

* **uvcan** should log messages coming from the UV0D display. The default Node-ID of the display is 0x0D. Press Ctrl+C to exit.
* To flash the firmware to the UV0D, run the command: 

uvcan --nodeid 0xd --loadbin binary.bin

* The UV0D resets itself and the binary is executed automatically

##In case of error
* If flashing the UV0D fails, for example the transmission is distrubed, it will fail to start up the corrupted binary. In that case, a new firmware can be installed with the same command.
* If the UV0D is flashed with a firmware that has a lethal bug in it, for example an infinite loop, flashing the new firmware might not be possible. In this case:
	* Turn of the power from the UV0D
	* run command:

uvcan --nodeid 0xd --loadbinwfr binary.bin

	* Turn on the power to the UV0D
	* Loading the firmware should start once the UV0D is reset. This is how the Usevolt bootloader works. No matter of the firmware downloaded to the microcontroller, the Usevolt bootloader runs always before the application firmware. Thus, downloading a new firmware is always possible after the boot up before the application firmware is started. 

##Flashing media files to the UV0D external flash
* Run command:

uvcan --nodeid 0xd --loadmedia path/to/media

Where *path/to/media* can either be a .jpg, .jpeg or .png image, or a directory. Image files are downloaded as is, but if a directory is given, the **uvcan** will automatically search the directory and download all supported image files found inside the directory into the UV0D. Recursive search of directories is not supported.

##Command line interface with UV0D
* A development command line interface with the UV0D can be opened by running command:

uvcan --nodeid 0xd --terminal

* The command line interface of the UV0D is disabled until it receives any single character from the command line. 
* The interface can be used while developing for example logging printf-statements via CAN-bus, resetting the UV0D, saving non-volatile data or reverting the non-volatile data to default values. Also, the user application can specify it's own commands. See messages.h & messages.c for example of the command line commands.

##Software development
The software development can be done using any text editor, IDE or such. However, the preferred editor is [Eclipse](https://www.eclipse.org/cdt/), since it is a commonly used and customizable editor. This project already contains eclipse CDT project files (.project & .cproject). The project can be opened up in Eclipse by choosing File->Import, and selecting "Existing Projects into the Workspace" under "General". 

To set the Eclipse settings for the project development:
* Go to Project->Properties->C/C++ Build and check that the "Build location" is set correctly to where the project is on your computer
* Got to Run->Run Configurations->uvcan_ and set C/C++ Application to point to the *uvcan* software on your computer.

After these, the project should compile with Ctrl+B and when the CAN-USB connector is connected to the powered on UV0D, the firmware can be downloaded to the UV0D with Ctrl+R, or by selecting Run->Run As->uvcan_
