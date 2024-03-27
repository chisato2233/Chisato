#pragma once
#include "Drawable.h"

#include"ChisatoCore/Layers/Layer.h"


namespace cst {
	struct CSTAPI Render_layer : layer {
		Render_layer() :layer("Render") {}
		void on_attach() override;
		void on_update() override;
		void on_event(event& event) override;

		std::vector<ptr<drawable>> graphics;
		ptr<orthographic_camera> camera;
	};
}
