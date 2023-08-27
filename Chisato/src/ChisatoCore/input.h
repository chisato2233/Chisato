#pragma once

namespace cst {
	struct input {

		template<class T>requires std::is_base_of_v<T, input>
		static void init() {
			p_input_ = new T{};
		}

		static auto& get() {
			CST_ASSERT(p_input_, "do not create input yet");
			return *p_input_;
		}
		bool is_key_pressed(int key) { return is_key_pressed_impl(key); }


	protected:
		virtual bool is_key_pressed_impl(int key) = 0;
	private:
		static input* p_input_;
	};
}