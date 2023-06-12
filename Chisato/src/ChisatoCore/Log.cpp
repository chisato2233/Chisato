#include "Log.h"

namespace Chisato {
	void Log::Init() {
		spdlog::set_pattern("%^%v  ---[%n][%T]%$");

		Log::p_EngineLogger = spdlog::stdout_color_mt("Application");
		Log::p_EngineLogger->set_level(spdlog::level::trace);

		Log::p_CosoleLogger = spdlog::stdout_color_mt("Chisato Core");
		Log::p_CosoleLogger->set_level(spdlog::level::trace);
	}

}