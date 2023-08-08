#include "pch.h"
#include "Wnd_Windows.h"

namespace Chisato {
	static bool s_GLFWInitialized = false;

	Window* Window::Creat(const WndProps& props) { return new Wnd_Windows(props); }
	
	Wnd_Windows::Wnd_Windows(const WndProps& props) :
		data{props} 
	{
		Log::Funcs<Log::Engine>::Trace("Create " + GetName());
		Init(props);
	}
	Wnd_Windows::~Wnd_Windows() { Close(); }
	
	void Wnd_Windows::Init(const WndProps& props) {
		if (!s_GLFWInitialized) {
			int s = glfwInit();
			CST_ASSERT(s, "Could not initialize GLFW!!");
			s_GLFWInitialized = true;
		}
		wnd = glfwCreateWindow((int)data.size.first, (int)data.size.second, data.title.c_str(), nullptr, nullptr);
		
		glfwMakeContextCurrent(wnd);
		glfwSetWindowUserPointer(wnd, &data);
		SetVSync(true);

		//Set GLFW Event Call Back
		glfwSetErrorCallback([](int code, const char* description) mutable{
			Log::Engine::Error("GLFW Error ({2}): {1}", description, code); 
		});

		glfwSetWindowSizeCallback(wnd, [](GLFWwindow* wnd, int w, int h) {
			auto data = *(WndData*)glfwGetWindowUserPointer(wnd);
			data.size = { w,h };

			WindowResizeEvent e(w, h);
			data.callback(e);

		});

		glfwSetWindowCloseCallback(wnd, [](GLFWwindow* wnd) {
			auto data = *(WndData*)glfwGetWindowUserPointer(wnd);

			WindowCloseEvent e;
			data.callback(e);
				
		});

		glfwSetMouseButtonCallback(wnd, [](GLFWwindow* wnd, int button, int action, int mods) {
			auto data = *(WndData*)glfwGetWindowUserPointer(wnd);
			switch (action) {
				case GLFW_PRESS: {
					MouseDownEvent e{button}; 
					data.callback(e);
					break;
				}
				case GLFW_REPEAT:{
					MouseHoldEvent e{ button,mods };
					data.callback(e);
					break;
				}
				case GLFW_RELEASE: {
					MouseUpEvent e{button}; 
					data.callback(e);
					break;
				}
			}
		});

		glfwSetCursorPosCallback(wnd, [](GLFWwindow* wnd, double x, double y) {
			auto data = *(WndData*)glfwGetWindowUserPointer(wnd);
			MouseMoveEvent e({ x,y });
			data.callback(e);
		});

	}

	void Wnd_Windows::Close() { glfwDestroyWindow(wnd); }

	void Wnd_Windows::OnUpdate() {
		glfwPollEvents();
		glfwSwapBuffers(wnd);

	}
}