//#pragma once
//#include"Delegate.h"
//
//namespace cst{
//	struct state_base {
//		virtual void on_enter() = 0;
//		virtual void on_exit() = 0;
//		virtual void on_update() = 0;
//	};
//
//	//template<typename T,typename... Args>
//	//inline constexpr auto find_index()->opt<int> {
//	//	if constexpr (sizeof...(Args) == 0) return std::nullopt;
//
//	//	auto f = []<typename _, typename... TArgs>() {
//	//		return std::is_same_v<T, _> ? 0 : 1 + find_index<T, TArgs...>();
//	//	};
//	//	
//	//}
//
//	template<class E,std::derived_from<state_base>... States>
//	struct state_machine {
//
//		template<std::derived_from<state_base> Init_State>
//		constexpr void init() { current_state_.template emplace<Init_State>(); }
//
//		
//
//		template<std::derived_from<state_base>... To_States>
//		constexpr void change_to() {
//			auto index = current_state_.index();
//			std::visit([](auto& state) {
//				state.on_exit();
//			}, current_state_);
//
//			current_state_.template emplace<To_States>();
//
//			std::visit([](auto& state) {
//				state.on_enter();
//			}, current_state_);
//			
//
//		}
//
//		void update() {
//			std::visit([](auto& state) {
//				state.on_update();
//			}, current_state_);
//		}
//
//		auto index() -> E{ return static_cast<E>(current_state_.index()); }
//	private:
//		std::variant<std::monostate, States...> current_state_;
//	};
//
//	struct state_1:state_base {
//		void on_enter() override {
//			std::cout << "enter state_1" << std::endl;
//		}
//		void on_exit() override {
//			std::cout << "exit state_1" << std::endl;
//		}
//		void on_update() override {
//			std::cout << "update state_1" << std::endl;
//		}
//	};
//
//	struct state_2 :state_base {
//		void on_enter() override {
//			std::cout << "enter state_2" << std::endl;
//		}
//		void on_exit() override {
//			std::cout << "exit state_2" << std::endl;
//		}
//		void on_update() override {
//			std::cout << "update state_2" << std::endl;
//		}
//	};
//
//	struct state_3:state_base {
//		void on_enter() override {
//			std::cout << "enter state_3" << std::endl;
//		}
//		void on_exit() override {
//			std::cout << "exit state_3" << std::endl;
//		}
//		void on_update() override {
//			std::cout << "update state_3" << std::endl;
//		}
//	};
//
//	enum class state_enum {
//		mono,s1, s2, s3
//	};
//
//	inline state_machine<state_enum,state_1, state_2, state_3> sm;
//
//	void test() {
//		sm.change_to<state_1>();
//		auto i=sm.index();
//		if(i==state_enum::s1) std::cout << "state_1" << std::endl;
//
//	}
//
//
//}