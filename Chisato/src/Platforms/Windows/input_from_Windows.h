#pragma once
#include<ChisatoCore/input.h>
#include<ChisatoCore/application.h>
#include"GLFW/glfw3.h"

namespace cst {
	template<cpt_plat P> struct CSTAPI input_information;


	template<>
	struct CSTAPI input_information<platforms::Windows> : input_base {

		bool is_key_pressed(int key) override {
			const auto p_wnd = static_cast<GLFWwindow*>(application::get().window().get_wnd_ptr());
			return glfwGetKey(p_wnd, key) == GLFW_PRESS;
		}

		bool is_mouse_button_pressed(int button)override {
			const auto p_wnd = static_cast<GLFWwindow*>(application::get().window().get_wnd_ptr());
			return glfwGetMouseButton(p_wnd, button) == GLFW_PRESS;
		}

		std::pair<float, float> get_mouse_pos() override {
			const auto p_wnd = static_cast<GLFWwindow*>(application::get().window().get_wnd_ptr());
			double x, y;
			glfwGetCursorPos(p_wnd, &x,&y);

			return { static_cast<float>(x),static_cast<float>(y) };
		}
	};
}