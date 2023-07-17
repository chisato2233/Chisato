#pragma once
#include"Event.h"


namespace Chisato {
	class CSTAPI WindowResizeEvent:public Event {
	private:
		std::pair<unsigned int, unsigned int> size;
	
	public:
		WindowResizeEvent(std::pair<unsigned int,unsigned int> _size = {}):
			Event(Tag::Window),
			size(_size) { }

		WindowResizeEvent(unsigned int w, unsigned int h) : WindowResizeEvent(std::pair{w, h}) { }

		constexpr unsigned int GetW() { return size.first; }
		constexpr unsigned int GetH() { return size.second; }

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