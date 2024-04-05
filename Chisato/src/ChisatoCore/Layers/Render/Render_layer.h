#pragma once
#include "Drawable.h"
#include "ChisatoCore/keycode.h"
#include "ChisatoCore/Async/awaiter.h"
#include"ChisatoCore/Layers/Layer.h"
#include "ChisatoCore/Layers/ImGui/ImGui_layer.h"
#include "ChisatoCore/Rendering/matearial.h"
#include "ChisatoCore/UI/test.h"
#include "glm/gtc/type_ptr.hpp"


namespace cst {
	struct CSTAPI Render_layer : layer {
		Render_layer() :layer("Render") {}
		void on_attach() override;
		void on_update() override;
		void on_event(event& event) override;

		std::vector<ptr<drawable>> graphics;
		ptr<orthographic_camera> camera;


		auto control_camera()->async::co_task<> {
			using namespace async;


			while(true) {
				

				auto& input_info = application::get().input();
				float move_speed = 10 * timer::delta().count();

				if (input_info.is_pressed(key_code_map::_w))
					camera->transform.position -= glm::vec3(0, move_speed, 0);
				else if (input_info.is_pressed(key_code_map::_s))
					camera->transform.position += glm::vec3(0, move_speed, 0);
				else if (input_info.is_pressed(key_code_map::_a))
					camera->transform.position += glm::vec3(move_speed, 0, 0);
				else if (input_info.is_pressed(key_code_map::_d))
					camera->transform.position -= glm::vec3(move_speed, 0, 0);
				else if (input_info.is_pressed(key_code_map::_q))
					camera->transform.position += glm::vec3(0, 0, move_speed);
				else if (input_info.is_pressed(key_code_map::_e))
					camera->transform.position -= glm::vec3(0, 0, move_speed);

				co_await wait_next_frame{};
			}
		}

		void set_ui() {
			ImGui_layer::UI_drawer += [this] {
				cst::ui::window{
					.body = {
						ui::ui_element{
							.on_build = [this] {
								ImGui::ColorEdit4("color",
							value_ptr(*dynamic_cast<glm::vec4*>(&color_data)));
							},
						}
					},
				}.build();
			};
		}



	public:
		rendering::color color_data{1.0f};
	}; 
}
