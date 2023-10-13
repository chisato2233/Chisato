#pragma once
#include<ChisatoCore/Core.h>

#include<coroutine>

namespace cst {
	namespace async {
		struct CSTAPI next_frame;
		struct CSTAPI seconds;
	

		struct CSTAPI standard_promise {
			auto get_return_object() { return std::coroutine_handle<standard_promise>::from_promise(*this); }
			using async_handle = std::coroutine_handle<standard_promise>;
			auto initial_suspend() noexcept { return std::suspend_always{}; }
			auto final_suspend() noexcept { return std::suspend_never{}; }
			void return_void() {}
			void unhandled_exception() { std::terminate(); }
		private:
		};
		
		using Iasync = standard_promise;

		struct CSTAPI task {
			using promise_type = standard_promise;
			using async_handle = std::coroutine_handle<promise_type>;
			task(async_handle h) :_handle{h} {}
			auto& get_handle() { return _handle; }
		private:
			async_handle _handle;
		};



		struct CSTAPI system {

		public:
			static system& get() { CST_ASSERT(instance != nullptr, "async system not initialized"); return *instance; }
			static void init() { instance = new system(); }

			void push_to_time(float time, Iasync& async_task);
			void push_to_update(Iasync& async_task) { update_queue.push(async_task); }
			void start_task(task async_task){
				push_to_ready(async_task.get_handle().promise());
			}


			void update();

		private:
			static system* instance;
			struct time_task {
				float time;
				Iasync& async_task;

				bool operator<(const time_task& other) const { return time < other.time; }
				time_task& operator=(const time_task& other){
					time = other.time;
					async_task = other.async_task;
					return *this;
				}
			};

			std::queue<std::reference_wrapper<Iasync>> ready_queue{};
			std::queue<std::reference_wrapper<Iasync>> update_queue{};
			std::priority_queue<time_task> time_queue{};
			
			void push_to_ready(Iasync& async_task) { ready_queue.push(async_task); }
			
		};

		struct CSTAPI seconds {
			float time;
			seconds(float t) :time{ t } {}
			constexpr bool await_ready() const noexcept { return false; }
			void await_suspend(std::coroutine_handle<standard_promise>) const noexcept;
			constexpr void await_resume() const noexcept {}
		};
		
		struct CSTAPI next_frame {
			constexpr bool await_ready() const noexcept { return false; }
			void await_suspend(std::coroutine_handle<standard_promise>) const noexcept;
			constexpr void await_resume() const noexcept {}
		};




	}
}
