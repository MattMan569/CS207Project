/*
	File: WindowsCOMTest.cpp
	Purpose: This file tests the ability to read input from a COM port on Windows.
	Date: 28th Nov. 2018

	Based off of the example at: http://playground.arduino.cc/Interfacing/CPPWindows
*/

#pragma comment (lib, "Setupapi.lib")

#ifdef UNICODE
#define tcout std::wcout
#define tcin std::wcin
#define tcerr std::wcerr
#else
#define tcout std::cout
#define tcin std::cin
#define tcerr std::cerr
#endif

#pragma warning(push, 0);
#include <Windows.h>
#include <tchar.h>
#include <iostream>
#include <stdio.h>
#include <thread>
#include <chrono>
#include <string>
#include <SetupAPI.h>
#include "SerialClass.h"
#pragma warning(pop);




INT _tmain(INT argc, TCHAR *argv[])
{
	UNREFERENCED_PARAMETER(argc);
	UNREFERENCED_PARAMETER(argv);

	/*
	HDEVINFO x = SetupDiGetClassDevs(NULL, "USB", NULL, DIGCF_PRESENT);
	tcout << x << std::endl;
	*/

	Serial* SP = new Serial("\\\\.\\COM6");

	if (SP->IsConnected())
		tcout << _TEXT("We're connected");

	char incomingData[256] = {};
	int dataLength = 255;
	int readResult = 0;

	while (SP->IsConnected())
	{
		readResult = SP->ReadData(incomingData, dataLength);
		if (!readResult)
			continue;

		// printf("Bytes read: (0 means no data available) %i\n",readResult);
		incomingData[readResult] = 0;

		printf("%s", incomingData);

		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}

	return 0;
}

