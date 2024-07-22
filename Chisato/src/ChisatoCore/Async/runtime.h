#pragma once

#include <queue>
#include <array>
#include <functional>
#include <map>

#include <ChisatoCore/Async/co_task.h>


#include"ChisatoCore/Tools/Time.h"

namespace cst::async {

	struct runtime{
		inline static constexpr int task_queue_num = 2;
		using task_id = uint64_t;
		using predicate_id = uint64_t;
		
		using task_queue_container = std::array<std::queue<co_task_base*>,task_queue_num >;
		using stop_queue_container = std::queue<unit<task_id, co_task_base*>>;
		using timer_queue_container = std::priority_queue<
			unit<game_time_point, task_id, co_task_base*>,
			std::vector<unit<game_time_point, task_id, co_task_base*>>,
			std::greater<>
		>;

		using predicate_container = std::unordered_map <predicate_id, unit<predicate_id, std::function<bool()>, co_task_base*>>;
		using suspend_container = std::list<co_task_base*>;

		runtime() = default;
		~runtime() { stop_all(); }

		struct register_option {
			ptr<co_task_base> task_ref;
			runtime* runtime_ref;
			bool is_rewrite = false;

			auto add_predicate(const std::function<bool()>& predicate )&& {
				is_rewrite = true;
				runtime_ref->predicate_map_.insert({ 
					++next_predicate_id_,
					{ task_ref->task_id(),predicate,task_ref.get()}
				});
				return std::move(task_ref);
			}

			template<class Rep, class Period>
			auto add_timer(std::chrono::duration<Rep,Period> duration)&& {
				is_rewrite = true;
				
				runtime_ref->timer_queue_.push({
					timer::now() + std::chrono::duration_cast<game_time_point>(duration),
					task_ref->task_id(),
					task_ref.get()
				});
				return std::move(task_ref);
			}
		};




		// register a task which well not start immediately, call start_task is a better choice
		// this function will return some options, which you can choose when you want to start the task
		template<class T>
		auto register_task(co_task<T>&& task)->register_option ;

		//cancel a task will destroy the task immediately, which is dangerous;
		//if you want to stop a task, call stop_task
		void cancel_task(co_task_base* task_ref);

		void cancel_task(task_id id);

		//registrite and start a task
		//do not use the capture of lambda to create a task, it will cause a dangling pointer
		template<class T>
		auto start_task(co_task<T>&& task) -> co_task<T>&;

		//registrite (if it doesn't) and start a task by task id 
		//do not use the capture of lambda to create a task, it will cause a dangling pointer
		auto start_task(task_id id) -> ptr<co_task_base> ;

		//stop a task by point;
		//please 
		void stop_task(co_task_base* task);

		//stop a task by id
		void stop_task(task_id id);

		//suspend a task by point
		void suspend_task(co_task_base* task);

		//suspend a task by id
		void suspend_task(task_id id);

		//resume a task by point
		//if the task is not suspend, it will do nothing
		void resume_task(co_task_base* task);

		//resume a task by id
		//if the task is not suspend, it will do nothing
		void resume_task(task_id id);

		void stop_all();


		void update() {

			// update predicate-------------------------------------------------------------
			_update_predicate();

			//update time queue--------------------------------------------------------------
			_update_timer_queue();

			//update task queue---------------------------------------------------------------
			_update_run_task_queue();

			//update suspend queue-------------------------------------------------------------
			_update_suspend_task();

			//update stop queue---------------------------------------------------------------
			_update_stop_task();

			//update cancel queue-------------------------------------------------------------
			_update_cancel_queue();
		}

		auto task_count()const noexcept->std::size_t {
			return task_map.size();
		}

	private:
		auto _get_task_queue() -> std::queue<co_task_base*>& {
			return task_queue_array_[task_queue_flag_];
		}

		void _start_task_from_point(co_task_base* task_ref) {
			
			task_ref->task_state() = task_state::ready;
			_get_task_queue().push(task_ref);
		}

