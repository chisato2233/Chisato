#pragma once

//统一的Chisato库。

#include"ChisatoCore/App.h"

#include<ChisatoCore/Core.h>
#include<ChisatoCore/Events/EventLib.h>
#include<ChisatoCore/Layers/LayerLib.h>
#include<ChisatoCore/Tools/ToolLib.h>

/*************************************主函数***********************************/
#ifdef CST_PLATFORM_WINDOWS

int main(int argc, char** argv) {
	auto app = Chisato::Create();
	app->Main();
}

#endif
/*****************************************************************************/

