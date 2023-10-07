#pragma once

#include "Bento/Core/Core.h"

#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/string_cast.hpp"

// This ignores all warnings raised inside External headers
#pragma warning(push, 0)
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
#pragma warning(pop)

namespace Bento {

	class Log
	{
	public:
		static void Init();

		static Ref<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		static Ref<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static Ref<spdlog::logger> s_CoreLogger;
		static Ref<spdlog::logger> s_ClientLogger;
	};

}

template<typename OStream, glm::length_t L, typename T, glm::qualifier Q>
inline OStream& operator<<(OStream& os, const glm::vec<L, T, Q>& vector)
{
	return os << glm::to_string(vector);
}

template<typename OStream, glm::length_t C, glm::length_t R, typename T, glm::qualifier Q>
inline OStream& operator<<(OStream& os, const glm::mat<C, R, T, Q>& matrix)
{
	return os << glm::to_string(matrix);
}

template<typename OStream, typename T, glm::qualifier Q>
inline OStream& operator<<(OStream& os, glm::qua<T, Q> quaternion)
{
	return os << glm::to_string(quaternion);
}

// Core log macros
#define BENTO_CORE_TRACE(...)    ::Bento::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define BENTO_CORE_INFO(...)     ::Bento::Log::GetCoreLogger()->info(__VA_ARGS__)
#define BENTO_CORE_WARN(...)     ::Bento::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define BENTO_CORE_ERROR(...)    ::Bento::Log::GetCoreLogger()->error(__VA_ARGS__)
#define BENTO_CORE_CRITICAL(...) ::Bento::Log::GetCoreLogger()->critical(__VA_ARGS__)

// Client log macros
#define BENTO_TRACE(...)         ::Bento::Log::GetClientLogger()->trace(__VA_ARGS__)
#define BENTO_INFO(...)          ::Bento::Log::GetClientLogger()->info(__VA_ARGS__)
#define BENTO_WARN(...)          ::Bento::Log::GetClientLogger()->warn(__VA_ARGS__)
#define BENTO_ERROR(...)         ::Bento::Log::GetClientLogger()->error(__VA_ARGS__)
#define BENTO_CRITICAL(...)      ::Bento::Log::GetClientLogger()->critical(__VA_ARGS__)