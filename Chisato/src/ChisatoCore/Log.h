#pragma once
#include"Core.h"

#pragma warning(push,0)
#include"spdlog/spdlog.h"
#include <spdlog/fmt/ostr.h>
#include "spdlog/sinks/stdout_color_sinks.h"
#pragma warning(pop)

namespace Chisato::Log{
	//使用CRTP方便的写函数库
	template<typename Child>
	class Funcs {
	public:
		static void Info(std::string&& s) { Child::p_logger->info(s); }
		static void Warn(std::string&& s) { Child::p_logger->warn(s); }
		static void Error(std::string&& s) { Child::p_logger->error(s); }
		static void Trace(std::string&& s) { Child::p_logger->trace(s); }
		static void Critical(std::string&& s) { Child::p_logger->critical(s); }
	};




	class Engine : public Funcs<Engine>{
		friend void Init();
		template<typename Engine> friend class Funcs;
		static std::shared_ptr<spdlog::logger> p_logger;
	};
	
	class Cosole : public Funcs<Cosole> { 
		friend void Init();
		template<typename Cosole> friend class Funcs;
		static std::shared_ptr<spdlog::logger> p_logger;
	};

	void Init();
	
}
