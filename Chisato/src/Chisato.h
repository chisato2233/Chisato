#pragma once

//统一的Chisato库。
#include<iostream>


#include"ChisatoCore/App.h"
#include"ChisatoCore/Log.h"

/*************************************主函数***********************************/
#ifdef CST_PLATFORM_WINDOWS

int main(int argc, char** argv) {

	Chisato::Log::Init();
	
	Chisato::Log::Engine::Error("error!!");
	Chisato::Log::Engine::Trace("good!!");

	auto app = Chisato::CreateApplication();
	app->AppMain();
}

#endif
/*****************************************************************************/

