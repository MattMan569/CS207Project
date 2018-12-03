/*
	File: WinAPICS207Project.cpp
	Purpose: Entry point to the program
*/




#include "pch.h"
#include "defines.h"




// Bitwise process the incoming serial data
void ProcessSerial(const uint32 &);

// Send the specified lists of inputs
void SendInputs(const std::string &, const std::string &);

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
		// Delay to give the Arduino time to reset
		// Also print a waiting message
		for (int i = 0; i < ARDUINO_DELAY_CYCLES; ++i)
		{
			uint8 NumDots = 3;
			tcout << _TEXT("\rPlease wait" + std::string(NumDots, ' '));
			for (int j = 0; j < NumDots; ++j)
			{
				Sleep(WAIT_MSG_DELAY_MS);
				tcout << _TEXT("\rPlease wait" + std::string(j + 1, '.'));
			}
			Sleep(WAIT_MSG_DELAY_MS);
		}

		tcout << _TEXT("\rConnected to port ") << ComPortName << std::endl;
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
		
		IncomingData[ReadResult] = 0;
		
		// Convert the incoming char array into an integer
		std::stringstream IncomingStream{ IncomingData };
		uint32 IncomingInteger{};
		IncomingStream >> IncomingInteger;

#if DEBUG
		uint64 clock_start{ __rdtsc() };
#endif
		
		// Prevent communication errors by requiring the same input
		// for at least two loops before being processed
		local_persist uint32 PrevIncomingInteger{ 0x0 };
		if (IncomingInteger != PrevIncomingInteger)
		{
			PrevIncomingInteger = IncomingInteger;
			continue;
		}

		// Process the input
		ProcessSerial(IncomingInteger);

#if DEBUG
		uint64 clock_end{ __rdtsc() };
		LOG("Loop time: ", (clock_end - clock_start) / 10000, '\n');
#endif
	}

	return 0;
}




