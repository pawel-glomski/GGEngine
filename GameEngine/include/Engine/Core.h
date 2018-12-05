#pragma once

#ifdef BUILD_DLL
	#define EN_API __declspec(dllexport)
#else
	#define EN_API __declspec(dllimport)
#endif // BUILD_DLL