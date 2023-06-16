#pragma once

//Í³Ò»µÄ¿â
#include"Core.h"
#include"Events/EventCore.h"
#include"Log.h"

#include<memory>

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