// Bitwise process the incoming serial data
void ProcessSerial(const uint32 & Serial)
{
	LOG(Serial, _TEXT("\n"));

	// Keep track of button presses and releases
	// There is no need to constantly send keydown commands,
	// only send one keydown when pressed and a keyup when released.
	local_persist bool Was_A{ false };
	local_persist bool Was_B{ false };
	local_persist bool Was_Z{ false };
	local_persist bool Was_START{ false };
	local_persist bool Was_LB{ false };
	local_persist bool Was_RB{ false };
	local_persist bool Was_C_LEFT{ false };
	local_persist bool Was_C_UP{ false };
	local_persist bool Was_C_RIGHT{ false };
	local_persist bool Was_C_DOWN{ false };
	local_persist bool Was_D_LEFT{ false };
	local_persist bool Was_D_UP{ false };
	local_persist bool Was_D_RIGHT{ false };
	local_persist bool Was_D_DOWN{ false };
	local_persist bool Was_JOY_LEFT{ false };
	local_persist bool Was_JOY_RIGHT{ false };
	local_persist bool Was_JOY_DOWN{ false };
	local_persist bool Was_JOY_UP{ false };

	std::string KeyDown{};
	std::string KeyUp{};

	/*
		Check if the inputs are active via bitwise operations
		on the incoming serial data.
		If it is active and was not already pressed, send a keydown command.
		if it is not active and was previously active, send a keyup command.
		Else, do nothing.
	*/

	if ((Serial & A) && !Was_A)
	{
		KeyDown += 'V';
		Was_A = true;
	}
	else if (Was_A && !(Serial & A))
	{
		KeyUp += 'V';
		Was_A = false;
	}

	if ((Serial & B) && !Was_B)
	{
		KeyDown += 'C';
		Was_B = true;
	}
	else if (Was_B && !(Serial & B))
	{
		KeyUp += 'C';
		Was_B = false;
	}

	if ((Serial & Z) && !Was_Z)
	{
		KeyDown += 'Z';
		Was_Z = true;
	}
	else if (Was_Z && !(Serial & Z))
	{
		KeyUp += 'Z';
		Was_Z = false;
	}

	if ((Serial & START) && !Was_START)
	{
		KeyDown += 'R';
		Was_START = true;
	}
	else if (Was_START && !(Serial & START))
	{
		KeyUp += 'R';
		Was_START = false;
	}

	if ((Serial & LB) && !Was_LB)
	{
		KeyDown += 'Q';
		Was_LB = true;
	}
	else if (Was_LB && !(Serial & LB))
	{
		KeyUp += 'Q';
		Was_LB = false;
	}

	if ((Serial & RB) && !Was_RB)
	{
		KeyDown += 'E';
		Was_RB = true;
	}
	else if (Was_RB && !(Serial & RB))
	{
		KeyUp += 'E';
		Was_RB = false;
	}

	if ((Serial & C_LEFT) && !Was_C_LEFT)
	{
		KeyDown += 'J';
		Was_C_LEFT = true;
	}
	else if (Was_C_LEFT && !(Serial & C_LEFT))
	{
		KeyUp += 'J';
		Was_C_LEFT = false;
	}

	if ((Serial & C_UP) && !Was_C_UP)
	{
		KeyDown += 'I';
		Was_C_UP = true;
	}
	else if (Was_C_UP && !(Serial & C_UP))
	{
		KeyUp += 'I';
		Was_C_UP = false;
	}

	if ((Serial & C_RIGHT) && !Was_C_RIGHT)
	{
		KeyDown += 'L';
		Was_C_RIGHT = true;
	}
	else if (Was_C_RIGHT && !(Serial & C_RIGHT))
	{
		KeyUp += 'L';
		Was_C_RIGHT = false;
	}

	if ((Serial & C_DOWN) && !Was_C_DOWN)
	{
		KeyDown += 'K';
		Was_C_DOWN = true;
	}
	else if (Was_C_DOWN && !(Serial & C_DOWN))
	{
		KeyUp += 'K';
		Was_C_DOWN = false;
	}

	if ((Serial & D_LEFT) && !Was_D_LEFT)
	{
		KeyDown += 'F';
		Was_D_LEFT = true;
	}
	else if (Was_D_LEFT && !(Serial & D_LEFT))
	{
		KeyUp += 'F';
		Was_D_LEFT = false;
	}

	if ((Serial & D_UP) && !Was_D_UP)
	{
		KeyDown += 'T';
		Was_D_UP = true;
	}
	else if (Was_D_UP && !(Serial & D_UP))
	{
		KeyUp += 'T';
		Was_D_UP = false;
	}

	if ((Serial & D_RIGHT) && !Was_D_RIGHT)
	{
		KeyDown += 'H';
		Was_D_RIGHT = true;
	}
	else if (Was_D_RIGHT && !(Serial & D_RIGHT))
	{
		KeyUp += 'H';
		Was_D_RIGHT = false;
	}

	if ((Serial & D_DOWN) && !Was_D_DOWN)
	{
		KeyDown += 'G';
		Was_D_DOWN = true;
	}
	else if (Was_D_DOWN && !(Serial & D_DOWN))
	{
		KeyUp += 'G';
		Was_D_DOWN = false;
	}

	if ((Serial & JOY_LEFT) && !Was_JOY_LEFT)
	{
		KeyDown += 'A';
		Was_JOY_LEFT = true;
	}
	else if (Was_JOY_LEFT && !(Serial & JOY_LEFT))
	{
		KeyUp += 'A';
		Was_JOY_LEFT = false;
	}

	if ((Serial & JOY_RIGHT) && !Was_JOY_RIGHT)
	{
		KeyDown += 'D';
		Was_JOY_RIGHT = true;
	}
	else if (Was_JOY_RIGHT && !(Serial & JOY_RIGHT))
	{
		KeyUp += 'D';
		Was_JOY_RIGHT = false;
	}

	if ((Serial & JOY_DOWN) && !Was_JOY_DOWN)
	{
		KeyDown += 'S';
		Was_JOY_DOWN = true;
	}
	else if (Was_JOY_DOWN && !(Serial & JOY_DOWN))
	{
		KeyUp += 'S';
		Was_JOY_DOWN = false;
	}

	if ((Serial & JOY_UP) && !Was_JOY_UP)
	{
		KeyDown += 'W';
		Was_JOY_UP = true;
	}
	else if (Was_JOY_UP && !(Serial & JOY_UP))
	{
		KeyUp += 'W';
		Was_JOY_UP = false;
	}

	// Send the inputs
	SendInputs(KeyDown, KeyUp);
}




// Send the specified lists of inputs
void SendInputs(const std::string & KeyDown, const std::string & KeyUp)
{
	INPUT ip{};
	ip.type = INPUT_KEYBOARD;

	// Go through the range of characters and send each one
	for (const char & c : KeyDown)
	{
		LOG(_TEXT(c));
		ip.ki.dwFlags = KEYEVENTF_SCANCODE;
		ip.ki.wScan = static_cast<WORD>(MapVirtualKey(c, MAPVK_VK_TO_VSC));

		SendInput(1, &ip, sizeof(INPUT));
	}
	for (const char & c : KeyUp)
	{
		LOG(_TEXT(c));
		ip.ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;
		ip.ki.wScan = static_cast<WORD>(MapVirtualKey(c, MAPVK_VK_TO_VSC));

		SendInput(1, &ip, sizeof(INPUT));
	}
}




// Enumerate over all active COM ports and print user-friendly names
// Original from: https://stackoverflow.com/a/45613884
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
