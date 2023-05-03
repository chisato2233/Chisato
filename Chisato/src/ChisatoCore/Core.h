#pragma once

#ifdef CST_PLATFORM_WINDOWS
	#ifdef CST_BUILD_DLL
		#define CSTAPI __declspec(dllexport)
	#else
		#define CSTAPI __declspec(dllimport)
	#endif
#else
	#error Please try to change Windows System
#endif
