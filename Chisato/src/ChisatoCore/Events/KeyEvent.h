#pragma once
#include"Event.h"
#include<sstream>

//键盘事件系统。包括：
//	公用的KeyEvent，构造函数为保护类型，只能派生
//	按下事件
//	保持事件
//	抬起事件

namespace Chisato {
	namespace Events {
		class CSTAPI KeyEvent :public Event {
		protected:
			int keycode;
			KeyEvent(int _code,int _tag = Tag::None)
				:keycode(_code),Event(_tag) { }
		public:
			inline int GetKey() const noexcept { return keycode; }
		};

		class CSTAPI KeyDownEvent :public KeyEvent {
		public:
			KeyDownEvent(int _code)
				:KeyEvent(_code,Tag::Input | Tag::Keybord) { }
			virtual std::string GetName()const noexcept override;
		};		
		
		class CSTAPI KeyHoldEvent :public KeyDownEvent {
		private:
			int repeatCount;
		public:
			KeyHoldEvent(int _code,int cnt)
				:KeyDownEvent(_code),repeatCount(cnt) { }
			virtual std::string GetName()const noexcept override;
		};


		class CSTAPI KeyUpEvent :public KeyEvent {
		public:
			KeyUpEvent(int _code)
				:KeyEvent(_code,Tag::Input | Tag::Keybord) { }
			virtual std::string GetName()const noexcept override;
		};

	}
}