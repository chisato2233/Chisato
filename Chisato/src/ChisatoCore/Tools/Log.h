#pragma once


#pragma warning(push,0)
#include"spdlog/spdlog.h"
#include <spdlog/fmt/ostr.h>
#include "spdlog/sinks/stdout_color_sinks.h"
#pragma warning(pop)

#ifdef CST_DEBUGS
	#define CST_DEBUG_DEFAULT_LOGGER ::cst::debug::engine
#elif
	#define CST_DEBUG_DEFAULT_LOGGER ::cst::Debug::application
#endif


namespace cst::debug {

	struct CSTAPI engine { static std::shared_ptr<spdlog::logger> p_logger; };
	struct CSTAPI application { static std::shared_ptr<spdlog::logger> p_logger; };

	template<typename T> concept logger = std::same_as<T, engine> || std::same_as<T, application>;

	template<logger L = CST_DEBUG_DEFAULT_LOGGER> struct CSTAPI log {
		static void info		(std::string_view s, auto&&... args) { L::p_logger->info		(std::vformat(s, std::make_format_args(std::forward<decltype(args)>(args)...))); }
		static void warn		(std::string_view s, auto&&... args) { L::p_logger->warn		(std::vformat(s, std::make_format_args(std::forward<decltype(args)>(args)...))); }
		static void error		(std::string_view s, auto&&... args) { L::p_logger->error		(std::vformat(s, std::make_format_args(std::forward<decltype(args)>(args)...))); }
		static void trace		(std::string_view s, auto&&... args) { L::p_logger->trace		(std::vformat(s, std::make_format_args(std::forward<decltype(args)>(args)...))); }
		static void critical	(std::string_view s, auto&&... args) { L::p_logger->critical	(std::vformat(s, std::make_format_args(std::forward<decltype(args)>(args)...))); }

		static void info_arg (auto&&... args) {
			std::ostringstream oss;
			[[maybe_unused]] int _[]{ (oss << std::forward<decltype(args)>(args) << ' ', 0)... };
			L::p_logger->info(oss.str());
		}
		static void critical_arg(auto&&... args) {
			std::ostringstream oss;
			[[maybe_unused]] int _[]{ (oss << std::forward<decltype(args)>(args) << ' ', 0)... };
			L::p_logger->critical(oss.str());
		}

		static void warn_arg(auto&&... args) {
			std::ostringstream oss;
			((oss << std::forward<decltype(args)>(args) << ' '), ...);
			L::p_logger->warn(oss.str());
		}

		static void error_arg(auto&&... args) {
			std::ostringstream oss;
			((oss << std::forward<decltype(args)>(args) << ' '), ...);
			L::p_logger->error(oss.str());
		}

		static void trace_arg(auto&&... args) {
			std::ostringstream oss;
			((oss << std::forward<decltype(args)>(args) << ' '), ...);
			L::p_logger->trace(oss.str());
		}




		/*static void warn		(auto&&... args) { L::p_logger->warn		(std::forward<decltype(args)>(args)...); }
		static void error		(auto&&... args) { L::p_logger->error		(std::forward<decltype(args)>(args)...); }
		static void trace		(auto&&... args) { L::p_logger->trace		(std::forward<decltype(args)>(args)...); }
		static void critical	(auto&&... args) { L::p_logger->critical	(std::forward<decltype(args)>(args)...); }*/


	};

	template<logger L = CST_DEBUG_DEFAULT_LOGGER> struct CSTAPI log_arg {
		
		static void trace(auto&&... args) {
			std::ostringstream oss;
			[[maybe_unused]] int _[]{ (oss << std::forward<decltype(args)>(args) << ' ', 0)... };
			L::p_logger->trace (oss.str());
		}

	private:
		const char* extend_arg(auto&&... args) {
			std::ostringstream oss;
			[[maybe_unused]] int _[]{ (oss << std::forward<decltype(args)>(args) << ' ', 0)... };
			return oss.str().c_str();
		}
	};


	template struct log<engine>;
	template struct log<application>;
	template struct log_arg<engine>;
	template struct log_arg<application>;
	
	void init();
}



/*
 *disable log libra
 *
 */
//namespace Chisato::Log{
//
//
//	template<typename Child>
//	struct CSTTEMPLATE Funcs {
//		static void Info	(std::string_view s) { Child::Get()->info		(s); }
//		static void Warn	(std::string_view s) { Child::Get()->warn		(s); }
//		static void Error	(std::string_view s) { Child::Get()->error		(s); }
//		static void Trace	(std::string_view s) { Child::Get()->trace		(s); }
//		static void Critical(std::string_view s) { Child::Get()->critical	(s); }
//
//		template<typename... Args> static void Info		(std::string_view s, Args&&... args) {	Child::Get()->info		(std::vformat(s, std::make_format_args(std::forward<Args>(args)...)));	}
//		template<typename... Args> static void Warn		(std::string_view s, Args&&... args) {	Child::Get()->warn		(std::vformat(s, std::make_format_args(std::forward<Args>(args)...)));	}
//		template<typename... Args> static void Error	(std::string_view s, Args&&... args) {	Child::Get()->error		(std::vformat(s, std::make_format_args(std::forward<Args>(args)...)));	}
//		template<typename... Args> static void Trace	(std::string_view s, Args&&... args) {	Child::Get()->trace		(std::vformat(s, std::make_format_args(std::forward<Args>(args)...)));	}
//		template<typename... Args> static void Critical	(std::string_view s, Args&&... args) {	Child::Get()->critical	(std::vformat(s, std::make_format_args(std::forward<Args>(args)...)));	}
//		
//	};
//
//	class CSTTEMPLATE Engine : public Funcs<Engine>{
//		friend struct Funcs <Engine>;
//		friend void Init();
//
//		static std::shared_ptr<spdlog::logger> p_logger;
//		static std::shared_ptr<spdlog::logger>& Get() { return p_logger; }
//	};
//	
//	class CSTTEMPLATE Application : public Funcs<Application> {
//		friend struct Funcs <Application> ;
//		friend void Init();
//
//		static std::shared_ptr<spdlog::logger> p_logger;
//		static std::shared_ptr<spdlog::logger>& Get() { return p_logger; }
//	};
//
//	void Init();
//	
//}

