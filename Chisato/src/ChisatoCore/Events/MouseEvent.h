#pragma once
#include"Event.h"

//�����¼�ϵͳ��������
//	���õ�KeyEvent�����캯��Ϊ�������ͣ�ֻ������
//	�����¼�
//	�����¼�
//	̧���¼�

namespace Chisato{
	
	class CSTAPI MouseEvent :public Event {
	protected:
		std::pair<float, float> pos;

		//main constructor
		MouseEvent(std::pair<float, float> _pos, int _tag = Tag::None) :
			pos{_pos},Event(_tag) { }

	public:
		constexpr float GetX() { return pos.first; }
		constexpr float GetY() { return pos.second; }
		constexpr std::pair<float, float> GetPos() {return pos; }
	};


	class CSTAPI MouseDownEvent :public MouseEvent {
	protected:
		int button;

	public:
		
		MouseDownEvent(std::pair<float,float> _pos,int _b):
			MouseEvent(_pos,Tag::Input|Tag::Mouse|Tag::MouseButton),
			button{ _b } { }

		virtual std::string GetName()const noexcept override;
	};

	class CSTAPI MouseMoveEvent :public MouseEvent {
	public:

		MouseMoveEvent(std::pair<float,float> _pos) :
			MouseEvent(_pos, Tag::Input | Tag::Mouse) { }

		
		//virtual std::string GetName()const noexcept override;
	};

	class CSTAPI MouseHoldEvent :public MouseDownEvent {
	private:
		int repeatCount;
	public:
		MouseHoldEvent(std::pair<float,float> _pos, int _b, int cnt)
			:MouseDownEvent(_pos, _b),
			repeatCount(cnt) { }

		virtual std::string GetName()const noexcept override;
		inline int GetCount() { return repeatCount; }

	};


	class CSTAPI MouseUpEvent :public MouseEvent {
	public:
		MouseUpEvent(std::pair<float,float> _pos)
			:MouseEvent(_pos, Tag::Input | Tag::Mouse | Tag::MouseButton) { }

		virtual std::string GetName()const noexcept override;
	};
}