		void _resume_task(void* task_ref) {
			static_cast<co_task_base*>(task_ref)->resume();
		}

		void _update_cancel_queue() {
			while (!cancel_queue.empty()) {
				cancel_queue.pop();
			}
		}

		void _update_run_task_queue();

		void _update_suspend_task();

		void _update_stop_task();

		void _update_timer_queue();

		void _update_predicate();

	public:

		std::map<task_id , ptr<co_task_base>> task_map;
		std::queue<ptr<co_task_base>> cancel_queue;
		bool enable_check_suspend_list = false;


	private:
		char task_queue_flag_ = 0;
		inline static predicate_id next_predicate_id_ = 0;

		task_queue_container task_queue_array_;
		std::mutex task_queue_mutex_;

		stop_queue_container stop_queue_;
		std::mutex stop_queue_mutex_;

		suspend_container suspend_list_;
		std::mutex suspend_list_mutex_;

		predicate_container predicate_map_;
		std::mutex predicate_map_mutex_;

		timer_queue_container timer_queue_;
		std::mutex timer_queue_mutex_;
	};

	inline void runtime::cancel_task(co_task_base* task_ref) {
		auto id = task_ref->task_id();
		auto state = task_ref->task_state();
		if(state == task_state::suspend) 
			suspend_list_.remove(task_ref);

		task_map.erase(id);
			
	}

	inline void runtime::cancel_task(task_id id) {
		auto res = task_map.find(id);
		if (res == task_map.end()) return;
		cancel_task(res->second.get());
	}

	inline auto runtime::start_task(task_id id) -> ptr<co_task_base> {
		auto res = task_map.find(id);
		if (res == task_map.end()) return nullptr;

		_start_task_from_point(res->second.get());
		return res->second;
	}

	inline void runtime::stop_task(co_task_base* task) {
		if (!task) return;
		

		auto& state = task->task_state();
		if (state == task_state::suspend)
			suspend_list_.remove(task);
		state = task_state::stop;
		task->on_stop()();
		stop_queue_.emplace(task->task_id(), task);
	}

	inline void runtime::stop_task(task_id id) {
		auto res = task_map.find(id);
		if (res == task_map.end()) 
			return;

		stop_task(res->second.get());
	}

	inline void runtime::suspend_task(co_task_base* task) {
		if (!task || task->task_state() == task_state::stop || task->task_state() == task_state::suspend)
			return;

		task->task_state() = task_state::suspend;
		suspend_list_.push_back(task);
	}

	inline void runtime::suspend_task(task_id id) {
		auto res = task_map.find(id);
		if (res == task_map.end()) return;
		suspend_task(res->second.get());
	}

	inline void runtime::resume_task(co_task_base* task) {
			
		if (!task) return;
		suspend_list_.remove(task);
		if(task->task_state() == task_state::suspend) {
			_start_task_from_point(task);
		}
	}

	inline void runtime::resume_task(task_id id) {
		auto res = task_map.find(id);
		if (res == task_map.end()) return;
		resume_task(res->second.get());
	}

	inline void runtime::stop_all() {
		for (auto& [id, task] : task_map) {
			stop_task(task.get());
		}
	}

	inline void runtime::_update_run_task_queue() {
		auto& this_task_queue_ = _get_task_queue();
		(++task_queue_flag_) %= task_queue_num;

		while (!this_task_queue_.empty()) {
			if (const auto task = this_task_queue_.front()) {
				auto state = task->task_state();

				state == task_state::ready ? _resume_task(task) :
					state == task_state::suspend ? suspend_task(task):
					state == task_state::stop ? stop_task(task) :
					[]{}();
			}
			this_task_queue_.pop();
		}
	}

