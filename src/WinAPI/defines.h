/*
	File: defines.h
	Purpose: Contains definitions for the application
*/


#pragma once


#undef DEBUG
#define DEBUG TRUE


#ifdef UNICODE
#define tcout	std::wcout
#define tcin	std::wcin
#define tcerr	std::wcerr
#else
#define tcout	std::cout
#define tcin	std::cin
#define tcerr	std::cerr
#endif


// Debug only output
#if DEBUG
#define LOG(...) tcout , __VA_ARGS__
#else
#define LOG(...) NULL
#endif


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
