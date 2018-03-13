#pragma once
#include <iostream>

#ifdef _DEBUG

#include <string>
#include <typeindex>

// checks the expression and prints message when it fails
#define ASSERT(expr, failMessage) \
 if (!expr) \
 {\
	 std::cerr << "Assertion from file: " << __FILE__ << " at line: " << __LINE__ << " failed! Message: " << failMessage << std::endl;\
 }
#else
#define ASSERT(expr, failMessage) // evaluates to nothing
#endif

#define CLIENT_ONLY