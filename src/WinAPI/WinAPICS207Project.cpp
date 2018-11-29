/*
	File: WinAPICS207Project.cpp
	Purpose: Entry point to the program
	Date: 28th Nov. 2018
*/




#include "pch.h"
#include "defines.h"




// Author: Leherenn at https://stackoverflow.com/questions/304986/how-do-i-get-the-friendly-name-of-a-com-port-in-windows
void EnumerateSerialPortsFriendlyNames()
{
	SP_DEVINFO_DATA devInfoData = {};
	devInfoData.cbSize = sizeof(devInfoData);

	// get the tree containing the info for the ports
	HDEVINFO hDeviceInfo = SetupDiGetClassDevs(&GUID_DEVCLASS_PORTS,
		0,
		nullptr,
		DIGCF_PRESENT
	);
	if (hDeviceInfo == INVALID_HANDLE_VALUE)
	{
		return;
	}

	tcout << "List of used COM ports:\n";

	// iterate over all the devices in the tree
	int nDevice = 0;
	while (SetupDiEnumDeviceInfo(hDeviceInfo,            // Our device tree
		nDevice++,            // The member to look for
		&devInfoData))
	{
		DWORD regDataType;
		DWORD reqSize = 0;

		// find the size required to hold the device info
		SetupDiGetDeviceRegistryProperty(hDeviceInfo, &devInfoData, SPDRP_HARDWAREID, nullptr, nullptr, 0, &reqSize);
		BYTE* hardwareId = new BYTE[(reqSize > 1) ? reqSize : 1];
		// now store it in a buffer
		if (SetupDiGetDeviceRegistryProperty(hDeviceInfo, &devInfoData, SPDRP_HARDWAREID, &regDataType, hardwareId, sizeof(hardwareId) * reqSize, nullptr))
		{
			// find the size required to hold the friendly name
			reqSize = 0;
			SetupDiGetDeviceRegistryProperty(hDeviceInfo, &devInfoData, SPDRP_FRIENDLYNAME, nullptr, nullptr, 0, &reqSize);
			BYTE* friendlyName = new BYTE[(reqSize > 1) ? reqSize : 1];
			// now store it in a buffer
			if (!SetupDiGetDeviceRegistryProperty(hDeviceInfo, &devInfoData, SPDRP_FRIENDLYNAME, nullptr, friendlyName, sizeof(friendlyName) * reqSize, nullptr))
			{
				// device does not have this property set
				memset(friendlyName, 0, reqSize > 1 ? reqSize : 1);
			}
			// use friendlyName here
			tcout << friendlyName << std::endl;
			delete[] friendlyName;
		}
		delete[] hardwareId;
	}
}




INT _tmain(INT argc, TCHAR *argv[])
{
	UNREFERENCED_PARAMETER(argc);
	UNREFERENCED_PARAMETER(argv);


	// Print the COM port names
	EnumerateSerialPortsFriendlyNames();

	// User COM port selection
	INT ComPortNum = -1;
	tcout << "Enter the number of the COM port to connect to: ";
	tcin >> ComPortNum;
	std::string s = "\\\\.\\COM" + std::to_string(ComPortNum);
	CONST CHAR *ComPortName = { s.c_str() };
	

	// Connect to the COM port
	Serial* SP = new Serial(ComPortName);

	if (SP->IsConnected())
	{
		LOG("Connected to port ", ComPortName, '\n');
	}
	
	CHAR IncomingData[256] = {};
	INT DataLength = 255;
	INT ReadResult = 0;

	// Read the incoming data from the COM port
	while (SP->IsConnected())
	{
		ReadResult = SP->ReadData(IncomingData, DataLength);
		if (!ReadResult) // No data received
		{
			continue;
		}

		IncomingData[ReadResult] = 0;

		LOG(IncomingData, '\n');
	}

	return 0;
}
