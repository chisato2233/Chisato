#pragma once
#include"Event.h"

//键盘事件系统。包括：
//	公用的KeyEvent，构造函数为保护类型，只能派生
//	按下事件
//	保持事件
//	抬起事件

namespace Chisato{
	
	class CSTAPI MouseEvent :public Event {
	protected:
		MouseEvent(int _tag = Tag::Input | Tag::Mouse) : Event(_tag) { }
	};



	class CSTAPI MouseMoveEvent :public MouseEvent {
	private:
		std::pair<float, float> pos;
	public:
		MouseMoveEvent(std::pair<float, float> _pos) : pos{_pos},MouseEvent() { }

		float GetX()const noexcept { return pos.first; }
		float GetY() const noexcept { return pos.second; }
		auto GetPos() { return pos; }

		virtual std::string GetName()const noexcept override;
	};



	class CSTAPI MouseDownEvent :public MouseEvent {
	protected:
		int button;

	public:
		MouseDownEvent(int _b):
			MouseEvent(Tag::Input|Tag::Mouse|Tag::MouseButton),
			button{ _b } { }
		
		virtual std::string GetName()const noexcept override;
	};



	class CSTAPI MouseHoldEvent :public MouseDownEvent {
	private:
		int repeatCount;
	public:
		MouseHoldEvent(int _b, int cnt) : MouseDownEvent(_b), repeatCount(cnt) { }

		int GetCount() const noexcept { return repeatCount; }
		
		virtual std::string GetName()const noexcept override;
	};



	class CSTAPI MouseUpEvent :public MouseEvent {
		int button;
	public:
		MouseUpEvent(int _b):
			button{_b},
			MouseEvent(Tag::Input | Tag::Mouse | Tag::MouseButton) { }

		virtual std::string GetName()const noexcept override;
	};

	class CSTAPI MouseScrollEvent :public MouseEvent {
		std::pair<float, float> offset;
	public:
		MouseScrollEvent(std::pair<float, float> _offset) :offset{ _offset } { }
		virtual std::string GetName()const noexcept override { 
			return std::format("[Event] Mouse Scroll ({}, {})", offset.first, offset.second); 
		}
	};
}