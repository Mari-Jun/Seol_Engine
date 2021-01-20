#pragma once

#include <memory>

#include "spdlog/spdlog.h"

namespace PARS
{
	class Log
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
#define PARS_CORE_TRACE(...)    ::PARS::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define PARS_CORE_INFO(...)     ::PARS::Log::GetCoreLogger()->info(__VA_ARGS__)
#define PARS_CORE_WARN(...)     ::PARS::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define PARS_CORE_ERROR(...)    ::PARS::Log::GetCoreLogger()->error(__VA_ARGS__)
#define PARS_CORE_FATAL(...)    ::PARS::Log::GetCoreLogger()->fatal(__VA_ARGS__)

// Client log macros
#define PARS_TRACE(...)	      ::PARS::Log::GetClientLogger()->trace(__VA_ARGS__)
#define PARS_INFO(...)	      ::PARS::Log::GetClientLogger()->info(__VA_ARGS__)
#define PARS_WARN(...)	      ::PARS::Log::GetClientLogger()->warn(__VA_ARGS__)
#define PARS_ERROR(...)	      ::PARS::Log::GetClientLogger()->error(__VA_ARGS__)
#define PARS_FATAL(...)	      ::PARS::Log::GetClientLogger()->fatal(__VA_ARGS__)