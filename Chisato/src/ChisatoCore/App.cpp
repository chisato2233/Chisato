#include "App.h"
#include"GLFW/glfw3.h"
#include"Log.h"

namespace Chisato {
	App::App(){
		Log::Init();
		
		wnd = std::unique_ptr<Window>(Window::Create());
		wnd->SetEventCallback([this](Event& PH1) { OnEvent((PH1)); });

		Log::Engine::Info("Initialized success");
		
	}
	App::~App() = default;

	void App::Main(){
		while (isRunning) {
			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			for(auto& i:layerStack) i->OnUpdate();

			wnd->OnUpdate();
		}
	}

	void App::OnEvent(Event& e) {
		Log::Engine::Trace(e.GetName());

		for (const auto& i : layerStack) {
			i->OnEvent(e);
			if (!e.isActive) break;
		}

		EventManger m(e);
		m.Dispatch<WindowCloseEvent>([this](WindowCloseEvent& e) {isRunning = false; return true; });
	}
}
