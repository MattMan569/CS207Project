/*
	File: WinAPICS207Project.cpp
	Purpose: Entry point to the program
	Date: 28th Nov. 2018
*/




#include "pch.h"
#include "defines.h"




//
void ProcessSerial(const uint32 &);

// Print a user friendly version of COM ports currently in use
void EnumerateSerialPortsFriendlyNames();




int _tmain(int argc, TCHAR *argv[])
{
	// Prevent unreferenced parameter warnings
	UNREFERENCED_PARAMETER(argc);
	UNREFERENCED_PARAMETER(argv);

	// Print the COM port names
	EnumerateSerialPortsFriendlyNames();

	// User COM port selection
	int ComPortNum = -1;
	tcout << _TEXT("Enter the number of the COM port to connect to: ");
	tcin >> ComPortNum;
	while (tcin.fail()) // Validate input
	{
		tcerr << "Please enter an integer.\n";
		tcin.clear();
		tcin.ignore(INT_MAX, '\n');
		tcin >> ComPortNum;
	}

	// Put the selection in a c-string
	std::string s = "\\\\.\\COM" + std::to_string(ComPortNum);
	const char *ComPortName = { s.c_str() };

	// Connect to the specified COM port
	Serial* SP = new Serial(ComPortName);
	if (SP->IsConnected())
	{
		tcout << _TEXT("Connected to port ") << ComPortName << std::endl;
	}

	// Read the incoming data from the COM port while it remains connected
	while (SP->IsConnected())
	{
		char IncomingData[256] = {};
		int DataLength = 255;
		int ReadResult = 0;

		// Check for incoming data
		ReadResult = SP->ReadData(IncomingData, DataLength);
		if (!ReadResult) // No data received
		{
			continue;
		}

#if DEBUG
		uint64 clock_start{ __rdtsc() };
#endif

		// Ensure there is no null terminator
		IncomingData[ReadResult] = 0;

		LOG(_TEXT(IncomingData));

		// Prevent communication errors by requiring the same input
		// for at least two loops before being processed
		local_persist std::string PrevIncomingData{};
		if (IncomingData != PrevIncomingData)
		{
			PrevIncomingData = IncomingData;
			continue;
		}

		ProcessSerial(strtoul(IncomingData, nullptr, NULL));

#if DEBUG
		uint64 clock_end{ __rdtsc() };
		LOG("Loop time: ", (clock_end - clock_start) / 10000, '\n');
#endif
	}

	return 0;
}




//
void ProcessSerial(const uint32 & Serial)
{
	tcout << Serial << std::endl;
}




// Author: Leherenn at https://stackoverflow.com/questions/304986/how-do-i-get-the-friendly-name-of-a-com-port-in-windows
void EnumerateSerialPortsFriendlyNames()
{
	SP_DEVINFO_DATA devInfoData = {};
	devInfoData.cbSize = sizeof(devInfoData);

	// Get the tree containing the info for the ports
	HDEVINFO hDeviceInfo = SetupDiGetClassDevs(&GUID_DEVCLASS_PORTS,
		0,
		nullptr,
		DIGCF_PRESENT
	);
	if (hDeviceInfo == INVALID_HANDLE_VALUE)
	{
		return;
	}

	tcout << _TEXT("List of active COM ports:\n");

	// Iterate over all the devices in the tree
	int nDevice = 0;
	while (SetupDiEnumDeviceInfo(hDeviceInfo,   // Our device tree
		nDevice++,								// The member to look for
		&devInfoData))
	{
		DWORD regDataType;
		DWORD reqSize = 0;

		// Find the size required to hold the device info
		SetupDiGetDeviceRegistryProperty(hDeviceInfo, &devInfoData, SPDRP_HARDWAREID, nullptr, nullptr, 0, &reqSize);
		BYTE* hardwareId = new BYTE[(reqSize > 1) ? reqSize : 1];
		// Now store it in a buffer
		if (SetupDiGetDeviceRegistryProperty(hDeviceInfo, &devInfoData, SPDRP_HARDWAREID, &regDataType, hardwareId, sizeof(hardwareId) * reqSize, nullptr))
		{
			// Find the size required to hold the friendly name
			reqSize = 0;
			SetupDiGetDeviceRegistryProperty(hDeviceInfo, &devInfoData, SPDRP_FRIENDLYNAME, nullptr, nullptr, 0, &reqSize);
			BYTE* friendlyName = new BYTE[(reqSize > 1) ? reqSize : 1];
			// Now store it in a buffer
			if (!SetupDiGetDeviceRegistryProperty(hDeviceInfo, &devInfoData, SPDRP_FRIENDLYNAME, nullptr, friendlyName, sizeof(friendlyName) * reqSize, nullptr))
			{
				// Device does not have this property set
				memset(friendlyName, 0, reqSize > 1 ? reqSize : 1);
			}
			// Print the friendly names
			tcout << _TEXT(friendlyName) << std::endl;
			delete[] friendlyName;
		}
		delete[] hardwareId;
	}
}
