#pragma once
#ifdef CST_PLATFORM_WINDOWS

template<std::derived_from<application> App>
int engine_run() {
	application::handle_ = new App{};
	try { application::get().main(); }
	catch (debug::exception& e) { debug::log<>::error("{}", e.get_what()); }
	catch (std::exception& e) { debug::log<>::error("[std exception]: \"{}\"", e.what()); }

	return 0;
}

#endif