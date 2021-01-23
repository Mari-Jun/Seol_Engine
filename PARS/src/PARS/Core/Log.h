#pragma once

#include <memory>

#include "spdlog/spdlog.h"

namespace PARS
{
	class Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetDefaultLogger() { return s_DefaultLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetTrackingLogger() { return s_TrackingLogger; }
	private:
		static std::shared_ptr<spdlog::logger> s_DefaultLogger;
		static std::shared_ptr<spdlog::logger> s_TrackingLogger;
	};
}



//log macros
#define PARS_TRACE(...)			::PARS::Log::GetDefaultLogger()->trace(__VA_ARGS__)
#define PARS_INFO(...)			::PARS::Log::GetDefaultLogger()->info(__VA_ARGS__)
#define PARS_WARN(...)			SPDLOG_LOGGER_WARN(::PARS::Log::GetTrackingLogger(), __VA_ARGS__)
#define PARS_ERROR(...)			SPDLOG_LOGGER_ERROR(::PARS::Log::GetTrackingLogger(), __VA_ARGS__)
#define PARS_CRITICAL(...)		SPDLOG_LOGGER_CRITICAL(::PARS::Log::GetTrackingLogger(), __VA_ARGS__)