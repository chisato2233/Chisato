﻿



#include "application.h"


#include"Layers/layer.h"

#include "Layers/ImGui/ImGui_layer.h"
#include "Layers/Web/Web_Layer.h"
#include "Rendering/Renderer.h"
#include "Rendering/render_command.h"

#include "UI/test.h"


namespace cst {
	application* application::handle_;

	application::application(){
		timer::	init();
		debug::	init();
		tag_system::init();
		file_path::init();
		shader_library::init();


		wnd_	= std::unique_ptr<window_base>	(window_base::create());
		input_	= std::unique_ptr<input_base>	(input_base	::create());

		wnd_->set_event_callback([this](event& PH1) { on_event((PH1)); });

		debug::log<>::info("Initialize app success!");
	}


	void application::main() {
		renderer::init();

		layers().push(std::make_shared<ImGui_layer>());
		//wlayers().push(std::make_shared<Web_layer>());

		{
			on_start();
			while (is_running) {
				timer::update();
				

				layer_stack_.update();

				window().on_update();
				
				on_update();
				render_command::set_color({ 245 / 255.f, 212 / 255.f, 217 / 255.f, 1 });
				render_command::clear();
			}
			on_stop();
			
		}
	}


	void application::on_event(event& e) {
		using namespace debug;
		//async::event_system::get().on_event(e);

		for (auto i = layer_stack_.end(); i != layer_stack_.begin();) {
			(**--i).on_event(e);
			if (!e.is_active) break;
		}
		
		event_dispatch<window_close_event>{ [this](auto&) {is_running = false; } }(e);


		
	}

	
}
