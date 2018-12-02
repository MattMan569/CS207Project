/*
	File: pch.h
	Purpose: Holds all precompiled headers
*/

#pragma once

#pragma comment (lib, "Setupapi.lib")

#pragma warning(push, 0);

// Third party headers
#include "SerialClass.h"

// Windows headers
#include <Windows.h>
#include <tchar.h>
#include <atlstr.h>
#include <cstring>
#include <initguid.h>
#include <devguid.h>
#include <setupapi.h>

// Standard C++ headers
#include <iostream>
#include <thread>
#include <chrono>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <ctime>
#include <iomanip>

#pragma warning(pop);

// Custom headers

