#pragma once
#include <iostream>
#include <cstdint>

#define ASSERTIONS_ENABLED

#ifdef _DEBUG

#define debugBreak() asm { int 3 }
// check the expression and fail if it is false 
#define ASSERT(expr, context) \
 if (!expr) \
 {\
	 std::cerr << "Assertion from file: " << __FILE__ << " at line: " << __LINE__ << " failed! Context: " << context << std::endl;\
 }
#else
#define ASSERT(expr, context) // evaluates to nothing
#endif
