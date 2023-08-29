#include "pch.h"
#include "window_from_Windows.h"

namespace cst {
	static bool s_GLFWInitialized = false;

	window_base* window_base::create(const wnd_props& props) { return new window<platforms::Windows>(props); }
	
	window<platforms::Windows>::window(const wnd_props& props) :
		data_{props} 
	{
		init(props);
	}

	window<platforms::Windows>::~window() { glfwDestroyWindow(wnd_ptr_); }

	//init function
	void window<platforms::Windows>::init(const wnd_props& props)  {
		if (!s_GLFWInitialized) {
			int s = glfwInit();
			CST_ASSERT(s, "Could not initialize GLFW!!");
			s_GLFWInitialized = true;
		}

		wnd_ptr_ = glfwCreateWindow(static_cast<int>(data_.size.first), static_cast<int>(data_.size.second), data_.title.c_str(), nullptr, nullptr);
		
		glfwMakeContextCurrent(wnd_ptr_);

		int _ = gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress));
		CST_ASSERT(_ , "Could not initialize GLAD!!");

		glfwSetWindowUserPointer(wnd_ptr_, &data_);
		set_v_sync(true);

		//Set GLFW Event Call Back
		glfwSetErrorCallback([](int code, const char* description) mutable{
			debug::log<>::error("GLFW Error ({1}): {0}", description, code);
		});
		
		glfwSetWindowSizeCallback(wnd_ptr_, [](GLFWwindow* wnd, int w, int h) mutable {
			auto& data = *static_cast<WndData*>(glfwGetWindowUserPointer(wnd));
			data.size = { w,h };
			window_resize_event e(w, h);
			data.callback(e);
		});

		glfwSetWindowCloseCallback(wnd_ptr_, [](GLFWwindow* wnd) {
			auto& data = *static_cast<WndData*>(glfwGetWindowUserPointer(wnd));
			window_close_event e;
			data.callback(e);
				
		});
		
		glfwSetMouseButtonCallback(wnd_ptr_, [](GLFWwindow* wnd, int button, int action, int mods) {
			const auto& data = *static_cast<WndData*>(glfwGetWindowUserPointer(wnd));
			switch (action) {
				case GLFW_PRESS: {
					mouse_down_event e{button}; 
					data.callback(e);
					break;
				}
				case GLFW_REPEAT:{
					mouse_hold_event e{ button,mods };
					data.callback(e);
					break;
				}
				case GLFW_RELEASE: {
					mouse_up_event e{button}; 
					data.callback(e);
					break;
				}
			}
		});

		glfwSetCursorPosCallback(wnd_ptr_, [](GLFWwindow* wnd, double x, double y) {
			const auto& data = *static_cast<WndData*>(glfwGetWindowUserPointer(wnd));
			mouse_move_event e({ static_cast<float>(x),static_cast<float>(y) });
			data.callback(e);
		});

		glfwSetScrollCallback(wnd_ptr_, [](GLFWwindow* wnd, double x, double y) {
			const auto& data = *static_cast<WndData*>(glfwGetWindowUserPointer(wnd));
			mouse_scroll_event e{ {static_cast<float>(x),static_cast<float>(y)} };
			data.callback(e);
		});

		glfwSetKeyCallback(wnd_ptr_, [](GLFWwindow* wnd, int key, int scancode, int action, int mods) {
			auto& data = *static_cast<WndData*>(glfwGetWindowUserPointer(wnd));
			switch (action) {
				case GLFW_PRESS: {
					key_down_event e{ key };
					data.callback(e);
					break;
				}
				case GLFW_REPEAT: {
					key_hold_event e{ key,mods };
					data.callback(e);
					break;
				}
				case GLFW_RELEASE: {
					key_up_event e{ key };
					data.callback(e);
					break;
				}
			}
		});
		
		glfwSetCharCallback(wnd_ptr_, [](GLFWwindow* wnd, unsigned int codepoint) {
			const auto& data = *static_cast<WndData*>(glfwGetWindowUserPointer(wnd));
			key_char_event e{ codepoint };
			data.callback(e);
		});
	}

	void window<platforms::Windows>::set_v_sync(bool enabled) {
		if (enabled) glfwSwapInterval(1);
		else glfwSwapInterval(0);
		data_.v_sync = enabled;
	}

}
