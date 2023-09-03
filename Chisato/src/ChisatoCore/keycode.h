#pragma once

namespace cst {

	namespace codes {
		//copy from glfw3.h

		//mouse button
		enum class e_mouse {
			_left,
			_right,
			_middle,
			_extension_1,
			_extension_2,
			_extension_3,
			_extension_4,
			_end,
		};
		struct CSTAPI mouse{
			std::string get_name() {
				switch(val) {
				case e_mouse::_left:						return	"left";
				case e_mouse::_right:						return	"right";
				case e_mouse::_middle:						return	"middle";
				case e_mouse::_extension_1:					return	"extension_1";
				case e_mouse::_extension_2:					return	"extension_2";	
				case e_mouse::_extension_3:					return	"extension_3";
				case e_mouse::_extension_4:					return	"extension_4";
				default:									return "unknown";
				}
			}
			e_mouse val;
		};

		//key code enum
		enum class e_key {
			_space = 32,
			_apostrophe = 39,
			_comma = 44,
			_minus = 45,
			_perio = 46,
			_slash = 47,
			_0 = 48,
			_1 = 49,
			_2 = 50,
			_3 = 51,
			_4 = 52,
			_5 = 53,
			_6 = 54,
			_7 = 55,
			_8 = 56,
			_9 = 57,
			_semicolon = 59,
			_equal = 61,
			_a = 65,
			_b = 66,
			_c = 67,
			_d = 68,
			_e = 69,
			_f = 70,
			_g = 71,
			_h = 72,
			_i = 73,
			_j = 74,
			_k = 75,
			_l = 76,
			_m = 77,
			_n = 78,
			_o = 79,
			_p = 80,
			_q = 81,
			_r = 82,
			_s = 83,
			_t = 84,
			_u = 85,
			_v = 86,
			_w = 87,
			_x = 88,
			_y = 89,
			_z = 90,
			_left_bracket = 91,
			_backslash = 92,
			_right_bracket = 93,
			_grave_accent = 96,
			_world_1 = 161,
			_world_2 = 162,

