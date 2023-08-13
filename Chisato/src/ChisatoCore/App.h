#pragma once

//Í³Ò»µÄ¿â
#include"Core.h"
#include"Window.h"
#include"Events/EventCore.h"
#include"LayerStack.h"



namespace Chisato {
	
	class CSTAPI App {
		std::unique_ptr<Window> wnd;
		bool isRunning = true;

	protected:
		LayerStack layerStack;
	public:

		App();
		virtual ~App();

		void Main();
		void OnEvent(Event&);


	
	};

	App* Create();
}

