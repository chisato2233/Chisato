#pragma once
#include"ChisatoCore/Window.h"
#include"ChisatoCore/Log.h"
#include"GLFW/glfw3.h"

namespace Chisato {

	class Wnd_Windows :public Window {
	private:
		GLFWwindow* wnd;

		struct WndData : WndProps {
			bool VSync;
			EventCallback callback;
		} data;
	public:
		Wnd_Windows(const WndProps& props);
		virtual ~Wnd_Windows();

		void OnUpdate() override;

		inline uint GetW()const override { return data.size.first; }
		inline uint GetH()const override { return data.size.second; }
		inline std::string GetName()const override {
			return std::format("{} Window({},{}), form Windows ", data.title, GetW(), GetH());
		}

		inline void SetEventCallback(const EventCallback& _callback) override { data.callback = _callback; }

		void SetVSync(bool enabled);
		bool IsVSync()const;

	private:
		virtual void Init(const WndProps& props);
		virtual void Close();

	};
}