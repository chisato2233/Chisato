#pragma once
#include"Core.h"


namespace Chisato {
	
	class CSTAPI App{
	public:
		App();
		virtual ~App();

		void AppMain();

	};

	App* CreateApplication();
}

