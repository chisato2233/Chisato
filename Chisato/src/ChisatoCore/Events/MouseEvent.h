#pragma once
#include"Event.h"

//键盘事件系统。包括：
//	公用的KeyEvent，构造函数为保护类型，只能派生
//	按下事件
//	保持事件
//	抬起事件

namespace Chisato::Events {
	
	class CSTAPI MouseEvent :public Event {
	protected:
		std::pair<float, float> pos;

		MouseEvent(float x, float y, int _tag = Tag::None)
			:
			pos({ x,y }), 
			Event(_tag) { }

	public:
		inline float GetX() const noexcept { return pos.first; }
		inline float GetY() const noexcept { return pos.second; }
		inline std::pair<float, float> GetPos() const noexcept{return pos; }
	};


	class CSTAPI MouseDownEvent :public MouseEvent {
	protected:
		int button;

	public:
		MouseDownEvent(float x, float y, int _b)
			:
			MouseEvent(x, y, Tag::Input | Tag::Mouse | Tag::MouseButton),
			button(_b) { }

		virtual std::string GetName()const noexcept override;
	};

	class CSTAPI MouseMoveEvent :public MouseEvent {
	public:
		MouseMoveEvent(float x, float y)
			:
			MouseEvent(x, y, Tag::Input | Tag::Mouse) { }
		
		//virtual std::string GetName()const noexcept override;
	};

	class CSTAPI MouseHoldEvent :public MouseDownEvent {
	private:
		int repeatCount;
	public:
		MouseHoldEvent(float x, float y, int _b, int cnt)
			:MouseDownEvent(x, y, _b),
			repeatCount(cnt) { }

		virtual std::string GetName()const noexcept override;
		inline int GetCount() { return repeatCount; }

	};


	class CSTAPI MouseUpEvent :public MouseEvent {
	public:
		MouseUpEvent(float x,float y)
			:MouseEvent(x,y, Tag::Input | Tag::Mouse | Tag::MouseButton) { }

		virtual std::string GetName()const noexcept override;
	};
}