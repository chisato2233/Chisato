#pragma once
#include"../Core.h"
namespace cst ::debug{
	
	class CSTAPI exception :std::exception {
		int line_; std::string file_;
	protected:
		std::string what_r_;
	public:
		exception(int line, const char* file) noexcept : line_(line), file_(file) {  }

		int			get_line()	const noexcept { return	line_; }
		std::string get_file()	const noexcept { return	file_; }

		const char* what()	const noexcept override { return what_r_.c_str(); }
		
		virtual std::string get_type	()	const	noexcept { return "[UnKnown Exception]:"; }
		virtual std::string get_location()	const	noexcept { return std::format("({} in {})", get_line(), get_file()); }
		virtual std::string get_what	()			noexcept {
			return what_r_ = std::format(
				"{} something error,{}",
				get_type(),
				get_location()
			);
		}
		
	};
	struct CSTAPI my_exception : exception {
		my_exception(std::string_view s, int l, const char* file) :exception{ l,file }, info_{ s } {}

		auto		get_info()const noexcept			{ return info_; }
		std::string get_type()const noexcept override	{ return "[error information]:"; }
		std::string get_what()		noexcept override { return what_r_ = std::format("{} {} {}", get_type(), get_info(), get_location()); }
	private:
		std::string info_;
	};

}

#define CST_ERROR(s) throw ::cst::debug::my_exception(s,__LINE__,__FILE__)