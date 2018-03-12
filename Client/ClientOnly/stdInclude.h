#pragma once
#include <iostream>

#ifdef _DEBUG

// checks the expression and prints message when it fails
#define ASSERT(expr, failMessage) \
 if (!expr) \
 {\
	 std::cerr << "Assertion from file: " << __FILE__ << " at line: " << __LINE__ << " failed! Message: " << failMessage << std::endl;\
 }
#else
#define ASSERT(expr, context) // evaluates to nothing
#endif

#define CLIENT_ONLY