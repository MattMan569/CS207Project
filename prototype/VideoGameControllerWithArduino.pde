/*
  File: VideoGameControllerWithArduino.pde
  
  Purpose: This file is the slightly modified original from
    https://www.instructables.com/id/Video-Game-Controller-With-Arduino/
    that will serve as the base for my own project to build off of.
*/

import processing.serial.*;
import java.awt.AWTException;
import java.awt.Robot;
import java.awt.event.InputEvent;
import java.awt.event.KeyEvent;
import javax.swing.KeyStroke;


Serial MyPort;                                
String KeyString = "";


void setup()
{
  System.out.println("Hi");
  size(700, 500);
  MyPort = new Serial(this, "COM6", 1000000);// Enter the COM on which your Arduino is on.
  MyPort.bufferUntil('\n');
}


void draw()
{
  background(0, 0, 0);
  fill(255, 0, 0);
  text("Press any key", 100, 175);
}


void serialEvent(Serial MyPort)throws Exception
{
   KeyString = MyPort.readStringUntil('\n');
   KeyString = KeyString.substring(0, KeyString.indexOf(':'));//The string is split. the whole string leaving the colon is taken
   System.out.println(KeyString);//prints the serial string for debugging purpose
   Robot Arduino = new Robot();//Constructor of robot class
   
   switch(KeyString)
   {
     case "1" :
       Arduino.keyPress(KeyEvent.VK_LEFT);
       Arduino.keyRelease(KeyEvent.VK_LEFT);
       break;
     case "2" :
       Arduino.keyPress(KeyEvent.VK_UP);
       Arduino.keyRelease(KeyEvent.VK_UP);
       break;
     case "3" :
       Arduino.keyPress(KeyEvent.VK_DOWN);
       Arduino.keyRelease(KeyEvent.VK_DOWN);      
       break;
     case "4" :
       Arduino.keyPress(KeyEvent.VK_RIGHT);
       Arduino.keyRelease(KeyEvent.VK_RIGHT);      
       break;
   }
   
}
