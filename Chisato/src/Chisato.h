#pragma once

//ͳһ��Chisato�⡣
#include<iostream>


#include"ChisatoCore/App.h"
#include"ChisatoCore/Log.h"

/*************************************������***********************************/
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

