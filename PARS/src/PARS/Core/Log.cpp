#include "stdafx.h"
#include "PARS/Core/Log.h"

#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/basic_file_sink.h"

namespace PARS {

	std::shared_ptr<spdlog::logger> Log::s_DefaultLogger;
	std::shared_ptr<spdlog::logger> Log::s_TrackingLogger;

	void Log::Init()
	{

		std::vector<spdlog::sink_ptr> DefaultSinks;
		DefaultSinks.emplace_back(std::make_shared<spdlog::sinks::stderr_color_sink_mt>());

		DefaultSinks[0]->set_pattern("%v%$");

		std::vector<spdlog::sink_ptr> TrackingSinks;
		TrackingSinks.emplace_back(std::make_shared<spdlog::sinks::stderr_color_sink_mt>());
		TrackingSinks.emplace_back(std::make_shared<spdlog::sinks::basic_file_sink_mt>("PARS.log", true));

		TrackingSinks[0]->set_pattern("[file : %s] [line : %#] : %v%$");
		TrackingSinks[1]->set_pattern("[Time %T] [file : %@] [%l] %v%$");

		s_DefaultLogger = std::make_shared<spdlog::logger>("Default", begin(DefaultSinks), end(DefaultSinks));
		spdlog::register_logger(s_DefaultLogger);
		s_DefaultLogger->set_level(spdlog::level::trace);
		
		s_TrackingLogger = std::make_shared<spdlog::logger>("Tracking", begin(TrackingSinks), end(TrackingSinks));
		spdlog::register_logger(s_TrackingLogger);
		s_TrackingLogger->set_level(spdlog::level::warn);
	}

}