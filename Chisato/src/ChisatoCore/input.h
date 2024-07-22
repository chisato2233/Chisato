#pragma once

#include"ChisatoCore/Events/event_lib.h"
namespace cst {
	struct input_base {
		inline static delegate<void()> on_event;



		virtual ~input_base() = default;
		static input_base* create();

		virtual bool is_pressed(codes::e_key)			= 0;
		virtual bool is_pressed(codes::e_mouse)			= 0;

		virtual std::pair<float, float>	get_mouse_pos() = 0;
		virtual std::pair<float, float> get_mouse_pos_delta() = 0;
	};
	

	struct  CSTAPI input {
		inline static delegate<void()> on_input;

		struct CSTAPI window {
			inline static delegate<void(window_close_event)> on_close;
			inline static delegate<void(window_resize_event)> on_resize;
		};

		struct CSTAPI mouse {
			inline static delegate<void(mouse_down_event)> on_left_down;
			inline static delegate<void(mouse_down_event)> on_right_down;
			inline static delegate<void(mouse_down_event)> on_middle_down;

			inline static delegate<void(mouse_up_event)> on_left_up;
			inline static delegate<void(mouse_up_event)> on_right_up;
			inline static delegate<void(mouse_up_event)> on_middle_up;

			inline static delegate<void(mouse_hold_event)> on_left_hold;
			inline static delegate<void(mouse_hold_event)> on_right_hold;
			inline static delegate<void(mouse_hold_event)> on_middle_hold;

			inline static delegate<void(mouse_move_event)> on_move;
			inline static delegate<void(mouse_scroll_event)> on_scroll;

		};

		struct CSTAPI keyboard {
			inline static delegate<void(key_down_event)> on_down;
			inline static delegate<void(key_up_event)> on_up;
			inline static delegate<void(key_char_event)> on_char;
			inline static delegate<void(key_hold_event)> on_hold;

		};
	};
	
}