#pragma once
#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/fmt/ostr.h"

namespace Bento {

	class BENTO_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}

// Core log macros
#define BENTO_CORE_TRACE(...)  ::Bento::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define BENTO_CORE_INFO(...)   ::Bento::Log::GetCoreLogger()->info(__VA_ARGS__)
#define BENTO_CORE_WARN(...)   ::Bento::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define BENTO_CORE_ERROR(...)  ::Bento::Log::GetCoreLogger()->error(__VA_ARGS__)
#define BENTO_CORE_FATAL(...)  ::Bento::Log::GetCoreLogger()->fatal(__VA_ARGS__)

// Core log macros
#define BENTO_TRACE(...)       ::Bento::Log::GetClientLogger()->trace(__VA_ARGS__)
#define BENTO_INFO(...)        ::Bento::Log::GetClientLogger()->info(__VA_ARGS__)
#define BENTO_WARN(...)        ::Bento::Log::GetClientLogger()->warn(__VA_ARGS__)
#define BENTO_ERROR(...)       ::Bento::Log::GetClientLogger()->error(__VA_ARGS__)
#define BENTO_FATAL(...)       ::Bento::Log::GetClientLogger()->fatal(__VA_ARGS__)