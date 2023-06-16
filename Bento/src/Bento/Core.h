#pragma once

#ifdef BENTO_PLATFORM_WINDOWS
	#ifdef BENTO_BUILD_DLL
		#define BENTO_API __declspec(dllexport)
	#else
		#define BENTO_API __declspec(dllimport)
	#endif

#else
	#error Bento only support Windows!
#endif
