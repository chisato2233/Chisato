#pragma once
#include"ChisatoCore/Window.h"
#include"ChisatoCore/Log.h"
#include"ChisatoCore/Events/EventCore.h"
#include"GLFW/glfw3.h"

namespace Chisato {

	class Wnd_Windows :public Window {
	private:
		GLFWwindow* wnd;

		struct WndData : WndProps {
			bool VSync;
			std::function<void(Event&)> callback;
		} data;

	public:
		Wnd_Windows(const WndProps& props);
		virtual ~Wnd_Windows();

		void OnUpdate() override;
		void Close()override;

		inline uint GetW()const override { return data.size.first; }
		inline uint GetH()const override { return data.size.second; }
		inline std::string GetName()const override {
			return std::format("{} Window({},{}), form Windows ", data.title, GetW(), GetH());
		}

		inline void SetEventCallback(const std::function<void(Event&)>& _callback) override { data.callback = _callback; }

		inline void SetVSync(bool enabled) {
			if (enabled) glfwSwapInterval(1);
			else glfwSwapInterval(0);
			data.VSync = enabled;
		}
		inline bool IsVSync()const { return data.VSync; }

	private:
		virtual void Init(const WndProps& props);
	};
}