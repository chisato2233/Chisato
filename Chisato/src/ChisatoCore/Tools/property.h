#pragma once
#include"Delegate.h"
namespace cst {

	template<class T>
	struct property {
		//property() = default;

		T get() { return getter(); }
		void set(const T& new_val) {
			setter(new_val);
			on_change();
		}

		explicit operator T() { return get(); }

		T& get_ref() { return value; }

		//this will call the on change delegate
		T& operator()() { on_change(); return get_ref(); }



		const T* operator->() { return &get_ref(); }
		const T& operator*() { return get_ref(); }




		property& operator=(const T& new_val) {
			set(new_val);
			return *this;
		}

		template<class T2> requires requires { std::declval<T>() + std::declval<T2>(); }
		auto operator+=(const T2& new_val) {
			set(get() + new_val);
			return *this;
		}

		template<class T2> requires requires { std::declval<T>() - std::declval<T2>(); }
		auto operator-=(const T2& new_val) {
			set(get() - new_val);
			return *this;
		}
		template<class T2> requires requires { std::declval<T>() * std::declval<T2>(); }
		auto operator*=(const T2& new_val) {
			set(get() * new_val);
			return *this;
		}
		template<class T2> requires requires { std::declval<T>() / std::declval<T2>(); }
		auto operator/=(const T2& new_val) {
			set(get() / new_val);
			return *this;
		}
		template<class T2> requires requires { std::declval<T>() & std::declval<T2>(); }
		auto operator&=(const T2& new_val) {
			set(get() & new_val);
			return *this;
		}
		template<class T2> requires requires { std::declval<T>() | std::declval<T2>(); }
		auto operator|=(const T2& new_val) {
			set(get() | new_val);
			return *this;
		}
		template<class T2> requires requires { std::declval<T>() << std::declval<T2>(); }
		auto operator<<=(const T2& new_val) {
			set(get() << new_val);
			return *this;
		}
		template<class T2> requires requires { std::declval<T>() >> std::declval<T2>(); }
		auto operator>>=(const T2& new_val) {
			set(get() >> new_val);
			return *this;
		}


		T value;
		std::function<T()> getter{ [this] {return get_ref(); } };
		std::function<void(const T&)> setter{ [this](const T& new_val) {return get_ref() = new_val; }};
		delegate_ptr<property, void()> on_change{ this };
		
	};

	template<class T> property(T) -> property<T>;


}