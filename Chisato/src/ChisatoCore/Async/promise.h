#pragma once
#include<coroutine>
namespace cst::async {
	enum class promise_state {
		Init,
		Ready,
		Suspend,
		Stop,
	};

	struct CSTAPI standard_promise {

		standard_promise() { async_id = async_id++; }

		standard_promise(auto&& Obj) {
			async_id = async_id++;
		}

		auto get_return_object() { return std::coroutine_handle<standard_promise>::from_promise(*this); }

		auto initial_suspend() noexcept { return std::suspend_always{}; }
		auto final_suspend() noexcept { return std::suspend_never{}; }
		void return_void() {}
		static void unhandled_exception() { std::terminate(); }

		int get_id() const { return async_id; }
		
		promise_state state = promise_state::Init;

	private:
		int async_id = 0;
		inline static int async_next_id = 0;
	};
};