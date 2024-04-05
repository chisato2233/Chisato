#include "pch.h"
#include "window_from_Windows.h"

#include "ChisatoCore/input.h"

namespace cst {
	static bool s_GLFWInitialized = false;

	
	window_base* window_base::create(const wnd_props& props) { return new window<platforms::Windows>(props); }
	
	window<platforms::Windows>::window(const wnd_props& props) :
		data_{props} 
	{
		init(props);
	}

	window<platforms::Windows>::~window() { glfwDestroyWindow(wnd_ptr_); }


	void window<platforms::Windows>::on_update() {
		glfwPollEvents();
		renderer_context_->swap_buffers();
		
	}

	//init function
	void window<platforms::Windows>::init(const wnd_props& props)  {
		if (!s_GLFWInitialized) {
			int s = glfwInit();
			CST_ASSERT(s, "Could not initialize GLFW!!");
			s_GLFWInitialized = true;
		}

		wnd_ptr_ = glfwCreateWindow(static_cast<int>(data_.size.first), static_cast<int>(data_.size.second), data_.title.c_str(), nullptr, nullptr);
		renderer_context_ = std::make_unique<opengl_renderer_context>(wnd_ptr_);

		renderer_context_->init();




		glfwSetWindowUserPointer(wnd_ptr_, &data_);
		set_v_sync(false);

		//Set GLFW Event Call Back
		glfwSetErrorCallback([](int code, const char* description) mutable{
			debug::log<>::error("GLFW Error ({1}): {0}", description, code);
		});
		
		glfwSetWindowSizeCallback(wnd_ptr_, [](GLFWwindow* wnd, int w, int h) mutable {
			auto& data = *static_cast<WndData*>(glfwGetWindowUserPointer(wnd));
			data.size = { w,h };
			window_resize_event e(w, h);
			input::window::on_resize(e);
			data.callback(e);
		});

		glfwSetWindowCloseCallback(wnd_ptr_, [](GLFWwindow* wnd) {
			auto& data = *static_cast<WndData*>(glfwGetWindowUserPointer(wnd));
			window_close_event e;
			input::window::on_close(e);
			data.callback(e);
				
		});
		
		glfwSetMouseButtonCallback(wnd_ptr_, [](GLFWwindow* wnd, int button, int action, int mods) {
			const auto& data = *static_cast<WndData*>(glfwGetWindowUserPointer(wnd));
			switch (action) {
				case GLFW_PRESS: {
					mouse_down_event e{button};
					switch(button) {
						case GLFW_MOUSE_BUTTON_LEFT: input::mouse::on_left_down(e); break;
						case GLFW_MOUSE_BUTTON_RIGHT: input::mouse::on_right_down(e); break;
						case GLFW_MOUSE_BUTTON_MIDDLE: input::mouse::on_middle_down(e); break;
					}
					
					data.callback(e);
					break;
				}
				case GLFW_REPEAT:{
					mouse_hold_event e{ button,mods };
					switch (button) {
						case GLFW_MOUSE_BUTTON_LEFT: input::mouse::on_left_hold(e); break;
						case GLFW_MOUSE_BUTTON_RIGHT: input::mouse::on_right_hold(e); break;
						case GLFW_MOUSE_BUTTON_MIDDLE: input::mouse::on_middle_hold(e); break;
					}
					data.callback(e);
					break;
				}
				case GLFW_RELEASE: {
					mouse_up_event e{button}; 
					switch (button) {
						case GLFW_MOUSE_BUTTON_LEFT: input::mouse::on_left_up(e); break;
						case GLFW_MOUSE_BUTTON_RIGHT: input::mouse::on_right_up(e); break;
						case GLFW_MOUSE_BUTTON_MIDDLE: input::mouse::on_middle_up(e); break;
					}
					data.callback(e);
					break;
				}
			}
		});

		glfwSetCursorPosCallback(wnd_ptr_, [](GLFWwindow* wnd, double x, double y) {
			const auto& data = *static_cast<WndData*>(glfwGetWindowUserPointer(wnd));
			mouse_move_event e({ static_cast<float>(x),static_cast<float>(y) });
			input::mouse::on_move(e);
			data.callback(e);
		});

		glfwSetScrollCallback(wnd_ptr_, [](GLFWwindow* wnd, double x, double y) {
			const auto& data = *static_cast<WndData*>(glfwGetWindowUserPointer(wnd));
			mouse_scroll_event e{ {static_cast<float>(x),static_cast<float>(y)} };
			input::mouse::on_scroll(e);
			data.callback(e);
		});

		glfwSetKeyCallback(wnd_ptr_, [](GLFWwindow* wnd, int key, int scancode, int action, int mods) {
			auto& data = *static_cast<WndData*>(glfwGetWindowUserPointer(wnd));
			switch (action) {
				case GLFW_PRESS: {
					key_down_event e{ key };
					input::keyboard::on_down(e);
					data.callback(e);
					break;
				}
				case GLFW_REPEAT: {
					key_hold_event e{ key,mods };
					input::keyboard::on_hold(e);
					data.callback(e);
					break;
				}
				case GLFW_RELEASE: {
					key_up_event e{ key };
					input::keyboard::on_up(e);
					data.callback(e);
					break;
				}
			}
		});
		
		glfwSetCharCallback(wnd_ptr_, [](GLFWwindow* wnd, unsigned int codepoint) {
			const auto& data = *static_cast<WndData*>(glfwGetWindowUserPointer(wnd));
			key_char_event e{ codepoint };
			input::keyboard::on_char(e);
			data.callback(e);
		});
	}

	void window<platforms::Windows>::set_v_sync(bool enabled) {
		if (enabled) glfwSwapInterval(1);
		else glfwSwapInterval(0);

		data_.v_sync = enabled;
	}

}
