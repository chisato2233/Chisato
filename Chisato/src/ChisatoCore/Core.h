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

#ifdef CST_ASSERT_ENABLE
	#define CST_ASSERT(x,...) { if(!(x)){::Chisato::Log::Engine::Error(std::format("Error: {}",__VA_ARGS__));__debugbreak(); } }
	#define CST_COSOLE_ASSERT(x,...) { if(!(x)){::Chisato::Log::Cosole::Error(std::format("Error: {}",__VA_ARGS__));__debugbreak(); } }
#else
	#define CST_ASSERT(x,...)
	#define CST_COSOLE_ASSERT(x,...)
#endif