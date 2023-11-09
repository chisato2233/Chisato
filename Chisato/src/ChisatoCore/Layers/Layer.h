#pragma once
#include"layer_stack.h"

namespace cst {
	
	class CSTAPI layer {
		friend class layer_stack;
		std::string name_;
		layer_stack sub_layer_stack_;

		void static_attach() ;
		void static_detach() ;
		void static_update() ;
		void static_event(event& event);

	public:
		layer(std::string&& name = "Layer") :name_{ name } { }
		virtual ~layer() = default;


		virtual void on_attach() { }
		virtual void on_detach() { }
		virtual void on_update() { }
		virtual void on_event(event& event) { }

		auto get_name()const noexcept { return name_; }
		auto& sub_layers() noexcept { return sub_layer_stack_; }
	};
};