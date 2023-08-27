#pragma once
#include"event.h"
#include<ChisatoCore/Tools/Log.h>

namespace cst {

		class CSTAPI key_event :public event {
		protected:
			int keycode_;
			key_event (int _code,int _tag = Tag::None) : event(_tag), keycode_(_code) { }
		public:
			int get_key() const noexcept { return keycode_; }
		};

		struct CSTAPI key_down_event : key_event {
			key_down_event(int _code) : key_event(_code, Tag::Input | Tag::Keybord) { }

			std::string get_name() const noexcept override { return std::format("[Event]: Key Down ({})", keycode_); }
		};		
		
		class CSTAPI key_hold_event :public key_down_event {
			int repeatCount_;
		public:
			key_hold_event(int _code,int cnt) :key_down_event(_code),repeatCount_(cnt) { }

			std::string get_name() const noexcept override { return std::format("[Event]: Key Hold ({},cnt:{})", keycode_, repeatCount_); }
		};

		struct CSTAPI key_char_event : event{
			key_char_event(unsigned int c):char_code_(c){ }

			auto		get_char() const noexcept		   { return char_code_; }
			std::string get_name() const noexcept override { return std::format("[Event]: Key Char ({})", static_cast<char>(char_code_)); }
		private:
			unsigned int char_code_;
		};

		struct CSTAPI key_up_event : key_event {
			key_up_event(int _code) : key_event(_code,Tag::Input | Tag::Keybord) { }
			std::string get_name()const noexcept override { return std::format("[Event]: Key Up ({})", keycode_); }
		};
}