#pragma once
#include "ChisatoCore/Rendering/Drawable/Drawable.h"
#include "ChisatoCore/keycode.h"
#include "ChisatoCore/Async/awaiter.h"
#include "ChisatoCore/Gameplay/camera.h"
#include"ChisatoCore/Layers/Layer.h"

#include "ChisatoCore/Rendering/matearial.h"
#include "ChisatoCore/UI/test.h"
#include "glm/gtc/type_ptr.hpp"


namespace cst {
	struct  Render_layer : layer {
		Render_layer() :layer("Render") {}
		void on_attach() override;
		void on_update() override;
		void on_event(event& event) override;

		std::vector<ptr<graph::drawable>> graphics;
		ptr<rendering::viewport> viewport;
		ptr<gameplay::camera2D> camera2D;

	
	public:
		ui::window window;
		ui::element_layout layout;
		pair<float,float> last_mouse_pos_{};
		rendering::color  color_data;
	};


}
