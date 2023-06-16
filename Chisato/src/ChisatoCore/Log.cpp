#include "Log.h"

namespace Chisato::Log {
	std::shared_ptr<spdlog::logger> Engine::p_logger;
	std::shared_ptr<spdlog::logger> Cosole::p_logger;


	void Init() {
		spdlog::set_pattern("%^%v  ---[%n][%T]%$");

		Engine::p_logger = spdlog::stdout_color_mt("Application");
		Engine::p_logger->set_level(spdlog::level::trace);

		Cosole::p_logger = spdlog::stdout_color_mt("Chisato Core");
		Cosole::p_logger->set_level(spdlog::level::trace);
	}

}