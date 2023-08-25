#include "Log.h"

namespace Chisato::Debug {

	std::shared_ptr<spdlog::logger> Engine::p_logger;
	std::shared_ptr<spdlog::logger> Application::p_logger;

	void Init() {
		spdlog::set_pattern("%^ [%n][%T]>>>>>    %v %$");

		Engine::p_logger = spdlog::stdout_color_mt("Chisato Engine");
		Application::p_logger = spdlog::stdout_color_mt("Application");

		Engine::p_logger->set_level(spdlog::level::trace);
		Application::p_logger->set_level(spdlog::level::trace);
	}
}




//
//namespace Chisato::Log {
//	std::shared_ptr<spdlog::logger> Engine::p_logger;
//	std::shared_ptr<spdlog::logger> Application::p_logger;
//
//
//	void Init() {
//		spdlog::set_pattern("%^ [%n][%T]>>>>>    %v %$");
//
//		Engine::Get() = spdlog::stdout_color_mt("Engine");
//		Engine::Get()->set_level(spdlog::level::trace);
//
//		Application::Get() = spdlog::stdout_color_mt("Application");
//		Application::Get()->set_level(spdlog::level::trace);
//	}
//
//}

