/*
	File: config.h

	Purpose:
		This file contains all configurable options for the application.
		These can be changed to suit your needs.
*/

#pragma once

#include "defines.h"

// DEBUG_OFF		- No debug output
// DEBUG_ON			- Normal debug output
// DEBUG_VERBOSE	- Verbose debug output
#define DEBUG_MODE DEBUG_VERBOSE

// Name of the window class
global_variable
_TCHAR szWindowClass[] = _TEXT("cs207project");

// Title of the window
global_variable
_TCHAR szTitle[] = _TEXT("CS 207 Project");
