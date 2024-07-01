#pragma once
#include "Drawable.h"
#include "ChisatoCore/keycode.h"
#include "ChisatoCore/Async/awaiter.h"
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

		std::vector<ptr<drawable>> graphics;
		ptr<camera> camera;


		auto control_camera()->async::co_task<> {
			using namespace async;


			while(true) {
				co_await wait_next_frame{};
				operator_key();
				operator_mouse();
				last_mouse_pos_ = application::input().get_mouse_pos();

			}
		}

		void operator_key() {
			auto& input_info = application::input();
			float move_speed = 10 * timer::delta().count();
			if (input_info.is_pressed(key_code_map::_w)) 
				camera->transform.position += camera->transform.forward() * move_speed;
			else if (input_info.is_pressed(key_code_map::_s)) 
				camera->transform.position -= camera->transform.forward() * move_speed;

			

			

			if (input_info.is_pressed(key_code_map::_a)) 
				camera->transform.position -= camera->transform.right() * move_speed;
			else if (input_info.is_pressed(key_code_map::_d)) 
				camera->transform.position += camera->transform.right() * move_speed;
			

			if (input_info.is_pressed(key_code_map::_q)) 
				camera->transform.position -= camera->transform.up() * move_speed;
			else if (input_info.is_pressed(key_code_map::_e)) 
				camera->transform.position += camera->transform.up() * move_speed;
			
		}

		void operator_mouse() {
			auto& input_info = application::get().input();
			float move_speed = 0.1f * timer::delta().count();
			if (input_info.is_pressed(mouse_code_map::_right)) {
				auto current_pos = input_info.get_mouse_pos();
				pair delta{ current_pos.first - last_mouse_pos_.first,current_pos.second - last_mouse_pos_.second };
				camera->transform.rotation += glm::vec3(delta.second * move_speed, delta.first * move_speed, 0);
			}
		}

	public:
		pair<float,float> last_mouse_pos_{};
		rendering::color  color_data;
	};


}
