#pragma once

//ͳһ��Chisato�⡣

#include"ChisatoCore/application.h"


/*************************************������***********************************/
#ifdef CST_PLATFORM_WINDOWS

int main() {
	cst::application::handle_ = cst::create();
	try { cst::application::get().main(); }
	catch (cst::debug::exception& e) { cst::debug::log<>::error(e.get_what()); }
	catch (std::exception& e) { cst::debug::log<>::error(e.what()); }
}

#endif
/*****************************************************************************/

