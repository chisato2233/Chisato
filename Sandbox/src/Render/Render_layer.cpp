#include"Render_layer.h"

#include "Drawable.h"



namespace cst {
	void Render_layer::on_attach() {
		ptr<triangle> tri1 = std::make_shared<triangle>();
		tri1->color = color_data;
		graphics.push_back(tri1);
		auto a = application::window().get_aspect_ratio();
		camera =
			std::make_shared<perspective_camera>(45.0f, a , -1.0f,1.0f);

		renderer::begin_scene(camera);

		async_runtime().start_task(control_camera());
		


		
		for(auto i:graphics) {
			i->runtime = &async_runtime();
			async_runtime().start_task(i->draw());
		}
	}

	void Render_layer::on_update() {
		
	}

	void Render_layer::on_event(event& event) {
		
	}
}