	inline void runtime::_update_suspend_task() {
		[[likely]]if (!enable_check_suspend_list) return;

		for (auto it = suspend_list_.begin(); it != suspend_list_.end(); ++it) {
			bool is_clear = false;
			task_state state;
			if (*it) {
				state = (*it)->task_state();
				auto id = (*it)->task_id();

				state == task_state::ready ? resume_task(*it), is_clear = true :
					state == task_state::suspend ? is_clear = false :
					state == task_state::stop ? stop_task(*it), is_clear = true
					: false;
			}
			else is_clear = true;

			if (is_clear)
				suspend_list_.erase(it);
		}
	}

	inline void runtime::_update_stop_task() {
		while (!stop_queue_.empty()) {
			const auto it = task_map.find(stop_queue_.front().index);
			if (it != task_map.end()) {
				task_map.erase(it);
			}
			stop_queue_.pop();
		}

	}

	inline void runtime::_update_timer_queue() {
		while (!timer_queue_.empty() && timer_queue_.top().index <= timer::now()) {
			const auto [id, task] = timer_queue_.top().value;
			timer_queue_.pop();
			if (task_map.contains(id)) {
				
				_start_task_from_point(task);
			}
		}
	}

	inline void runtime::_update_predicate() {
		for (auto [id, src] : predicate_map_) {
			auto task_id = src.index;
			auto& [predicate, task] = src.value;
			if (predicate()) {
				if(task_map.contains(task_id))
					_start_task_from_point(task);

				predicate_map_.erase(id);
			}
		}
	}

	template <class T>
	auto runtime::register_task(co_task<T>&& task) -> register_option {
		task.bind_runtime(this);
		const auto id = task.task_id();
		auto res = task_map.insert({ id, std::make_shared<co_task<T>>(std::move(task)) });
		return {
			.task_ref = res.first->second,
			.runtime_ref = this
		};

	}

	template <class T>
	auto runtime::start_task(co_task<T>&& task) -> co_task<T>& {
		
		co_task_base* task_ref;
		if (!task.has_runtime()) {
			task_ref = register_task(std::move(task)).task_ref.get();
		}
		else task_ref = &task;
			
		_start_task_from_point(task_ref);
		return *static_cast<co_task<T>*>(task_ref);

	}


	template <class T>
	inline void _builtin_call_runtime_start_task(runtime* rt, co_task<T>&& task) {
		rt->start_task(std::move(task));
	}

	inline void _builtin_call_runtime_stop_task(runtime* rt, co_task_base* task) {
		rt->stop_task(task);
	}
	inline void _builtin_call_runtime_suspend_task(runtime* rt, co_task_base* task) {
		rt->suspend_task(task);
	}
	inline void _builtin_call_runtime_resume_task(runtime* rt, co_task_base* task) {
		rt->resume_task(task);
	}
	inline void _builtin_call_runtime_cancel_task(runtime* rt, co_task_base* task) {
		rt->cancel_task(task);
	}


	inline  auto task_promise_base::get_task()const noexcept-> ptr<co_task_base> {
		if (!runtime_ref) return nullptr;

		auto it = runtime_ref->task_map.find(id);
		if (it != runtime_ref->task_map.end()) {
			return it->second;
		}
		return nullptr;
	}

	inline auto co_task_base::derived_task(standard_task auto&& task,derived_task_option option)->ptr<co_task_base> {
		auto promise = this->get_promise();
		auto& list =  promise->derived_task_list;
		
		auto rt = promise->runtime_ref;

		if (!rt) return nullptr;

		if(option.is_suspend_caller)[[likely]]
			rt->suspend_task(this);

		
		auto& task_ref = rt->start_task(std::move(task));
		auto task_ptr = task_ref.get_promise()->get_task();

		if(option.is_stop_task)[[likely]]
			list.push_back({ task_ptr->task_id(),task_ptr});

		if(option.is_resume_caller)[[likely]]
		task_ptr->on_done() += [rt,promise](auto&&...) {
			rt->resume_task(promise->get_task().get());
		};

		return task_ptr;
	}



}

