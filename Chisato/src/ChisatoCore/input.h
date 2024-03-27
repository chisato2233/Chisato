#pragma once

#include"ChisatoCore/Events/event_lib.h"
namespace cst {
	struct input_base {
		inline static delegate<void()> on_event;



		virtual ~input_base() = default;
		static input_base* create();

		virtual bool is_key_pressed(int)			= 0;
		virtual bool is_mouse_button_pressed(int)	= 0;

		virtual std::pair<float, float>	get_mouse_pos() = 0;
	};
	

	struct CSTAPI input {
		inline static delegate<void()> on_input;

		struct window {
			inline static delegate<void(window_close_event)> on_close;
			inline static delegate<void(window_resize_event)> on_resize;
		};

		struct mouse {
			inline static delegate<void(const mouse_down_event&)> on_down;
			inline static delegate<void(const mouse_up_event&)> on_up;
			inline static delegate<void(const mouse_hold_event&)> on_hold;
			inline static delegate<void(const mouse_move_event&)> on_move;
			inline static delegate<void(const mouse_scroll_event&)> on_scroll;

		};

		struct keyboard {
			inline static delegate<void(const key_down_event&)> on_down;
			inline static delegate<void(const key_up_event&)> on_up;
			inline static delegate<void(const key_char_event&)> on_char;
			inline static delegate<void(const key_hold_event&)> on_hold;

		};
	};
	
}