#pragma once
#include "ChisatoCore/Layers/layer.h"
#include "ChisatoCore/Web/web_app.h"
namespace cst {
	class Web_layer : public layer {
	public:
		Web_layer() : layer{ "Web" } {}
		void on_attach() override {
			web::app::init();
		}

		void on_update() override {
			web::app::update();
		}
	};
}
