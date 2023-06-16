#pragma once

//统一的Chisato库。

#include"ChisatoCore/App.h"

/*************************************主函数***********************************/
#ifdef CST_PLATFORM_WINDOWS

int main(int argc, char** argv) {
	auto app = Chisato::CreateApplication();
	app->AppMain();
}

#endif
/*****************************************************************************/

