/*
	File: defines.h
	Purpose: Contains definitions for the application
*/


#pragma once


// Undefine the DEBUG used in <atldef.h> and use our own
#undef DEBUG

// Debug mode
#define DEBUG FALSE


// Typedefs
typedef signed char			int8;
typedef short				int16;
typedef long				int32;
typedef long long			int64;
typedef unsigned char		uint8;
typedef unsigned short		uint16;
typedef unsigned long		uint32;
typedef unsigned long long	uint64;


// Delay cycles to wait for the Arduino when connecting
#define ARDUINO_DELAY_CYCLES 3


// Time to delay when printing a ticking "please wait" message
#define WAIT_MSG_DELAY_MS 200


// Bitwise position of the various inputs
constexpr unsigned long RESERVED =	0x1UL;		// Reserved value
constexpr unsigned long A =			0x2UL;		// Buttons
constexpr unsigned long B =			0x4UL;
constexpr unsigned long Z =			0x8UL;
constexpr unsigned long START =		0x10UL;
constexpr unsigned long LB =		0x20UL;		// Bumpers
constexpr unsigned long RB =		0x40UL;
constexpr unsigned long C_LEFT =	0x80UL;		// Action buttons
constexpr unsigned long C_UP =		0x100UL;
constexpr unsigned long C_RIGHT =	0x200UL;
constexpr unsigned long C_DOWN =	0x400UL;
constexpr unsigned long D_LEFT =	0x800UL;	// D Pad
constexpr unsigned long D_UP =		0x1000UL;
constexpr unsigned long D_RIGHT =	0x2000UL;
constexpr unsigned long D_DOWN =	0x4000UL;
constexpr unsigned long JOY_LEFT =	0x8000UL;	// Joystick
constexpr unsigned long JOY_RIGHT =	0x10000UL;
constexpr unsigned long JOY_DOWN =	0x20000UL;
constexpr unsigned long JOY_UP =	0x40000UL;


// Change the definition of cout, cin, and cerr depending on if
// the wide character set is being used or not
#ifdef UNICODE
#define tcout	std::wcout
#define tcin	std::wcin
#define tcerr	std::wcerr
#else
#define tcout	std::cout
#define tcin	std::cin
#define tcerr	std::cerr
#endif


// Debug only output with variadic parameters
#if DEBUG
#define LOG(...) tcout , __VA_ARGS__ , std::flush
#else
#define LOG(...) NULL
#endif


// Clarify the usage of static
#define local_persist static


// Overloaded ostream operators for variadic macros
// Original from: https://stackoverflow.com/a/29326744
template <typename T>
std::ostream& operator,(std::ostream& out, const T& t) {
	out << t;
	return out;
}
std::ostream& operator,(std::ostream& out, std::ostream&(*f)(std::ostream&)) {
	out << f;
	return out;
}
