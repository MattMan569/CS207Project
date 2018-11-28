/*
	File: WindowsExternalControlTest.cpp
	Purpose: This file tests the ability to send input to other applications via the Windows API.
	Date: 7th Nov. 2018
*/


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
#include <Psapi.h>
#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#pragma warning(pop);




INT _tmain(INT argc, TCHAR *argv[])
{
	UNREFERENCED_PARAMETER(argc);
	UNREFERENCED_PARAMETER(argv);

	// Get the character to send to the window
	TCHAR KeyToSend = {};
	tcout << "Enter the key to send: ";
	tcin >> KeyToSend;
	KeyToSend = (TCHAR)toupper(KeyToSend);
	
	// Get the title of the window to match against
	TCHAR TitleMatch[MAX_PATH] = {};
	tcout << "Enter a window title to match against: ";
	tcin >> TitleMatch;

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
			tcerr << "No windows found!" << std::endl;
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

	tcout << "Window found: " << WindowTitle << std::endl;

	// Set the focus on the window, making it receive all inputs
	SetForegroundWindow(Window);

	// Wait for the window to become active
	while (!GetForegroundWindow());

	// Get the handle of the newly active window
	HWND hWnd = GetForegroundWindow();

	// Send a message to the window
	PostMessage(hWnd, WM_CHAR, KeyToSend, NULL);
	
	return 0;
}
