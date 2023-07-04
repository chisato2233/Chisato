#pragma once
#include"Event.h"


namespace Chisato::Events {
	class CSTAPI WindowResizeEvent:public Event {
	private:
		unsigned int width, hight;
	
	public:
		WindowResizeEvent(unsigned int w, unsigned int h) 
			:
			Event(Tag::Window),
			width{ w }, hight{ h } { }
		WindowResizeEvent():WindowResizeEvent(0,0){ }

		constexpr unsigned int GetW() { return width; }
		constexpr unsigned int GetH() { return hight; }

		virtual std::string GetName()const noexcept override;
	};

	class CSTAPI WindowCloseEvent:public Event {
	public:
		WindowCloseEvent():Event(Tag::Window){ }
		virtual std::string GetName()const noexcept override;
	};

	class CSTAPI AppTickEvent :public Event {
	public:
		AppTickEvent() :Event(Tag::App) { }
		virtual std::string GetName()const noexcept override;
	};	
	
	class CSTAPI AppUpdateEvent :public Event {
	public:
		AppUpdateEvent() :Event(Tag::App) { }
		virtual std::string GetName()const noexcept override;
	};	
	
	class CSTAPI AppRenderEvent :public Event {
	public:
		AppRenderEvent() :Event(Tag::App) { }
		virtual std::string GetName()const noexcept override;
	};
}