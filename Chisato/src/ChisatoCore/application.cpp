#include "application.h"

namespace cst {
	application* application::handle_;
	application::application(){
		debug::init();
		wnd_ = std::unique_ptr<struct window>(window::create());
		wnd_->set_event_callback([this](event& PH1) { on_event((PH1)); });

		debug::log<>::info("Initialize app success!");
	}

	void application::main(){
		while (is_running) {
			glClearColor(245/255.f, 212/255.f, 217/255.f, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			for(auto& i:layer_stack_) i->on_update();
			wnd_->on_update();
		}
	}
	
	void application::on_event(event& e) {
		using namespace debug;

		for (auto i = layer_stack_.end(); i != layer_stack_.begin();) {
			(**--i).on_event(e);
			if (!e.is_active) break;
		}
		
		event_dispatch<window_close_event>{ [this](auto&) {is_running = false; } }(e);
		
		//event_dispatch<window_resize_event>{[this](auto& e) {debug::log<>::info("ll"), glViewport(0, 0, e.get_w(), e.get_h()); } }(e);
		if (e.is_active) log<>::trace(e.get_name());
	}

}
