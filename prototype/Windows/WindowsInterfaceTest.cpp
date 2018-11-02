/*
    File: WindowsInterfaceTest.cpp
    Purpose: Test interfacing with the windows API to check for input.
    Date: 1st Nov. 2018
*/

#include <iostream>
#include <Windows.h>
#include <string>
#include <conio.h>




// Simulate a Ctrl + LMB combintation
void ctrlClk()
{
	const int num = 1;
	const int size = sizeof(INPUT);

	// Inputs to be sent to Windows
	INPUT ip = { 0 };

	// Hold control
	ip.type = INPUT_KEYBOARD;
	ip.ki.wVk = VK_CONTROL;
	SendInput(num, &ip, size);

	// Hold left click
	ip.type = INPUT_MOUSE;
	ip.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
	SendInput(num, &ip, size);

	// Release left click
	ip.type = INPUT_MOUSE;
	ip.mi.dwFlags = MOUSEEVENTF_LEFTUP;
	SendInput(num, &ip, size);

	//Release control
	ip.type = INPUT_KEYBOARD;
	ip.ki.wVk = VK_CONTROL;
	ip.ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput(num, &ip, size);
}




// Check if a key is being pressed
bool isKeyPressed(char key)
{
	// High bit detects key presses
	const int pressed = 0x8000;

	// Check if key is pressed
	if (GetKeyState(key) & pressed)
		return true;
	else
		return false;
}




// Check if a key is toggled
bool isKeyToggled(char key)
{
	// Low bit detects toggle
	const int toggled = 0x0001;

	// Check if key is toggled
	if (GetKeyState(key) & toggled)
		return true;
	else
		return false;
}




//	Author: Jamin Grey on Stack Overflow
//	https ://stackoverflow.com/questions/1387064/how-to-get-the-error-message-from-the-error-code-returned-by-getlasterror
std::string getLastErrorAsString()
{
	//Get the error message, if any.
	DWORD errorMessageID = ::GetLastError();
	if (errorMessageID == 0)
		return std::string(); //No error message has been recorded

	LPSTR messageBuffer = nullptr;
	size_t size = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
								 NULL, errorMessageID, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&messageBuffer, 0, NULL);

	std::string message(messageBuffer, size);

	//Free the buffer.
	LocalFree(messageBuffer);

	return message;
}




int main()
{
	// Control + LMB
	std::cout << "Press any key to test Ctrl + LMB..." << std::endl;
	std::cin.ignore();
	ctrlClk();


	// Check for 'A'
	std::cout << "Now checking if 'A' is being pressed. Press 'X' to continue." << std::endl;
	while (true)
	{
		if (isKeyPressed('A'))
		{
			std::cout << "A is pressed." << std::endl;
		}

		if (isKeyPressed('X'))
			break;
	}


	// Wait for the user to release the 'X' key
	while (isKeyPressed('X'));


	// Check if capslock is toggled
	std::cout << "Now checking is capslock is toggled. Press 'X' to continue." << std::endl;
	while (true)
	{
		if (isKeyToggled(VK_CAPITAL))
		{
			std::cout << "Caps lock is on." << std::endl;
		}

		if (isKeyPressed('X'))
			break;
	}


	// Print an error, if needed
	std::string error = "";
	error = getLastErrorAsString();
	if (error != "")
	{
		std::cout << "ERROR: " << error << std::endl;
		return 1;
	}

    return 0;
}
