#pragma once

//ͳһ��Chisato�⡣

#include"ChisatoCore/App.h"

#include<ChisatoCore/Core.h>
#include<ChisatoCore/Events/EventLib.h>
#include<ChisatoCore/Layers/LayerLib.h>
#include<ChisatoCore/Tools/ToolLib.h>

/*************************************������***********************************/
#ifdef CST_PLATFORM_WINDOWS

int main(int argc, char** argv) {
	auto app = Chisato::Create();
	app->Main();
}

#endif
/*****************************************************************************/

