Arduino Video Game Controller via Windows API
=
[![License: Unlicense](https://img.shields.io/badge/license-Unlicense-blue.svg)](http://unlicense.org/)

Introduction
-
This repository demonstrates my attempt to create a video game controller with Arduino. A user created controller is connected to the Arduino. This controller sends its inputs to the Arduino which in turn then sends data to the target computer via USB. An intermediate C++ program employs the Windows API to then read these inputs from the COM port and send the corresponding inputs to the most foreground application.

Repository Contents
-
* **/img** - This is where the image files for this readme.
* **/LICENSE** - The license file.
* **/README.md** - The file you're reading now!
* **/src** - All software files for the project
* **/build** - A pre-built version of the Win32 application
* **/prototype** - Files for prototyping purposes, as per the project proposal, kept for the purposes of documentation

Requirements and Materials
-
Dependencies:
* Setupapi.lib - Included in Windows SDK and Visual Studio development kit

Bill of Materials:
* 4 x push buttons
* 12 x green LEDs
* 1 x 4.7k resistor
* 4 x 220 ohm resistor
* 1 x slide switch
* 1 x battery holder
* 1 x breadboard
* 1 x MSP4302553

Build Instructions
-
Here is where you give specific instructions about how the device is built. The more detail the better -- especially if your build is very complicated. Here you should include schematics of your build: 

![alt text][pic2]

[pic2]: https://github.com/trevortomesh/OSHRepo/blob/master/img/img2.jpg "Logo Title Text 2"

And a breadboard view is also a good idea. It gives the potential user a better idea of how to put the thing together. So we'll throw one in here as well. 

![alt text][pic3]

[pic3]: https://github.com/trevortomesh/OSHRepo/blob/master/img/img3.jpg "Logo Title Text 2"

![alt_text][pic4]
  
[pic4]: https://github.com/trevortomesh/OSHRepo/blob/master/folderName/joystick.png "This is some alt text"


If there are any special instructions on how to assemble the hardware, we should note it here as well. For example, if the user should solder things in a specific order, you should give them a heads-up. 

Usage
-
This is usually where you tell the user how the device works. Do you just upload the software and flip a switch? What sort of things does this thing do? Are there alternate settings / modes / programs that might be good to mention. This is where you tell the user exactly how the device or program is used. For example: 

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
This is where you give credit to any third parties that you borrowed from. 

* MSDN - Excellent documentation for the Windows API
