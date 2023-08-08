#include "Log.h"

namespace Chisato::Log {
	std::shared_ptr<spdlog::logger> Engine::p_logger;
	std::shared_ptr<spdlog::logger> Cosole::p_logger;


	void Init() {
		spdlog::set_pattern("%^ [%n][%T]>>>>>    %v %$");

		Engine::Get() = spdlog::stdout_color_mt("Application");
		Engine::Get()->set_level(spdlog::level::trace);

		Cosole::Get() = spdlog::stdout_color_mt("Chisato Core");
		Cosole::Get()->set_level(spdlog::level::trace);
	}

}

namespace Chisato::newLog {
	CoreLog coreLog;
	AppLog appLog;

	void Init() {
		spdlog::set_pattern("%^ [%n][%T]>>>>>    %v %$");

		coreLog.plogger = spdlog::stdout_color_mt("Chisato Core");
		appLog.plogger = spdlog::stdout_color_mt("Application");

		coreLog.plogger->set_level(spdlog::level::trace);
		appLog.plogger->set_level(spdlog::level::trace);
	}
}

