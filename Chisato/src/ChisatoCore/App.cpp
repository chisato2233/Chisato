
#include "App.h"

namespace Chisato {
	App::App(){
		AppInit();
		wnd = std::unique_ptr<Window>(Window::Creat());
	}

	App::~App(){

	}

	void App::AppInit() {
		Log::Init();
		Log::Engine::Info("Initialized succsese");
	}

	void App::AppMain(){
		while (isRuning) {
			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			wnd->OnUpdate();
		}
	}
}
