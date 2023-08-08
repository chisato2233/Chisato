#include "App.h"

namespace Chisato {
	App::App(){
		Log::Init();
		
		wnd = std::unique_ptr<Window>(Window::Creat());
		wnd->SetEventCallback(std::bind(&App::OnEvent, this, std::placeholders::_1));

		Log::Engine::Info("Initialized succsese");
		
	}
	App::~App(){ }

	void App::Main(){
		while (isRuning) {
			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			wnd->OnUpdate();
		}
	}

	void App::OnEvent(Event& e) {
		Log::Engine::Trace(e.GetName());
		
		EventManger m(e);
		m.Dispatch<WindowCloseEvent>(std::bind( [](App* papp,WindowCloseEvent& e) {papp->isRuning = false; return true; }, this, std::placeholders::_1));
		//if (!sucess) Log::Engine::Error("Do not doing WindowCloseEvent");
	}
}
