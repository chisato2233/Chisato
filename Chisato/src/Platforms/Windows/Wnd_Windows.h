#pragma once
#include"ChisatoCore/Window.h"
#include"ChisatoCore/Events/EventCore.h"
#include"GLFW/glfw3.h"
#include"glad/glad.h"

namespace Chisato {

	
	class Wnd_Windows :public Window {
		GLFWwindow* wnd;

		struct WndData : WndProps {
			bool VSync;
			std::function<void(Event&)> callback;
		} data;

	public:
		Wnd_Windows(const WndProps& props);
		~Wnd_Windows() override;

		void OnUpdate() override;

		uint GetW()const override;
		uint GetH()const override;

		std::string GetName()const override;

		void SetEventCallback(const std::function<void(Event&)>& _callback) override;

		void SetVSync(bool enabled) override;

		bool IsVSync()const override;

	private:
		void Init(const WndProps& props);
	};
}