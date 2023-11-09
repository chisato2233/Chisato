#include"system.h"

cst::async::system* cst::async::system::instance = nullptr;

namespace cst::async {
	//	next_frame standard_promise::initial_suspend() noexcept{ return next_frame{}; }

	void system::update() {
		update_time();
		update_stop();

		update_ready();
		
		for(auto& i:suspend_list) {
			auto& ii = async_pool[i];
			if (ii.promise().state == promise_state::Stop) {
				async_pool.erase(i);
				continue;
			}
			ii.resume();

		}

	}

	void system::push_to_time(float time, Iasync& async_task) {
		const auto should_time = cst::time::now() + time;
		time_queue.push({ should_time,async_task.promise().get_id() });
	}


	void system::update_time() {
		auto t = cst::time::now();
		while (!time_queue.empty()) {
			auto& tt = time_queue.top();
			if (tt.time <= t) {
				push_to_ready(tt.id);
				time_queue.pop();
			}
			else break;
		}
	}

	void system::update_stop()
	{
	}

	void system::update_ready()
	{
		//while (!ready_queue.empty()) {
		//	auto handle = ready_queue.front().get().get_return_object();
		//	ready_queue.pop();

		//	if (!handle.done()) handle.resume();
		//}
	}

	void seconds::await_suspend(std::coroutine_handle<standard_promise> handle)const noexcept {
		//auto& ii = handle.promise();
		////auto& ii = dynamic_cast<Iasync&>(handle.promise());
		//system::get().push_to_time(time, ii);
	}

	void next_frame::await_suspend(std::coroutine_handle<standard_promise> handle)const noexcept {
		//auto& ii = handle.promise();
		////auto& ii = dynamic_cast<Iasync&>(i);
		//system::get().push_to_update(ii);
	}
}