			_escape = 256,
			_enter = 257,
			_tab = 258,
			_backspace = 259,
			_insert = 260,
			_delete = 261,
			_right = 262,
			_left = 263,
			_down = 264,
			_up = 265,
			_page_up = 266,
			_page_down = 267,
			_home = 268,
			_end = 269,
			_caps_lock = 280,
			_scroll_lock = 281,
			_num_lock = 282,
			_print_screen = 283,
			_pause = 284,
			_f1 = 290,
			_f2 = 291,
			_f3 = 292,
			_f4 = 293,
			_f5 = 294,
			_f6 = 295,
			_f7 = 296,
			_f8 = 297,
			_f9 = 298,
			_f10 = 299,
			_f11 = 300,
			_f12 = 301,
			_f13 = 302,
			_f14 = 303,
			_f15 = 304,
			_f16 = 305,
			_f17 = 306,
			_f18 = 307,
			_f19 = 308,
			_f20 = 309,
			_f21 = 310,
			_f22 = 311,
			_f23 = 312,
			_f24 = 313,
			_f25 = 314,
			_kp_0 = 320,
			_kp_1 = 321,
			_kp_2 = 322,
			_kp_3 = 323,
			_kp_4 = 324,
			_kp_5 = 325,
			_kp_6 = 326,
			_kp_7 = 327,
			_kp_8 = 328,
			_kp_9 = 329,
			_kp_decimal = 330,
			_kp_divide = 331,
			_kp_multiply = 332,
			_kp_subtract = 333,
			_kp_add = 334,
			_kp_enter = 335,
			_kp_equal = 336,
			_left_shift = 340,
			_left_control = 341,
			_left_alt = 342,
			_left_super = 343,
			_right_shift = 344,
			_right_control = 345,
			_right_alt = 346,
			_right_super = 347,
			_menu = 348,
			_end
		};
		struct CSTAPI key{
			std::string get_name() {
				switch (val) {
				case e_key::_space:				return "space";
				case e_key::_apostrophe:		return "apostrophe";
				case e_key::_comma:				return "comma";
				case e_key::_minus:				return "minus";
				case e_key::_perio:				return "perio";
				case e_key::_slash:				return "slash";
				case e_key::_0:					return "0";
				case e_key::_1:					return "1";
				case e_key::_2:					return "2";
				case e_key::_3:					return "3";
				case e_key::_4:					return "4";
				case e_key::_5:					return "5";
				case e_key::_6:					return "6";
				case e_key::_7:					return "7";
				case e_key::_8:					return "8";
				case e_key::_9:					return "9";
				case e_key::_semicolon:			return "semicolon";
				case e_key::_equal:				return "equal";
				case e_key::_a:					return "a";
				case e_key::_b:					return "b";
				case e_key::_c:					return "c";
				case e_key::_d:					return "d";
				case e_key::_e:					return "e";
				case e_key::_f:					return "f";
				case e_key::_g:					return "g";
				case e_key::_h:					return "h";
				case e_key::_i:					return "i";
				case e_key::_j:					return "j";
				case e_key::_k:					return "k";
				case e_key::_l:					return "l";
				case e_key::_m:					return "m";
				case e_key::_n:					return "n";
				case e_key::_o:					return "o";
				case e_key::_p:					return "p";
				case e_key::_q:					return "q";
				case e_key::_r:					return "r";
				case e_key::_s:					return "s";
				case e_key::_t:					return "t";
				case e_key::_u:					return "u";
				case e_key::_v:					return "v";
				case e_key::_w:					return "w";
				case e_key::_x:					return "x";
				case e_key::_y:					return "y";
				case e_key::_z:					return "z";
				case e_key::_left_bracket:		return "left_bracket";
				case e_key::_backslash:			return "backslash";
				case e_key::_right_bracket:		return "right_bracket";
				case e_key::_grave_accent:		return "grave_accent";
				case e_key::_world_1:			return "world_1";
				case e_key::_world_2:			return "world_2";
				case e_key::_escape:			return "escape";
				case e_key::_enter:				return "enter";
				case e_key::_tab:				return "tab";
				case e_key::_backspace:			return "backspace";
				case e_key::_insert:			return "insert";
				case e_key::_delete:			return "delete";
				case e_key::_right:				return "right";
				case e_key::_left:				return "left";
				case e_key::_down:				return "down";
				case e_key::_up:				return "up";
				case e_key::_page_up:			return "page_up";
				case e_key::_page_down:			return "page_down";
				case e_key::_home:				return "home";
				case e_key::_end:				return "end";
				case e_key::_caps_lock:			return "caps_lock";
				case e_key::_scroll_lock:		return "scroll_lock";
				case e_key::_num_lock:			return "num_lock";
				case e_key::_print_screen:		return "print_screen";
				case e_key::_pause:				return "pause";
				case e_key::_f1:				return "f1";
				case e_key::_f2:				return "f2";
				case e_key::_f3:				return "f3";
				case e_key::_f4:				return "f4";
				case e_key::_f5:				return "f5";
				case e_key::_f6:				return "f6";
				case e_key::_f7:				return "f7";
				case e_key::_f8:				return "f8";
				case e_key::_f9:				return "f9";
				case e_key::_f10:				return "f10";
				case e_key::_f11:				return "f11";
				case e_key::_f12:				return "f12";
				case e_key::_f13:				return "f13";
				case e_key::_f14:				return "f14";
				case e_key::_f15:				return "f15";
				case e_key::_f16:				return "f16";
				case e_key::_f17:				return "f17";
				case e_key::_f18:				return "f18";
				case e_key::_f19:				return "f19";
				case e_key::_f20:				return "f20";
				case e_key::_f21:				return "f21";
				case e_key::_f22:				return "f22";
				case e_key::_f23:				return "f23";
				case e_key::_f24:				return "f24";
				case e_key::_f25:				return "f25";
				case e_key::_kp_0:				return "kp_0";
				case e_key::_kp_1:				return "kp_1";
				case e_key::_kp_2:				return "kp_2";
				case e_key::_kp_3:				return "kp_3";
				case e_key::_kp_4:				return "kp_4";
				case e_key::_kp_5:				return "kp_5";
				case e_key::_kp_6:				return "kp_6";
				case e_key::_kp_7:				return "kp_7";
				case e_key::_kp_8:				return "kp_8";
				case e_key::_kp_9:				return "kp_9";
				case e_key::_kp_decimal:		return "kp_decimal";
				case e_key::_kp_divide:			return "kp_divide";
				case e_key::_kp_multiply:		return "kp_multiply  ";
				case e_key::_kp_subtract:		return "kp_subtract  ";
				case e_key::_kp_add:			return "kp_add";
				case e_key::_kp_enter:			return "kp_enter";
				case e_key::_kp_equal:			return "kp_equal";
				case e_key::_left_shift:		return "left_shift";
				case e_key::_left_control:		return "left_control  ";
				case e_key::_left_alt:			return "left_alt";
				case e_key::_left_super:		return "left_super";
				case e_key::_right_shift:		return "right_shift  ";
				case e_key::_right_control:		return "right_control  ";
				case e_key::_right_alt:			return "right_alt";
				case e_key::_right_super:		return "right_super  ";
				case e_key::_menu:				return "menu";
				default:						return "unknown";
				}
			}
			e_key val;
		};

		template<class C> struct CSTAPI code;

		template<> struct CSTAPI code<key>:		key		{ code(int c):	key		{static_cast<e_key>		(c)} { }};
		template<> struct CSTAPI code<mouse>:	mouse	{ code(int c):	mouse	{static_cast<e_mouse>	(c)} { }};
	}
	using key_code		=codes::code<codes::key>;
	using mouse_code	=codes::code<codes::mouse>;
	
}