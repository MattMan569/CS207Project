/*
 * File: CS207Project.ino
 * Author: Matthew Polsom
 * Purpose: This file is the entry point and point of processing all inputs
 *          and sending the corresponding outputs via serial.
 */


// Use our own main, setup, and loop functions
#define setup ARDUINO_SETUP
#define loop ARDUINO_LOOP
#include <Arduino.h>
#undef setup
#undef loop

#include "defines.h"

#include <Wire.h>




int main()
{
  init();
  Serial.begin(BAUD_RATE);

  // Run setup
  Serial.print("setup_begin:");
  setup();
  Serial.print("setup_end:");

  // Run the loop
  Serial.print("loop_begin:");
  while(loop());
  Serial.print("loop_end:");
  
  return 0;
}




void setup()
{
#if DEBUG
  Serial.print("debug_on:");
#else
  Serial.print("debug_off:");
#endif

  // Start the I2C communication
  Wire.begin();

  //Set all GPIO pins to input mode
  Wire.beginTransmission(IC1);
  Wire.write(IODIR);
  Wire.write(0b11111111);
  Wire.endTransmission();
  Wire.beginTransmission(IC2);
  Wire.write(IODIR);
  Wire.write(0b11111111);
  Wire.endTransmission();

  // Enable the internal pull-up resistor on all pins
  Wire.beginTransmission(IC1);
  Wire.write(GPPU);
  Wire.write(0b11111111);
  Wire.endTransmission();
  Wire.beginTransmission(IC2);
  Wire.write(GPPU);
  Wire.write(0b11111111);
  Wire.endTransmission();
}




int loop()
{
  while (true)
  {
    Serial.flush();

    unsigned short gpio{0};

    // Read the input from IC1
    Wire.beginTransmission(IC1);
    Wire.write(GPIO);
    Wire.endTransmission();
    Wire.requestFrom(IC1, 1);
    gpio |= Wire.read();
    
    LOG(gpio);
    LOG("\t\t");
    
    // Shift the bits by one byte to make room for IC2's input
    gpio = gpio << 8;
    
    LOG(gpio);

    // Read the input from IC2
    Wire.beginTransmission(IC2);
    Wire.write(GPIO);
    Wire.endTransmission();
    Wire.requestFrom(IC2, 1);
    gpio |= Wire.read();

    LOG("\t\t");
    LOGN(gpio);

    Serial.println(enumerateInputs(gpio));
  }
  
  return 0;
}




// Enumerate all inputs and check if its corresponding bit is set.
// Also check the joystick input.
String enumerateInputs(const unsigned short & gpio)
{
  String inputs{""};

  // Check all MCP23008 inputs
  ifn (A & gpio)       inputs += "a:";
  ifn (B & gpio)       inputs += "b:";
  ifn (Z & gpio)       inputs += "z:";
  ifn (RB & gpio)      inputs += "rb:";
  ifn (LB & gpio)      inputs += "lb:";
  ifn (C_LEFT & gpio)  inputs += "cl:";
  ifn (C_UP & gpio)    inputs += "cu:";
  ifn (C_RIGHT & gpio) inputs += "cr:";
  ifn (C_DOWN & gpio)  inputs += "cd:";
  ifn (D_LEFT & gpio)  inputs += "dl:";
  ifn (D_UP & gpio)    inputs += "du:";
  ifn (D_RIGHT & gpio) inputs += "dr:";
  ifn (D_DOWN & gpio)  inputs += "dd:";
  ifn (START & gpio)   inputs += "s:";

  // Check the joystick input
  if (analogRead(JOY_X) > (JOY_CENTRE + JOY_DEADZONE)) inputs += "l:";  // Left
  if (analogRead(JOY_X) < (JOY_CENTRE - JOY_DEADZONE)) inputs += "r:";  // Right
  if (analogRead(JOY_Y) > (JOY_CENTRE + JOY_DEADZONE)) inputs += "d:";  // Down
  if (analogRead(JOY_Y) < (JOY_CENTRE - JOY_DEADZONE)) inputs += "u:";  // Up

  return inputs;
}
