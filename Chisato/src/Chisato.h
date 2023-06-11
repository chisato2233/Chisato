#pragma once

//统一的Chisato库。

#include<iostream>


#include"ChisatoCore/App.h"

/*************************************主函数***********************************/
#ifdef CST_PLATFORM_WINDOWS

extern std::unique_ptr<Chisato::App> Chisato::CreateApplication();

int main(int argc, char** argv) {
	std::cout << "Engine Start Vectory" << '\n';
	auto app = Chisato::CreateApplication();
	app->AppMain();
}

#endif
/*****************************************************************************/

