/*
 * File: defines.h
 * Author: Matthew Polsom
 * Purpose: This file contains all preprocessor definitions for the program
 *          such as pin numbers, macros, and addresses
 */


#pragma once


// Debug mode
#define DEBUG false


// Serial baud rate
#define BAUD_RATE 1000000


// Debug only output
#if DEBUG
#define LOG(X) Serial.flush(); Serial.print(X)
#define LOGN(X) Serial.flush(); Serial.println(X)
#else
#define LOG(X) NULL
#define LOGN(X) NULL
#endif


// If not
#define ifn(X) if(!(X))


// MCP23008 definitions
#define IC1     0x20  // The first MCP23008 at address 0x20
#define IC2     0x22  // The second MCP23008 at address 0x22
#define IODIR   0x00  // The IODIR register is at address 0x00
#define GPPU    0x06  // The GPPU register is at address 0x06
#define GPIO    0x09  // The GPIO register is at address 0x09


// Controller bitwise input positions in the MCP23008 ICs
#define C_DOWN    0x1
#define C_RIGHT   0x2
#define A         0x4
#define C_UP      0x8
#define B         0x10
#define C_LEFT    0x20
#define Z         0x40
#define RB        0x80
#define LB        0x100
#define D_RIGHT   0x200
#define D_DOWN    0x400
#define D_UP      0x800
#define D_LEFT    0x1000
#define START     0x2000


// Joystick pins
#define JOY_Y       A0
#define JOY_X       A1
#define JOY_CLICK   A2

// Joystick values
#define JOY_CENTRE 518
#define JOY_DEADZONE 100
