/*
	File: defines.h

	Purpose:
		This file holds all definitions for the applicaiton.
		These should typically not be changed.
*/

#pragma once

// Clarity of the use of static
#define local_persist	static	// Local variable that persists beyond scope lifetime
#define global_variable static	// Global variable
#define internal		static	// Scope limited to this translation unit

// LoadString
#define MAX_LOADSTRING 100

// Windows GetKeyState
#define PRESSED 0x8000 // High bit detects key presses
#define TOGGLED 0x0001 // Low bit detects toggle

// Size of array
#define ARRAY_SIZE(X) (sizeof(X) / sizeof(X[0])) // Static arrays only

// Debug output
#define DEBUG_MSG(X) do { std::cout << X << std::endl; } while (FALSE)										// Debug only message
#define FILENAME (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)							// Remove extraneous filepath
#define DEBUG_FUNCTION_CALLS std::cout << FILENAME << "\t" << __LINE__ << "\t" << __FUNCSIG__ << std::endl	// Place at the top of functions

// Debug levels
#define DEBUG_OFF 0			// No output
#define DEBUG_ON 1			// Normal output
#define DEBUG_VERBOSE 2		// Verbose output
