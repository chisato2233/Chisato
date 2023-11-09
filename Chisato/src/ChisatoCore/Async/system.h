#pragma once
#include<ChisatoCore/Core.h>

#include"promise.h"

namespace cst {
	namespace async {
		struct CSTAPI next_frame;
		struct CSTAPI seconds;


		using Iasync = std::coroutine_handle<standard_promise>;

		struct CSTAPI task {
			using promise_type = standard_promise;
			
			task(Iasync h) :_handle{ h } {}
			auto& get_handle() { return _handle; }
		private:
			Iasync _handle;
		};

		struct CSTAPI system {

		public:
			static system& get() { CST_ASSERT(instance != nullptr, "async system not initialized"); return *instance; }
			static void init() { instance = new system(); }
			void update();

			void push_to_time(float time, Iasync& async_task);
			
			void push_to_stop(const Iasync& async_task) {async_task.promise().state=promise_state::Stop, stop_list.push_back(async_task.promise().get_id()); }

			auto start_task(Iasync async_task)->Iasync& {
				const auto info = async_task.promise().get_id();
				async_pool[info] = async_task;
				
				push_to_ready(info);
				return async_pool[info];
			}

			auto start_task(task&& task) ->Iasync&{ return start_task(task.get_handle()); }

			auto stop_task(const Iasync& async_task)->Iasync& {
				push_to_stop(async_task);
				return async_pool[async_task.promise().get_id()];
			}

			auto get_Iasync(int id) -> Iasync& { return async_pool[id]; }

		private:
			static system* instance;
			struct time_task {
				float time;
				int id;

				bool operator<(const time_task& other) const { return time < other.time; }
				time_task& operator=(const time_task& other) {
					time = other.time;
					id = other.id;
					return *this;
				}
			};

			std::queue<int> ready_queue{};
			std::priority_queue<time_task> time_queue{};

			std::list<int> suspend_list;
			std::list<int> stop_list;

			std::unordered_map<int,Iasync> async_pool{};

			void push_to_ready(int id) {
				get_Iasync(id).promise().state = promise_state::Ready;
				ready_queue.push(id);
			}

			void update_time();
			void update_stop();
			void update_ready();
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
