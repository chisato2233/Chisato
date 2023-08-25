#pragma once

#ifdef CST_PLATFORM_WINDOWS
	#ifdef CST_BUILD_DLL
		#define CSTAPI __declspec(dllexport)
		#define CSTTEMPLATE __declspec(dllexport)
	#else
		#define CSTAPI __declspec(dllimport)
		#define CSTTEMPLATE
	#endif
#else
	#error Please try to change Windows System
#endif

#ifdef CST_ASSERT_ENABLE
	#define CST_ASSERT(x,...)		{ if(!(x)){::Chisato::Debug::Log	<::Chisato::Debug::Engine>		::Error("Error: {}", __VA_ARGS__);__debugbreak(); } }
	#define CST_APP_ASSERT(x,...)	{ if(!(x)){::Chisato::Debug::Log	<::Chisato::Debug::Application>	::Error("Error: {}", __VA_ARGS__);__debugbreak(); } }
#else
	#define CST_ASSERT(x,...)
	#define CST_APP_ASSERT(x,...)
#endif

//加了一行return在imgui.h 3837里。