#pragma once
#include"ChisatoCore/Core.h"
#include"ChisatoCore//Events//Event.h"

namespace Chisato {
	using uint = unsigned int;
	
	struct WndProps {
		std::string title;
		std::pair<uint,uint> size;
		WndProps(const std::string& _title = "Chisato Engine", std::pair<uint, uint> _size = { 1280,720 }):
			title{_title},size{_size} { 
			
		}
	};

	class CSTAPI Window {
	public:
		using EventCallback = std::function<void(Event&)>;

		virtual ~Window(){ }

		virtual void OnUpdate() = 0;

		virtual uint GetW() const = 0;
		virtual uint GetH() const = 0;
		virtual std::string GetName() const = 0;

		virtual void SetEventCallback(const EventCallback& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync()const = 0;

		static Window* Creat(const WndProps& props = WndProps{});
	};

}