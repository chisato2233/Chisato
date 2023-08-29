#pragma once
#include<pch.h>
namespace cst {
	struct input_base {
		virtual ~input_base() = default;
		static input_base* create();

		virtual bool is_key_pressed(int)			= 0;
		virtual bool is_mouse_button_pressed(int)	= 0;

		virtual std::pair<float, float>	get_mouse_pos() = 0;
	};
}