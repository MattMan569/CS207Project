/*
	File: WindowsExternalControlTest.cpp
	Purpose: This file tests the ability to send input to other applications via the Windows API.
	Date: 7th Nov. 2018
*/




#pragma warning(push, 0)        
#include <Windows.h>
#include <tchar.h>
#include <Psapi.h>
#include <iostream>
#include <string>
#pragma warning(pop)




INT _tmain(INT argc, TCHAR *argv[])
{
	// Get the character to send to the window
	TCHAR KeyToSend = {};
	std::cout << "Enter the key to send: ";
	std::cin >> KeyToSend;
	KeyToSend = toupper(KeyToSend);

	// Get the title of the window to match against
	TCHAR TitleMatch[MAX_PATH] = {};
	std::cout << "Enter a window title to match against: ";
	std::cin >> TitleMatch;

	// Don't match against the console window
	TCHAR ConsoleTitle[MAX_PATH] = {};
	GetConsoleTitle(ConsoleTitle, MAX_PATH);

	HWND Window = NULL;
	TCHAR WindowTitle[MAX_PATH] = {};
	
	while (TRUE)
	{
		// Look for children of the desktop
		Window = FindWindowEx(NULL, Window, NULL, NULL);
		if (Window == NULL)
		{
			std::cerr << "No windows found!" << std::endl;
			return 1;
		}
		
		// Compare the window's title against the title to match with
		GetWindowText(Window, WindowTitle, MAX_PATH);
		if (strstr(WindowTitle, TitleMatch) != NULL &&
			strcmp(WindowTitle, ConsoleTitle) != 0)
		{
			break;
		}
	}

	std::cout << "Window found: " << WindowTitle << std::endl;

	// Set the focus on the window, making it receive all inputs
	SetForegroundWindow(Window);
	

	// TODO: Attempt to send messages via window handle
//	HWND hWnd = GetForegroundWindow();
//	SendMessage(hWnd, WM_KEYDOWN, NULL, (LPARAM)_TEXT("Hello, world!"));
	

	// Send the specified input
	INPUT ip = {};
	ip.type = INPUT_KEYBOARD;
	ip.ki.wVk = KeyToSend;
	SendInput(1, &ip, sizeof(INPUT));
	
	return 0;
}
