#pragma once

//Í³Ò»µÄ¿â
#include"Core.h"
#include"window.h"
#include "Layers/layer_stack.h"


int main();
namespace cst {

	class CSTAPI application {
		friend int ::main();

		static application* handle_;

		std::unique_ptr<window> wnd_;
		layer_stack layer_stack_;

	protected:
		bool is_running = true;
		auto& layers() { return layer_stack_; }
	public:

		application();
		~application() = default;
		void main();
		void on_event(event&);

		static auto& get() {
			CST_ASSERT(handle_, "Application has not created yet")
			return *handle_;
		}

		auto& window()	const { return *wnd_; }
	};

	application* create();

}


