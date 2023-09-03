#pragma once

//Í³Ò»µÄ¿â
#include"Core.h"
#include "input_base.h"
#include"window_base.h"
#include "Layers/layer_stack.h"
#include"Tools/ToolLib.h"


int main();
namespace cst {
	class CSTAPI application;
	//template<std::derived_from<application> App> CSTAPI int engine_main();

	class CSTAPI application {
		template<std::derived_from<application> App>
		friend CSTAPI int engine_run();

		static application* handle_;

		std::unique_ptr<window_base> wnd_;
		std::unique_ptr<input_base> input_;

		layer_stack layer_stack_;

	protected:
		application();
		bool is_running = true;
		auto& layers() { return layer_stack_; }
	public:

		~application() = default;
		void main();
		void on_event(event&);
		static auto& get() {
			CST_ASSERT(handle_, "Application has not created yet")
			return *handle_;
		}

		auto& window()	const { return *wnd_; }
		auto& input()	const { return *input_; }
	};

	#include"ChisatoCore/engine_run.h"
}


