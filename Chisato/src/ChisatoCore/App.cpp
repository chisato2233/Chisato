#include "App.h"

namespace Chisato {
	App::App(){

	}

	App::~App(){

	}

	void App::AppInit() {
		Log::Init();
		Log::Cosole::Info("Initialized succsese");
	}
	void App::AppMain(){
		AppInit();
		Log::Cosole::Info("Hello, Chisato");
		Events::KeyDownEvent a(1);		
		Log::Cosole::Trace(a.GetName());
		while (1);
	}
}
