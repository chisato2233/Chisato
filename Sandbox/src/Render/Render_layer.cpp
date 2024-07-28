#include"Render_layer.h"

#include "ChisatoCore/Rendering/Drawable/Drawable.h"



namespace cst {
	void Render_layer::on_attach() {
		auto tri2 = std::make_shared<graph::triangle>();
		auto quad = std::make_shared<graph::quad>();
		graphics.push_back(tri2);
		//graphics.push_back(quad);
		quad->transform.position().x += 0.5f;

		auto a = application::window().get_aspect_ratio();
		viewport =
			std::make_shared<rendering::orthographic_viewport>(-1.0f, 1.f , -1.0f,1.0f);
		camera2D = std::make_shared<gameplay::camera2D>(std::dynamic_pointer_cast<rendering::orthographic_viewport>(viewport));


		renderer::begin_scene(viewport);

		async_runtime().start_task(camera2D->control_camera());
		

		window.title = "Render Layer";
		for(auto i:graphics) {
			i->runtime = &async_runtime();
			layout.add(ui::color_editor{
				.label = std::format("{} Color Edit",i->shape_name()),
				.color = i->material->ambient
			});

			async_runtime().start_task(i->draw());
		}
		window.body = layout;
		ImGui_layer::UI_drawer.add([this] {
			window.build();
		});

	}

	void Render_layer::on_update() {
		
	}

	void Render_layer::on_event(event& event) {
		
	}


}
