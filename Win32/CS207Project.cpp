/*
	File: CS207Project.cpp

	Purpose:
		Defines the entry point.
*/

#include "stdafx.h"

#include "CS207Project.h"
#include "config.h"




/*
	Function: CreateConsole

	Based on code by Atori:
	https://stackoverflow.com/questions/32185512/output-to-console-from-a-win32-gui-application-on-windows-10

	Input:
		VOID

	Output:
		VOID

	Purpose:
		This function create a console for the Windows application.
		stdout, stdin, stderr is then redirected to the console.
*/
BOOL CALLBACK
CreateConsole()
{
	// Create a console for the application
	if (!AllocConsole())
	{
		return FALSE;
	}


	HANDLE stdHandle;
	INT hConsole;
	FILE *fp;

	// Direct stdout to the console
	stdHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	hConsole = _open_osfhandle((long)stdHandle, _O_TEXT);
	fp = _fdopen(hConsole, "w");
	freopen_s(&fp, "CONOUT$", "w", stdout);

	// Get stdin from the console
	stdHandle = GetStdHandle(STD_INPUT_HANDLE);
	hConsole = _open_osfhandle((long)stdHandle, _O_TEXT);
	fp = _fdopen(hConsole, "r");
	freopen_s(&fp, "CONIN$", "r", stdin);

	// Direct stderr to the console
	stdHandle = GetStdHandle(STD_ERROR_HANDLE);
	hConsole = _open_osfhandle((long)stdHandle, _O_TEXT);
	fp = _fdopen(hConsole, "w");
	freopen_s(&fp, "CONOUT$", "w", stderr);

	// Direct all other streams to the console
	std::ios::sync_with_stdio();


	return TRUE;
}




/*
	Function: About

	Input:
		hDlg - Handle for the dialog box
		uMsg - The message from Windows
		wParam - Additional message info
		lParam - Additional message info

	Ouput:
		INT_PTR - Whether the message was handled or not

	Purpose:
		Handle the messages for the window's about box
*/
INT_PTR CALLBACK
About
(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);

	switch (uMsg)
	{
		// Creation of the dialog window
		case WM_INITDIALOG:
		{
			return static_cast<INT_PTR>(TRUE);
			break;
		}
		// A button has been pressed
		case WM_COMMAND:
		{
			if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
			{
				EndDialog(hDlg, LOWORD(wParam));
				return static_cast<INT_PTR>(TRUE);
			}
			break;
		}
	}

	return static_cast<INT_PTR>(FALSE);
}




/*
	Function: WndProc

	Input:
		hwnd - Handle to the window
		uMsg - The message from Windows
		wParam - Additional message info
		lParam - Additional message info

	Output:
		LRESULT - The result of the message operation

	Purpose:
		This is the window-procedure function. This function
		will handle messages from Windows upon events.
*/
LRESULT CALLBACK
WndProc
(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	LRESULT result = 0;
	
	switch (uMsg)
	{
		// Menu commands
		case WM_COMMAND:
		{
			INT wmId = LOWORD(wParam);

			switch (wmId)
			{
				// Help -> About
				case IDM_ABOUT:
				{
					DialogBox(HINST_THISCOMPONENT, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
					break;
				}
				// File -> Exit
				case IDM_EXIT:
				{
					if (MessageBox(hWnd, "Are you sure you want to exit?", szTitle, MB_OKCANCEL) == IDOK)
					{
						PostMessage(hWnd, WM_CLOSE, NULL, NULL);
					}
					break;
				}
				default:
				{
					result = DefWindowProc(hWnd, uMsg, wParam, lParam);
					break;
				}
			}
			break;
		}
		// Set the minimum and maximum sizes of the window
		case WM_GETMINMAXINFO:
		{
			LPMINMAXINFO lpMMI = reinterpret_cast<LPMINMAXINFO>(lParam);
			
			lpMMI->ptMinTrackSize.x = 500;
			lpMMI->ptMinTrackSize.y = 300;
			break;
		}
		/*case WM_CREATE:
		{
			break;
		}*/
		case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc;
			_TCHAR greeting[] = _TEXT("Hello, world!");
			
			hdc = BeginPaint(hWnd, &ps);

			// Here your application is laid out.  
			// For this introduction, we just print out "Hello, world!"  
			// in the top left corner.  
			TextOut
			(
				hdc,				// Handle to the device context
				5,					// x coord
				5,					// y coord
				greeting,			// Text to draw
				_tcslen(greeting)	// Length of the string
			);
			// End application-specific layout section.  

			EndPaint(hWnd, &ps);
			break;
		}
		case WM_DESTROY:
		{
			PostQuitMessage(0);
			break;
		}
		// Use Windows default behaviour
		default:
		{
			result = DefWindowProc(hWnd, uMsg, wParam, lParam);
			break;
		}
	}

	return result;
}




/*
	Function: InitInstance

	Input:
		hInstance: Handle to the instance to associate the window with
		nCmdShow: Code specifying the show status of the window

	Output:
		BOOL: Return the success or failure of the creation of the window

	Purpose:
		This function is responsible for the creation of a window
		associated with an instance.
*/
BOOL CALLBACK
InitInstance
(HINSTANCE hInstance, INT nCmdShow)
{
	// Create a window and get its handle
	HWND hWnd = CreateWindow
	(
		szWindowClass,			// Name of the application
		szTitle,				// Window title bar text
		WS_OVERLAPPEDWINDOW,	// Type of window
		CW_USEDEFAULT,			// Initial x position
		CW_USEDEFAULT,			// Initial y position
		CW_USEDEFAULT,			// Initial width
		CW_USEDEFAULT,			// Initial height
		nullptr,				// This window's parent
		nullptr,				// This application's menu bar
		hInstance,				// Handle of the instance associated with this window
		nullptr					// Used with WM_CREATE
	);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}




