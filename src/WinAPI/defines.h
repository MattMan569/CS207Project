/*
	File: defines.h
	Purpose: Contains definitions for the application
*/


#pragma once


// Undefine the DEBUG used in <atldef.h> and use our own
#undef DEBUG

// Debug mode
#define DEBUG TRUE


// Typedefs
typedef unsigned long uint32;
typedef unsigned __int64 uint64;


// Bitwise position of the various inputs
constexpr unsigned long A =			0x1;
constexpr unsigned long B =			0x2;
constexpr unsigned long Z =			0x4;
constexpr unsigned long START =		0x8;
constexpr unsigned long LB =		0x10;
constexpr unsigned long RB =		0x20;
constexpr unsigned long C_LEFT =	0x40;
constexpr unsigned long C_UP =		0x80;
constexpr unsigned long C_RIGHT =	0x100;
constexpr unsigned long C_DOWN =	0x200;
constexpr unsigned long D_LEFT =	0x400;
constexpr unsigned long D_UP =		0x800;
constexpr unsigned long D_RIGHT =	0x1000;
constexpr unsigned long D_DOWN =	0x2000;
constexpr unsigned long JOY_LEFT =	0x4000;
constexpr unsigned long JOY_RIGHT =	0x8000;
constexpr unsigned long JOY_DOWN =	0x10000;
constexpr unsigned long JOY_UP =	0x20000;


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
// Author: CygnusX1 at https://stackoverflow.com/questions/29326460/how-to-make-a-variadic-macro-for-stdcout
template <typename T>
std::ostream& operator,(std::ostream& out, const T& t) {
	out << t;
	return out;
}
std::ostream& operator,(std::ostream& out, std::ostream&(*f)(std::ostream&)) {
	out << f;
	return out;
}
