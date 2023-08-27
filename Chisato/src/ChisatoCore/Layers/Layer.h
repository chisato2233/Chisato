#pragma once

namespace cst {
	class CSTAPI layer {
		std::string name_;
	public:
		layer(std::string&& name = "Layer") :name_{ name } { }
		virtual ~layer() = default;

		virtual void on_attach() { }
		virtual void on_detach() { }
		virtual void on_update() { }
		virtual void on_event(event& event) { }

		auto get_name()const noexcept { return name_; }
	};
};