/*
	Function: MyRegisterClass

	Input:
		hInstance - The instance handle of the instance to create the window for

	Output:
		ATOM - The return value of the register class function

	Purpose:
		Create a window class with the specified style and register it with Windows
*/
ATOM CALLBACK
MyRegisterClass
(HINSTANCE hInstance)
{
	// Create a window class
	WNDCLASSEX wCex = {};

	wCex.cbSize = sizeof(WNDCLASSEX);									// Size of this structure

	wCex.style = CS_HREDRAW | CS_VREDRAW;								// Redraw window if width or height changes
	wCex.lpfnWndProc = WndProc;											// Pointer to window procedure function
	wCex.cbClsExtra = 0;												// Extra bytes allocated following the structure
	wCex.cbWndExtra = 0;												// Extra bytes allocated following the window instance
	wCex.hInstance = hInstance;											// Handle to the instance the window is a part of
	wCex.hIcon = LoadIcon(hInstance,									// Handle to the icon
						  MAKEINTRESOURCE(IDI_CS207PROJECT));			// 
	wCex.hCursor = LoadCursor(nullptr, IDC_ARROW);						// Handle to the cursor resource
	wCex.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1);	// Handle to the background brush
	wCex.lpszMenuName = MAKEINTRESOURCE(IDC_CS207PROJECT);				// Resource name
	wCex.lpszClassName = szWindowClass;									// Window class name
	wCex.hIconSm = LoadIcon(wCex.hInstance,								// Handle to the small icon
							MAKEINTRESOURCE(IDI_SMALL));				//


	// Register the window class with Windows
	return RegisterClassEx(&wCex);
}




/*
	Function: WinMain

	Input:
		hInstance - Handle for the application's instance
		hPrevInstan - Deprecated
		lpCmdLine - Command line arguments
		nCmdShow - How to display the application's window

	Output:
		INT - Return result, typically from a message

	Purpose:
		This function is the entry point of a Windows application.
*/
INT APIENTRY
WinMain
(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, INT nCmdShow)
{
	// Prevent unreferenced variable warnings
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// Init global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_CS207PROJECT, szWindowClass, MAX_LOADSTRING);


	// Create our application's console window
	if (!CreateConsole())
	{
		MessageBox
		(
			NULL,
			_TEXT("Failed to create console!"),
			szTitle,
			NULL
		);
		
		return 1;
	}

	// Create a window class and register it with Windows
	if (!MyRegisterClass(hInstance))
	{
		MessageBox
		(
			NULL,
			_TEXT("Failed to register window class!"),
			szTitle,
			NULL
		);

		return 1;
	}

	// Create a windows based on our window class
	if (!InitInstance(hInstance, nCmdShow))
	{
		MessageBox
		(
			NULL,
			_TEXT("Failed to initialize instance!"),
			szTitle,
			NULL
		);
	}

	// Load our projects accelerators (keyboard shortcuts)
	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_CS207PROJECT));
	

	// Listen for messages from Windows
	// GetMessage returns non-zero so long as WM_QUIT message is not received
	MSG msg;
	while (GetMessage(&msg, nullptr, 0,	0))
	{
		TranslateMessage(&msg);	// Translate virtual key messages into char messages
		DispatchMessage(&msg);	// Send the message to the window procedure
	}


	INT returnCode = static_cast<INT>(msg.wParam);
	std::cout << "Return code: " << returnCode << std::endl;
	if (returnCode == 0)
		std::cout << "Application exited normally" << std::endl;
	else
		std::cout << "Application error" << std::endl;

	std::cout << "Press any key to continue . . .";
	std::cin.ignore();
	return returnCode;
}




/*
void CtrlClick()
{
	// Inputs to be sent
	INPUT ip[4] = { 0 };

	// Hold control
	ip[0].type = INPUT_KEYBOARD;
	ip[0].ki.wVk = VK_CONTROL;

	// Left click
	ip[1].type = INPUT_MOUSE;
	ip[1].mi.dwFlags = MOUSEEVENTF_LEFTDOWN;

	// Release left click
	ip[2].type = INPUT_MOUSE;
	ip[2].mi.dwFlags = MOUSEEVENTF_LEFTUP;

	// Release control
	ip[3].type = INPUT_KEYBOARD;
	ip[3].ki.wVk = VK_CONTROL;
	ip[3].ki.dwFlags = KEYEVENTF_KEYUP;

	// Send the inputs
	SendInput(ARRAY_SIZE(ip), ip, sizeof(INPUT));
}




void CheckA()
{
	while (true)
	{
		if (GetKeyState('A') & PRESSED)
		{
			std::cout << "'A' is pressed" << std::endl;
		}

		if (GetKeyState(VK_CAPITAL) & TOGGLED)
		{
			std::cout << "Caps lock toggled" << std::endl;
		}
	}
}




//*
	Function: GetLastErrorAsString
	Author: Jamin Grey on Stack Overflow
	https://stackoverflow.com/questions/1387064/how-to-get-the-error-message-from-the-error-code-returned-by-getlasterror
//
std::string GetLastErrorAsString()
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
*/
