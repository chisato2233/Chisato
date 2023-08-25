#pragma once
#include <pch.h>

namespace Chisato {
	using uint = unsigned int;
	
	struct WndProps {
		std::string title;
		std::pair<uint,uint> size;
		WndProps(std::string&& title = "Chisato Engine", std::pair<uint, uint> size = { 1280,720 }):
			title{title},size{size} { }
	};

	class CSTAPI Window {
	public:

		virtual ~Window(){ }

		virtual void OnUpdate() = 0;

		virtual uint GetW() const = 0;
		virtual uint GetH() const = 0;
		virtual std::string GetName() const = 0;

		virtual void SetEventCallback(const std::function<void(Event&)>& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync()const = 0;

		static Window* Create(const WndProps& props = WndProps{});
	};

}