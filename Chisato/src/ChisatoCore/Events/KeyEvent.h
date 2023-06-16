#pragma once
#include"Event.h"

namespace Chisato {
	namespace Events {
		class CSTAPI KeyEvent :public Event {
		protected:
			int keycode;
		public:
			KeyEvent(int _code,int _tag = Tag::None)
				:keycode(_code),Event(_tag) { }
			
			int GetCode() const noexcept { return keycode; }
			virtual std::string GetName()const noexcept override { return "Key Event: " + keycode; }

		};

		class CSTAPI KeyDownEvent :public KeyEvent {

		public:
			KeyDownEvent(int _code)
				:KeyEvent(_code,Tag::Input | Tag::Keybord) { }

			virtual std::string GetName()const noexcept override { return "Key Down Event: " + keycode; }
		};

	}
}