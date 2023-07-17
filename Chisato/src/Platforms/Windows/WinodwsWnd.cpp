#include "pch.h"
#include "WinodwsWnd.h"

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

	}

	void Wnd_Windows::Close() {
		glfwDestroyWindow(wnd);
	}

	void Wnd_Windows::OnUpdate() {
		glfwPollEvents();
		glfwSwapBuffers(wnd);

	}


	void Wnd_Windows::SetVSync(bool enabled) {
		if (enabled) glfwSwapInterval(1);
		else glfwSwapInterval(0);
		data.VSync = enabled;
	}

	bool Wnd_Windows::IsVSync()const {
		return data.VSync;
	}
}