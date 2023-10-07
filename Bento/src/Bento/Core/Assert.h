#pragma once

#include "Bento/Core/Core.h"
#include "Bento/Core/Log.h"
#include <filesystem>

#ifdef BENTO_ENABLE_ASSERTS

// Alteratively we could use the same "default" message for both "WITH_MSG" and "NO_MSG" and
// provide support for custom formatting by concatenating the formatting string instead of having the format inside the default message
#define BENTO_INTERNAL_ASSERT_IMPL(type, check, msg, ...) { if(!(check)) { BENTO##type##ERROR(msg, __VA_ARGS__); BENTO_DEBUGBREAK(); } }
#define BENTO_INTERNAL_ASSERT_WITH_MSG(type, check, ...) BENTO_INTERNAL_ASSERT_IMPL(type, check, "Assertion failed: {0}", __VA_ARGS__)
#define BENTO_INTERNAL_ASSERT_NO_MSG(type, check) BENTO_INTERNAL_ASSERT_IMPL(type, check, "Assertion '{0}' failed at {1}:{2}", BENTO_STRINGIFY_MACRO(check), std::filesystem::path(__FILE__).filename().string(), __LINE__)

#define BENTO_INTERNAL_ASSERT_GET_MACRO_NAME(arg1, arg2, macro, ...) macro
#define BENTO_INTERNAL_ASSERT_GET_MACRO(...) BENTO_EXPAND_MACRO( BENTO_INTERNAL_ASSERT_GET_MACRO_NAME(__VA_ARGS__, BENTO_INTERNAL_ASSERT_WITH_MSG, BENTO_INTERNAL_ASSERT_NO_MSG) )

// Currently accepts at least the condition and one additional parameter (the message) being optional
#define BENTO_ASSERT(...) BENTO_EXPAND_MACRO( BENTO_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_, __VA_ARGS__) )
#define BENTO_CORE_ASSERT(...) BENTO_EXPAND_MACRO( BENTO_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_CORE_, __VA_ARGS__) )
#else
#define BENTO_ASSERT(...)
#define BENTO_CORE_ASSERT(...)
#endif