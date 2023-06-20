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

#ifdef BENTO_ENABLE_ASSERTS
	#define BENTO_ASSERT(x, ...) { if(!(x)) { BENTO_ERROR("Assertion Failed: {}", __VA_ARGS__); __debugbreak(); } }
	#define BENTO_CORE_ASSERT(x, ...) { if(!(x)) { BENTO_CORE_ERROR("Assertion Failed: {}", __VA_ARGS__); __debugbreak(); } }
#else
	#define BENTO_ASSERT(x, ...)
	#define BENTO_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define BENTO_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)