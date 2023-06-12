#pragma once
#include"Core.h"
#include"spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include<memory>

namespace Chisato {
	namespace Log {
		CSTAPI struct l {
			static std::shared_ptr<int> p_int;

		};
		CSTAPI std::shared_ptr<spdlog::logger> p_EngineLogger;
		CSTAPI std::shared_ptr<spdlog::logger> p_CosoleLogger;
		
		CSTAPI void Init();

		namespace Engine {
			CSTAPI inline void Trace(std::string&& s) { p_EngineLogger->trace(s); }
			CSTAPI inline void Info(std::string&& s) { p_EngineLogger->info(s); }
			CSTAPI inline void Warn(std::string&& s) { p_EngineLogger->warn(s); }
			CSTAPI inline void Error(std::string&& s) { p_EngineLogger->error(s); }
		}
		namespace Cosole {
			CSTAPI inline void Trace(std::string&& s) { p_CosoleLogger->trace(s); }
			CSTAPI inline void Info(std::string&& s) { p_CosoleLogger->info(s); }
			CSTAPI inline void Warn(std::string&& s) { p_CosoleLogger->warn(s); }
			CSTAPI inline void Error(std::string&& s) { p_CosoleLogger->error(s); }
		}

	}
	

}


