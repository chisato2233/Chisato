#pragma once

//Í³Ò»µÄ¿â
#include"Core.h"
#include"Events/EventCore.h"
#include"NewEvent/Event.h"
#include"Log.h"


namespace Chisato {
	
	class CSTAPI App{
	public:
		App();
		virtual ~App();
		
		void AppInit();
		void AppMain();
	};

	std::unique_ptr<App> CreateApplication();
}

