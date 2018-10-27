Arduino Video Game Controller via Windows API
=
[![License: Unlicense](https://img.shields.io/badge/license-Unlicense-blue.svg)](http://unlicense.org/)

Introduction
-
The repository demonstrates my attempt to create a video game controller with Arduino. The external hardware communicates with the Arduino which interprets the inputs. These interpretations are then sent to the computer via serial to a C++ Win32 GUI application. This application then sends these inputs to a specified running application.

![alt text][pic1]

[pic1]: https://github.com/trevortomesh/OSHRepo/blob/master/img/img1.jpg "Logo Title Text 2"

Repository Contents
-
* **/examples** - Example files that can be run on your hardware. 
* **/img** - This is where the image files for this readme.
* **/LICENSE** - The license file.
* **/README.md** - The file you're reading now!

Arduino Specific:
  * **/src** - Here's where the software for your device goes (.ino, .cpp).
  * **/hardware** - All the PCB design files / 3D models (.ftz, .brd, .sch, .stl).
  * **/build** - Files that are compiled and ready to run / upload.
  * **/libraries** - Any libraries that are needed to build your software for your device.

Win32 Specific:
  * **/CS207Project** - All files required for the Win32 Application
  * **CS207Project.sln** - The solution file to quickly load the project into Visual Studio

Requirements and Materials
-
Dependencies:
* energia-1.6.10E18 https://www.energia.nu
* msp430 command-line flasher https://www.ti.com/tool/msp430-flasher
* important libraries that need to be installed

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

Firmware Installation
-
This is where you should describe how the firmware is installed onto the device. If it's really straightforward you may not need this section. However, if there are multiple libraries and componenets involved -- or if there is some sort of build process, this is a good place to put those instructions. Most users just want to be able to copy-paste and upload the firmware without having to jump through a bunch of hoops. You should set it up for them. For example: 

To install:
```bash
MSP430Flasher.exe -n Unknown -w "MyGameFile_v1.2.txt" -v -g -z [VCC]

```


Usage
-
This is usually where you tell the user how the device works. Do you just upload the software and flip a switch? What sort of things does this thing do? Are there alternate settings / modes / programs that might be good to mention. This is where you tell the user exactly how the device or program is used. For example: 

* Upload the code to the thing. 
* Turn the thing on. 
* The thing will do a thing and it'll be really cool. 
* Don't forget to feed the badgers!

Team
-
The build team consists of: 
* Matthew Polsom
"I did everything." - Guy who did everything

Credits
-

This is where you give credit to any third parties that you borrowed from. 

* Kenneth Reitz - consultation on directory structure
* My wonderful class. :-)
