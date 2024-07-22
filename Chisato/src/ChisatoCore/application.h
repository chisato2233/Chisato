#pragma once

//统一的库
#include "application.h"
#include"Core.h"
#include "input.h"
#include"window_base.h"
#include "Async/runtime.h"
#include "Layers/layer_stack.h"

//#include"Async/async_lib.h"

//using namespace std;
int main();
namespace cst {


	using namespace std;
	class CSTAPI application;
	
	//template<std::derived_from<application> App> CSTAPI int engine_main();

	class CSTAPI application : no_copy,no_move{
		template<std::derived_from<application> App>

		friend CSTAPI int engine_run();

		static application* handle_;

		std::unique_ptr<window_base> wnd_;
		std::unique_ptr<input_base> input_;
		std::unique_ptr<async::runtime> app_runtime_;
		layer_stack layer_stack_;

	public:
		delegate<application, void()> on_app_created{ this };
		delegate<application, void()> on_start	{ this };
		delegate<application, void()> on_stop	{ this };
		delegate<application, void()> on_update	{ this };


	protected:
		application();
		bool is_running = true;
		auto& layers() { return layer_stack_; }
	public:

		~application() = default;

		void main();


		void on_event(event&);
		static auto& get() {
			CST_ASSERT(handle_, "Application has not created yet, pleace excute function engine_run to create Chisato Engine Application first");
			return *handle_;
		}


		static auto& window() { return *get().wnd_; }
		static auto& async_runtime()  { return *get().app_runtime_; }
		static auto& input_info()	 { return *get().input_; }
	};


	
}


