#pragma once

#include "Bento/Core/PlatformDectection.h"

#include <memory>

#ifdef BENTO_DEBUG
#if defined(BENTO_PLATFORM_WINDOWS)
#define BENTO_DEBUGBREAK() __debugbreak()
#elif defined(BENTO_PLATFORM_LINUX)
#include <signal.h>
#define BENTO_DEBUGBREAK() raise(SIGTRAP)
#else
#error "Platform doesn't support debugbreak yet!"
#endif
#define BENTO_ENABLE_ASSERTS
#else
#define BENTO_DEBUGBREAK()
#endif

#define BENTO_EXPAND_MACRO(x) x
#define BENTO_STRINGIFY_MACRO(x) #x

#define BIT(x) (1 << x)

#define BENTO_BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }

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

#include "Bento/Core/Log.h"
#include "Bento/Core/Assert.h"