#pragma once

//ͳһ��Chisato�⡣

#include"ChisatoCore/App.h"

/*************************************������***********************************/
#ifdef CST_PLATFORM_WINDOWS

int main(int argc, char** argv) {
	auto app = Chisato::CreateApplication();
	app->AppMain();
}

#endif
/*****************************************************************************/

