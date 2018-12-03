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
    LOG(gpio);

    // Send the enumerated input to the C++ program
    Serial.flush();
    Serial.println(enumerateInputs(gpio));
  }
  
  return 0;
}




// Enumerate all inputs and check if its corresponding bit is set.
// Also check the joystick input.
unsigned long enumerateInputs(const unsigned short & gpio)
{
  unsigned long inputs{0x1};

  // Check all MCP23008 inputs
  // Set the appropriate bit if an input is active
  // 0x1 is reserved
  ifn (A & gpio)       inputs |= 0x2;
  ifn (B & gpio)       inputs |= 0x4;
  ifn (Z & gpio)       inputs |= 0x8;
  ifn (START & gpio)   inputs |= 0x10;
  ifn (LB & gpio)      inputs |= 0x20;
  ifn (RB & gpio)      inputs |= 0x40;
  ifn (C_LEFT & gpio)  inputs |= 0x80;
  ifn (C_UP & gpio)    inputs |= 0x100;
  ifn (C_RIGHT & gpio) inputs |= 0x200;
  ifn (C_DOWN & gpio)  inputs |= 0x400;
  ifn (D_LEFT & gpio)  inputs |= 0x800;
  ifn (D_UP & gpio)    inputs |= 0x1000;
  ifn (D_RIGHT & gpio) inputs |= 0x2000;
  ifn (D_DOWN & gpio)  inputs |= 0x4000;

  // Check the joystick input
  if (analogRead(JOY_X) > (JOY_CENTRE + JOY_DEADZONE)) inputs |= 0x8000;   // Left
  if (analogRead(JOY_X) < (JOY_CENTRE - JOY_DEADZONE)) inputs |= 0x10000;  // Right
  if (analogRead(JOY_Y) > (JOY_CENTRE + JOY_DEADZONE)) inputs |= 0x20000;  // Down
  if (analogRead(JOY_Y) < (JOY_CENTRE - JOY_DEADZONE)) inputs |= 0x40000;  // Up

  LOG("\t\t");
  LOGN(inputs);

  return inputs;
}
