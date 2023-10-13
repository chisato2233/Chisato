#include"Coroutine.h"

cst::async::system* cst::async::system::instance = nullptr;

namespace cst::async {
	//	next_frame standard_promise::initial_suspend() noexcept{ return next_frame{}; }

	void system::update() {
		//debug::log<>::info("update");
		while (!ready_queue.empty()) {
			auto handle = ready_queue.front().get().get_return_object();
			ready_queue.pop();

			if (!handle.done()) handle.resume();
		}

		while (!update_queue.empty()) {
			push_to_ready(update_queue.front());
			update_queue.pop();
		}


		auto t = cst::time::now();
		while (!time_queue.empty()) {
			auto& tt = time_queue.top();
			if (tt.time <= t) {
				push_to_ready(tt.async_task);
				time_queue.pop();
			}
			else break;
		}
	}

	void system::push_to_time(float time, Iasync& async_task) {
		auto should_time=cst::time::now()+ time;
		time_queue.push({ should_time,async_task });
	}
	

	void seconds::await_suspend(std::coroutine_handle<standard_promise> handle)const noexcept {
		auto& ii = handle.promise();
		//auto& ii = dynamic_cast<Iasync&>(handle.promise());
		system::get().push_to_time(time,ii);
	}

	void next_frame::await_suspend(std::coroutine_handle<standard_promise> handle)const noexcept {
		auto& ii = handle.promise();
		//auto& ii = dynamic_cast<Iasync&>(i);
		system::get().push_to_update(ii);
	}
}