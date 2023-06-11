#pragma once
#include"Core.h"
#include<memory>

namespace Chisato {
	
	class CSTAPI App{
	public:
		App();
		virtual ~App();
		
		void AppMain();
	};

	std::unique_ptr<App> CreateApplication();
}

