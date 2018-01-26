#pragma once
#include <iostream>
#include <cstdint>

#define ASSERTIONS_ENABLED

#ifdef _DEBUG

#define debugBreak() asm { int 3 }
// check the expression and print Message if it is false 
#define ASSERT(expr, failMessage) \
 if (!expr) \
 {\
	 std::cerr << "Assertion from file: " << __FILE__ << " at line: " << __LINE__ << " failed! Context: " << failMessage << std::endl;\
 }
#else
#define ASSERT(expr, context) // evaluates to nothing
#endif
