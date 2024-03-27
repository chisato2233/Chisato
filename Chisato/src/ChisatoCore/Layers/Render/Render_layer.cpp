#include"Render_layer.h"

#include "Drawable.h"



namespace cst {
	void Render_layer::on_attach() {
		ptr<triangle> tri1 = std::make_shared<triangle>();

		graphics.push_back(tri1);

		camera =
			std::make_shared<orthographic_camera>(-2.0f, 2.0f, -2.0f, 2.0f);

		renderer::begin_scene(camera);
		camera->transform.position.set({ 0.5f,0.5f,0.0f });

		for(auto i:graphics) {
			async_runtime().start_task(i->draw());
		}
	}

	void Render_layer::on_update() {
		 
	}

	void Render_layer::on_event(event& event) {
		
	}
}
