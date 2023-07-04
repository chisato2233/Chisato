#include"pch.h"

#include "App.h"

namespace Chisato {
	App::App(){

	}

	App::~App(){

	}

	class AB{};

	void App::AppInit() {
		Log::Init();
		Log::Engine::Info("Initialized succsese");
	}

	void App::AppMain(){
		AppInit();
		Log::Engine::Info("Hello, Chisato");

		Events::KeyDownEvent a(1);
		Log::Cosole::Trace(a);
		
		Events::WindowResizeEvent b(1080, 3060);
		Log::Cosole::Trace(b);
		
		
		
		while (1);
	}
}
