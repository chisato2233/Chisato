#pragma once
#include"event.h"


namespace cst {
	class CSTAPI window_resize_event:public event {
		std::pair<unsigned int, unsigned int> size_;
	
	public:
		window_resize_event(std::pair<unsigned int,unsigned int> _size = {}):
			event(Tag::Window),
			size_(_size) { }

		window_resize_event(unsigned int w, unsigned int h) : window_resize_event(std::pair{w, h}) { }

		unsigned int get_w()const noexcept { return size_.first; }
		unsigned int get_h() const noexcept{ return size_.second; }
		auto get_size()const noexcept { return size_; }

		std::string get_name()const noexcept override { return std::format("[Event]: Window Resize ({},{})", get_w(), get_h()); }
	};

	class CSTAPI window_close_event:public event {
	public:
		window_close_event():event(Tag::Window){ }
		std::string get_name() const noexcept override { return "[Event]: Window Close"; }
	};

	struct CSTAPI app_tick_event : event {
		app_tick_event() :event(Tag::App) { }
		std::string get_name()const noexcept override { return "[Event]: App tick"; }
	};	
	
	struct CSTAPI app_update_event : event {
		app_update_event() :event(Tag::App) { }
		std::string get_name()const noexcept override { return"[Event]: App Update"; }
	};	
	
	struct CSTAPI app_render_event : event {
		app_render_event() :event(Tag::App) { }
		std::string get_name()const noexcept override { return "[Event]: App Render"; }
	};
}