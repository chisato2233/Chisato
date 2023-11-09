#include "application.h"
#include"Layers/layer.h"
namespace cst {
	application* application::handle_;
	
	

	application::application(){
		time::	init();
		debug::	init();
		//async::system::init();

		wnd_	= std::unique_ptr<window_base>	(window_base::create());
		input_	= std::unique_ptr<input_base>	(input_base	::create());

		wnd_->set_event_callback([this](event& PH1) { on_event((PH1)); });

		debug::log<>::info("Initialize app success!");

	}


	void application::main() {
		start();

		while (is_running) {
			time::update();
			//async::system::get().update();
			glClearColor(245 / 255.f, 212 / 255.f, 217 / 255.f, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			for (auto& i : layer_stack_) i->on_update();

			window().on_update();
			update();
		}

		stop();
	}
	void application::on_event(event& e) {
		using namespace debug;
		//async::event_system::get().on_event(e);

		for (auto i = layer_stack_.end(); i != layer_stack_.begin();) {
			(**--i).on_event(e);
			if (!e.is_active) break;
		}
		
		event_dispatch<window_close_event>{ [this](auto&) {is_running = false; } }(e);
		


		if (e.is_active) log<>::trace(e.get_name());
	}

	
}
