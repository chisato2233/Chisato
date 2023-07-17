#pragma once

//ͳһ�Ŀ�
#include"Core.h"
#include"Events/EventCore.h"
#include"NewEvent/Event.h"
#include"Log.h"
#include"Window.h"
#include"GLFW/glfw3.h"



namespace Chisato {
	
	class CSTAPI App{
	public:
		App();
		virtual ~App();
		
		void AppInit();
		void AppMain();
	private:
		std::unique_ptr<Window> wnd;
		bool isRuning = true;
	};

	App* CreateApplication();
}

