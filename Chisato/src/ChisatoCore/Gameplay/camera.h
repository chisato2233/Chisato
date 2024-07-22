#pragma once
#include "ChisatoCore/Async/awaiter.h"
#include "ChisatoCore/Rendering/transform.h"
#include"ChisatoCore/Rendering/camera.h"

namespace cst::gameplay {


	struct camera2D : auto_remove_from_delegate{
		transform transform {};
		ptr<rendering::orthographic_viewport> viewport;
		float move_speed = 10.f;
		bool enable_control_viewport = true;

		explicit camera2D(rptr<rendering::orthographic_viewport> viewport_) :viewport(viewport_){
			input::mouse::on_scroll .add(this, [this](mouse_scroll_event e) {
				if (enable_control_viewport)
					viewport->zoom(e.get_y());
			});
		}

		auto control_camera() -> async::co_task<> {
			using namespace async;


			while (true) {
				if(enable_control_viewport) {
					co_await wait_next_frame{};
					operator_key();
					last_mouse_pos_ = application::input_info().get_mouse_pos();
				}
			}
		}

		void operator_key() const {
			auto& input_info = application::input_info();
			float ms = move_speed * timer::delta().count();
			

			if (input_info.is_pressed(key_code_map::_a))
				viewport->transform.position -= viewport->transform.right() * ms;
			else if (input_info.is_pressed(key_code_map::_d))
				viewport->transform.position += viewport->transform.right() * ms;


			if (input_info.is_pressed(key_code_map::_w))
				viewport->transform.position -= viewport->transform.up() * ms;
			else if (input_info.is_pressed(key_code_map::_s))
				viewport->transform.position += viewport->transform.up() * ms;

		}


	public:
		pair<float, float> last_mouse_pos_{};
	};

}
