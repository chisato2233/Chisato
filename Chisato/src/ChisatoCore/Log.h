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
	struct CSTAPI Funcs {
		static void Info	(std::string_view s) { Child::Get()->info		(s); }
		static void Warn	(std::string_view s) { Child::Get()->warn		(s); }
		static void Error	(std::string_view s) { Child::Get()->error		(s); }
		static void Trace	(std::string_view s) { Child::Get()->trace		(s); }
		static void Critical(std::string_view s) { Child::Get()->critical	(s); }

		template<typename... Args> static void Info		(std::string_view s, Args&&... args) {	Child::Get()->info		(std::vformat(s, std::make_format_args(std::forward<Args>(args)...)));	}
		template<typename... Args> static void Warn		(std::string_view s, Args&&... args) {	Child::Get()->warn		(std::vformat(s, std::make_format_args(std::forward<Args>(args)...)));	}
		template<typename... Args> static void Error	(std::string_view s, Args&&... args) {	Child::Get()->error		(std::vformat(s, std::make_format_args(std::forward<Args>(args)...)));	}
		template<typename... Args> static void Trace	(std::string_view s, Args&&... args) {	Child::Get()->trace		(std::vformat(s, std::make_format_args(std::forward<Args>(args)...)));	}
		template<typename... Args> static void Critical	(std::string_view s, Args&&... args) {	Child::Get()->critical	(std::vformat(s, std::make_format_args(std::forward<Args>(args)...)));	}
		
	};

	class CSTAPI Engine : public Funcs<Engine>{
		friend struct Funcs <Engine>;
		friend void Init();

		static std::shared_ptr<spdlog::logger> p_logger;
		static std::shared_ptr<spdlog::logger>& Get() { return p_logger; }
	};
	
	class CSTAPI Application : public Funcs<Application> {
		friend struct Funcs <Application> ;
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
		inline void Info(std::string_view s, Args&&... args) {
			plogger->info(s , std::forward<Args>(args)... );
		}
		template<typename... Args>
		inline void Warn(std::string_view s, Args&&... args) {
			plogger->warn(s, std::forward<Args>(args)...);
		}
		template<typename... Args>
		inline void Error(std::string_view s, Args&&... args) {
			plogger->error(s, std::forward<Args>(args)...);
		}
		template<typename... Args>
		inline void Trace(std::string_view s, Args&&... args) {
			plogger->trace(s, std::forward<Args>(args)...);
		}

		template<typename... Args>
		inline void Critical(std::string_view s, Args&&... args) {
			plogger->critical(s, std::forward<Args>(args)...);
		}
	};

	void Init();

	class AppLog : public Log { } ;
	class CoreLog : public Log { } ;
}