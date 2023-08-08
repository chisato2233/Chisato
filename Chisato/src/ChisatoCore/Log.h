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
	class CSTAPI Funcs {
	public:
		static void Info(std::string&& s){ Child::Get()->info(s); }
		static void Warn(std::string&& s) { Child::Get()->warn(s); }
		static void Error(std::string&& s) { Child::Get()->error(s); }
		static void Trace(std::string&& s) { Child::Get()->trace(s); }
		static void Critical(std::string&& s) { Child::Get()->critical(s); }

		template<typename... Args> static void Info(spdlog::format_string_t<Args...> s,Args&&... args) { Child::Get()->info(s,std::forward<Args>(args)...); }
		template<typename... Args> static void Warn(spdlog::format_string_t<Args...> s,Args&&... args) { Child::Get()->warn(s,std::forward<Args>(args)...); }
		template<typename... Args> static void Error(spdlog::format_string_t<Args...> s,Args&&... args) { Child::Get()->error(s,std::forward<Args>(args)...); }
		template<typename... Args> static void Trace(spdlog::format_string_t<Args...> s,Args&&... args) { Child::Get()->trace(s,std::forward<Args>(args)...); }
		template<typename... Args> static void Critical(spdlog::format_string_t<Args...> s,Args&&... args) { Child::Get()->critical(s,std::forward<Args>(args)...); }
		
	};

	class CSTAPI Engine : public Funcs<Engine>{
		friend class Funcs<Engine>;
		friend void Init();

		static std::shared_ptr<spdlog::logger> p_logger;
		static std::shared_ptr<spdlog::logger>& Get() { return p_logger; }
	};
	
	class CSTAPI Cosole : public Funcs<Cosole> {
		friend class Funcs <Cosole> ;
		friend void Init();

		static std::shared_ptr<spdlog::logger> p_logger;
		static std::shared_ptr<spdlog::logger>& Get() { return p_logger; }
	};

	void Init();
	
}

namespace Chisato::newLog {
	class Log {
	friend void Init();
	
	private:
		std::shared_ptr<spdlog::logger> plogger;
	public:
		template<typename... Args>
		inline void Info(spdlog::format_string_t<Args...> s, Args&&... args) {
			plogger->info(s , std::forward<Args>(args)... );
		}
		template<typename... Args>
		inline void Warn(spdlog::format_string_t<Args...> s, Args&&... args) {
			plogger->warn(s, std::forward<Args>(args)...);
		}
		template<typename... Args>
		inline void Error(spdlog::format_string_t<Args...> s, Args&&... args) {
			plogger->error(s, std::forward<Args>(args)...);
		}
		template<typename... Args>
		inline void Trace(spdlog::format_string_t<Args...> s, Args&&... args) {
			plogger->trace(s, std::forward<Args>(args)...);
		}

		template<typename... Args>
		inline void Critical(spdlog::format_string_t<Args...> s, Args&&... args) {
			plogger->critical(s, std::forward<Args>(args)...);
		}
	};

	void Init();

	class AppLog : public Log { } ;
	class CoreLog : public Log { } ;
}