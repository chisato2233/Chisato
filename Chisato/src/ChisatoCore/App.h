#pragma once

//Í³Ò»µÄ¿â
#include"Core.h"
#include"Window.h"



namespace Chisato {
	
	class CSTAPI App {
		std::unique_ptr<Window> wnd;
		bool isRunning = true;

	protected:
		static App* handle;
		LayerStack layerStack;
	public:

		App();
		virtual ~App();
		void Main();
		void OnEvent(Event&);

		static auto& get() {
			CST_ASSERT(handle, "Application has not create yet");
			return *handle;
		}

		auto& GetWnd() const { return *wnd; }
	};

	App* Create();
}

