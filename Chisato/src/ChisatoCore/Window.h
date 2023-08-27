#pragma once
#include <pch.h>

namespace cst {
	using uint = unsigned int;
	
	struct wnd_props {
		std::string title;
		std::pair<uint,uint> size;
		
		wnd_props(std::string&& title = "Chisato Engine", std::pair<uint, uint> size = { 1280,720 }):
			title{title},size{size} { }
	};

	struct window {
		virtual ~window() = default;

		virtual void on_update() = 0;

		virtual uint					get_w()			const noexcept = 0;
		virtual uint					get_h()			const noexcept = 0;
		virtual std::pair<uint, uint>	get_size()		const noexcept = 0;
		virtual bool					get_key(int key)const noexcept = 0;
		virtual void*					get_wnd_ptr()	const noexcept = 0;
		virtual std::string				get_name()		const noexcept = 0;

		virtual void set_event_callback	(const std::function<void(event&)>& callback)	= 0;
		virtual void set_v_sync			(bool enabled)									= 0;
		virtual bool is_v_sync			()const noexcept								= 0;

		static window* create(const wnd_props& props = wnd_props{});
	};

}