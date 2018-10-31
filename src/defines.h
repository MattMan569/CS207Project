#pragma once


// Debug mode
#define DEBUG true

// Serial baud rate
#define BAUD_RATE 2000000




// Debug only output
#if DEBUG
#define LOG(X) Serial.flush(); Serial.print(X)
#else
#define LOG(X) NULL
#endif // DEBUG

// Return codes
#define RETURN_SUCCESS 0
#define RETURN_FAILURE 1

// Clarify the usage of static
#define local_persist   static
#define global_variable static
#define internal        static
