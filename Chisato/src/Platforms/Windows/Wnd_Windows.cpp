#include "pch.h"
#include "Wnd_Windows.h"

namespace Chisato {
	static bool s_GLFWInitialized = false;

	Window* Window::Create(const WndProps& props) { return new Wnd_Windows(props); }
	
	Wnd_Windows::Wnd_Windows(const WndProps& props) :
		data{props} 
	{

		if (!s_GLFWInitialized) {
			int s = glfwInit();
			CST_ASSERT(s, "Could not initialize GLFW!!");
			s_GLFWInitialized = true;
		}

		wnd = glfwCreateWindow(static_cast<int>(data.size.first), static_cast<int>(data.size.second), data.title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(wnd);

		int _ = gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress));
		CST_ASSERT(_, "Could not initialize GLAD!!");

		glfwSetWindowUserPointer(wnd, &data);
		SetVSync(true);

		//Set GLFW Event Call Back
		glfwSetErrorCallback([](int code, const char* description) mutable {
			Debug::Log<Debug::Engine>::Error("GLFW Error ({1}): {0}", description, code);
		});

		glfwSetWindowSizeCallback(wnd, [](GLFWwindow* wnd, int w, int h) {
			auto data = *static_cast<WndData*>(glfwGetWindowUserPointer(wnd));
			data.size = { w,h };

			WindowResizeEvent e(w, h);
			data.callback(e);

		});

		glfwSetWindowCloseCallback(wnd, [](GLFWwindow* wnd) {
			auto data = *static_cast<WndData*>(glfwGetWindowUserPointer(wnd));

			WindowCloseEvent e;
			data.callback(e);

		});

		glfwSetMouseButtonCallback(wnd, [](GLFWwindow* wnd, int button, int action, int mods) {
			auto data = *static_cast<WndData*>(glfwGetWindowUserPointer(wnd));
			switch (action) {
			case GLFW_PRESS: {
				MouseDownEvent e{ button };
				data.callback(e);
				break;
			}
			case GLFW_REPEAT: {
				MouseHoldEvent e{ button,mods };
				data.callback(e);
				break;
			}
			case GLFW_RELEASE: {
				MouseUpEvent e{ button };
				data.callback(e);
				break;
			}
			}
		});

		glfwSetCursorPosCallback(wnd, [](GLFWwindow* wnd, double x, double y) {
			auto& data = *static_cast<WndData*>(glfwGetWindowUserPointer(wnd));
			MouseMoveEvent e({ static_cast<float>(x),static_cast<float>(y) });
			data.callback(e);
		});

		glfwSetScrollCallback(wnd, [](GLFWwindow* wnd, double x, double y) {
			auto data = *static_cast<WndData*>(glfwGetWindowUserPointer(wnd));
			MouseScrollEvent e{ {static_cast<float>(x),static_cast<float>(y)} };
			data.callback(e);
		});
	}

	Wnd_Windows::~Wnd_Windows() { glfwDestroyWindow(wnd); }
	
	void Wnd_Windows::Init(const WndProps& props)  {
		//Log::Funcs<Log::Engine>::Trace("Create {}", GetName());

		if (!s_GLFWInitialized) {
			int s = glfwInit();
			CST_ASSERT(s, "Could not initialize GLFW!!");
			s_GLFWInitialized = true;
		}

		wnd = glfwCreateWindow(static_cast<int>(data.size.first), static_cast<int>(data.size.second), data.title.c_str(), nullptr, nullptr);
		
		glfwMakeContextCurrent(wnd);

		int _ = gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress));
		CST_ASSERT(_ , "Could not initialize GLAD!!");

		glfwSetWindowUserPointer(wnd, &data);
		SetVSync(true);

		//Set GLFW Event Call Back
		glfwSetErrorCallback([](int code, const char* description) mutable{
			Debug::Log<Debug::Engine>::Error("GLFW Error ({1}): {0}", description, code);
		});
		
		glfwSetWindowSizeCallback(wnd, [](GLFWwindow* wnd, int w, int h) {
			auto& data = *static_cast<WndData*>(glfwGetWindowUserPointer(wnd));
			data.size = { w,h };
			Debug::Log<Debug::Engine>::Error("in it");

			WindowResizeEvent e(w, h);
			data.callback(e);

		});

		glfwSetWindowCloseCallback(wnd, [](GLFWwindow* wnd) {
			auto& data = *static_cast<WndData*>(glfwGetWindowUserPointer(wnd));
			Debug::Log<Debug::Engine>::Error("in it");
			WindowCloseEvent e;
			data.callback(e);
				
		});

		glfwSetMouseButtonCallback(wnd, [](GLFWwindow* wnd, int button, int action, int mods) {
			auto& data = *static_cast<WndData*>(glfwGetWindowUserPointer(wnd));
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
			auto& data = *static_cast<WndData*>(glfwGetWindowUserPointer(wnd));
			MouseMoveEvent e({ static_cast<float>(x),static_cast<float>(y) });
			data.callback(e);
		});

		glfwSetScrollCallback(wnd, [](GLFWwindow* wnd, double x, double y) {
			auto& data = *static_cast<WndData*>(glfwGetWindowUserPointer(wnd));
			MouseScrollEvent e{ {static_cast<float>(x),static_cast<float>(y)} };
			data.callback(e);
		});
	}

	void Wnd_Windows::OnUpdate() {
		glfwPollEvents();
		glfwSwapBuffers(wnd);

	}

	uint Wnd_Windows::GetW() const { return data.size.first; }
	uint Wnd_Windows::GetH() const { return data.size.second; }
	std::string Wnd_Windows::GetName() const {
		return std::format("{} Window({},{}), form Windows ", data.title, GetW(), GetH());
	}
	void Wnd_Windows::SetEventCallback(const std::function<void(Event&)>& _callback) { data.callback = _callback; }
	void Wnd_Windows::SetVSync(bool enabled) {
		if (enabled) glfwSwapInterval(1);
		else glfwSwapInterval(0);
		data.VSync = enabled;
	}
	bool Wnd_Windows::IsVSync() const { return data.VSync; }
}
