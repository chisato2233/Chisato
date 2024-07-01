#pragma once

//统一的Chisato库。
#include"ChisatoCore/application.h"
#include<ChisatoCore/Core.h>
#include<ChisatoCore/Events/event_lib.h>
#include<ChisatoCore/Layers/layer_lib.h>
#include<ChisatoCore/Tools/ToolLib.h>
#include<ChisatoCore/platforms.h>



//Chisato Rendering库
#include<ChisatoCore/Rendering/Renderer.h>
#include<ChisatoCore/Rendering/renderer_context.h>
#include<ChisatoCore/Rendering/Shader.h>
#include<ChisatoCore/Rendering/Texture.h>
#include<ChisatoCore/Rendering/Buffer.h>




/*************************************主函数***********************************/
#ifdef CST_PLATFORM_WINDOWS
namespace cst {
	
	template<std::derived_from<application> App>
	int engine_run() {
		application::handle_ = new App{};

		try {
			application::get().on_app_created();
			application::get().main();
		}

		catch (debug::exception& e) { debug::log<>::error("{}", e.get_what()); }
		catch (std::exception& e) { debug::log<>::error("[std exception]: \"{}\"", e.what()); }

		return 0;
	}
}


#endif
/*****************************************************************************/

