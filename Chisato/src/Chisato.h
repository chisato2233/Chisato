#pragma once

//统一的Chisato库。

#include"ChisatoCore/application.h"


/*************************************主函数***********************************/
#ifdef CST_PLATFORM_WINDOWS

int main() {
	cst::application::handle_ = cst::create();
	try { cst::application::get().main(); }
	catch (cst::debug::exception& e) { cst::debug::log<>::error(e.get_what()); }
	catch (std::exception& e) { cst::debug::log<>::error(e.what()); }
}

#endif
/*****************************************************************************/

