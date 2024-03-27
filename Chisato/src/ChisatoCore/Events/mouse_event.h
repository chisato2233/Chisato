#pragma once
#include"event.h"

namespace cst{
	
	class CSTAPI mouse_event :public event{
	protected:
		mouse_event(int t = Tag::Input | Tag::Mouse) : event(t) { }
	};



	class CSTAPI mouse_move_event :public mouse_event {
		std::pair<float, float> pos_;
	public:
		mouse_move_event(std::pair<float, float> _pos) : pos_{_pos}{ }

		float	get_x()		const noexcept	{ return pos_.first; }
		float	get_y()		const noexcept	{ return pos_.second; }
		auto	get_pos()	const noexcept	{ return pos_; }

		std::string get_name()const noexcept override;
	};



	class CSTAPI mouse_down_event :public mouse_event {
	protected:
		int button_;

	public:
		mouse_down_event(int _b):
			mouse_event(Tag::Input|Tag::Mouse|Tag::MouseButton),
			button_{ _b } { }
		
		int get_button() const noexcept{ return button_; }
		std::string get_name()const noexcept override;

	};



	class CSTAPI mouse_hold_event :public mouse_down_event {
		int repeat_count_;
	public:
		mouse_hold_event(int _b, int cnt) : mouse_down_event(_b), repeat_count_(cnt) { }

		int get_count() const noexcept { return repeat_count_; }
		std::string get_name()const noexcept override;
	};



	class CSTAPI mouse_up_event :public mouse_event {
		int button;
	public:
		mouse_up_event(int _b) : mouse_event(Tag::Input | Tag::Mouse | Tag::MouseButton),button{ _b } {}
		int get_button() const noexcept { return button; }
		std::string get_name()const noexcept override;
	};

	class CSTAPI mouse_scroll_event :public mouse_event {
		std::pair<float, float> offset_;
	public:
		explicit mouse_scroll_event(std::pair<float, float> o) :offset_{ o } { }
		
		std::string get_name()const noexcept override { 
			return std::format("[Event] Mouse Scroll ({}, {})", offset_.first, offset_.second); 
		}
		auto get_x	() const noexcept { return offset_.first; }
		auto get_y	() const noexcept { return offset_.second; }
		auto get_pos() const noexcept { return offset_; }
	};
}