#pragma once

#include <memory>

#ifdef BENTO_PLATFORM_WINDOWS
#if BENTO_DYNAMIC_LINK
	#ifdef BENTO_BUILD_DLL
		#define BENTO_API __declspec(dllexport)
	#else
		#define BENTO_API __declspec(dllimport)
	#endif

#else
	#define BENTO_API
#endif
#else
	#error Benoto only supports Windows
#endif

#ifdef BENTO_DEBUG
	#define BENTO_ENABLE_ASSERTS
#endif // BENTO_DEBUG


#ifdef BENTO_ENABLE_ASSERTS
	#define BENTO_ASSERT(x, ...) { if(!(x)) { BENTO_ERROR("Assertion Failed: {}", __VA_ARGS__); __debugbreak(); } }
	#define BENTO_CORE_ASSERT(x, ...) { if(!(x)) { BENTO_CORE_ERROR("Assertion Failed: {}", __VA_ARGS__); __debugbreak(); } }
#else
	#define BENTO_ASSERT(x, ...)
	#define BENTO_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define BENTO_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

namespace Bento {

	template<typename T>
	using Scope = std::unique_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args) 
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using Ref = std::shared_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args) 
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}

}