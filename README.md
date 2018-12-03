Arduino Video Game Controller via Windows API
=
[![License: Unlicense](https://img.shields.io/badge/license-Unlicense-blue.svg)](http://unlicense.org/)

Introduction
-
This repository demonstrates my attempt to create a video game controller with Arduino. A user created controller is connected to the Arduino. This controller sends its inputs to the Arduino which in turn then sends data to the target computer via USB. An intermediate C++ program employs the Windows API to then read these inputs from the COM port and send the corresponding inputs to the most foreground application.

![alt text][pic2]

[pic2]: https://github.com/MattMan569/CS207Project/blob/master/img/build_pic.jpg "CS 207 Build Picture"

![alt text][pic3]

[pic3]: https://github.com/MattMan569/CS207Project/blob/master/img/build_exe.png "CS 207 Exe Console"

How It Works
-
<b>Controller:</b><br />
The controller, in its current setup, has a number of buttons and a joystick. This layout has one button for each button on a Nintendo 64 controller as well as an analog joystick. The inputs from the buttons are loaded into two MCP23008 ICs as a means of reducing the required number of wires between the breadboard and Arduino. These values can then be read by the Arduino via the I2C Wire connection. The joystick values are input directly into the Arduino's analog input pins.

<b>Arduino:</b><br />
The Arduino is responsible for collecting the incoming data from the controller, processing it, and sending the necessary information to the intermediate C++ program via its USB connection to a Windows computer COM port. The Arduino continuously polls for incoming information from the controller's ICs as well as the connected analog pins. If a particular input state is set, the Arduino will send a message via USB to the intermediate C++ program providing this information. The Arduino is also responsible for configuring the MCP23008s on the controller.

<b>Windows:</b><br />
The Windows C++ program collects the incoming informaton from a specified COM port. It will perform bitwise operations on the incoming data to determine which inputs are currently active and then make the appropriate operations based on this current state as well as previous states. The end result is these inputs being output to an external program.

Repository Contents
-
* **/img** - This is where the image files for this readme.
* **/LICENSE** - The license file.
* **/README.md** - The file you're reading now!
* **/src** - All software files for the project
  * */src/Arduino* - All code required for the Arduino program
  * */src/WinAPI* - All code required for the Windows program
  * */src/Win32* - Code for a planned Win32 expansion of the WinAPI code. Currently defunct.
* **/build** - A pre-built version of the WinAPI application
* **/prototype** - Files for prototyping purposes, as per the project proposal, kept for the purposes of documentation

Requirements and Materials
-
Dependencies:
* Setupapi.lib - Included in Windows SDK and Visual Studio development kit
* Arduino & CPP Serial Library (included) - http://playground.arduino.cc/Interfacing/CPPWindows

Bill of Materials:
* 1 x Arduino (any model or equivalent brand)
* 1 x Arduino to USB cable
* 1 x large breadboard
* 14 x momentary pushbuttons
* 1 x joystick
* 57 x wires
* 1 x Windows computer

Build Instructions
-
![alt text][pic1]

[pic1]: https://github.com/MattMan569/CS207Project/blob/master/img/cs207_schem.png "CS 207 Build Schematic"

Usage
-
* Plug the Arduino into the target Windows computer via USB
* Start the intermediate C++ program on the target computer
* Select the COM port the Arduino is connected to in the C++ program
* Bring the target appliction to the foreground (click on it)
* Use your Arduino controller to send input to the target application

Team
-
* Matthew Polsom

Credits
-
* https://www.instructables.com/id/Video-Game-Controller-With-Arduino/ - Original project
* http://www.learningaboutelectronics.com/Articles/MCP23008-IO-port-expander-circuit-with-arduino.php - MCP23008 introduction
* http://www.learningaboutelectronics.com/Articles/Read-input-from-an-MCP230xx-IO-port-expander-connected-to-an-arduino.php - MCP23008 examples
* http://playground.arduino.cc/Interfacing/CPPWindows - Serial communication library
* https://stackoverflow.com/a/29326744 - Overloaded ostream operators for variadic macro communication
* https://stackoverflow.com/a/45613884 - Retrieve the list of currently active COM ports and print friendly names
