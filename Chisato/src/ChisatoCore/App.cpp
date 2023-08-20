#include "App.h"
#include <glad/glad.h>
#include"Log.h"

namespace Chisato {
	App::App(){
		using namespace Debug;
		Init();
		
		wnd = std::unique_ptr<Window>(Window::Create());
		wnd->SetEventCallback([this](Event& PH1) { OnEvent((PH1)); });
		Log<Engine>::Info("Initialize app success!");
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
		using namespace Debug;

		for (auto i = layerStack.end(); i != layerStack.begin();) {
			(**--i).OnEvent(e);
			if (!e.isActive) break;
		}

		EventManger m(e);
		m.Dispatch<WindowCloseEvent>([this](WindowCloseEvent& e) {isRunning = false; return true; });
		
		if (e.isActive) Log<Engine>::Trace(e.GetName());
	}

}
