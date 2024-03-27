#pragma once
#include"layer_stack.h"
#include"layer_async_runtine.h"
#include "Platforms/Windows/input_from_Windows.h"

namespace cst {
	
	class CSTAPI layer {
		friend class layer_stack;
		std::string name_;
		layer_stack sub_layer_stack_;
		layer_runtime async_runtime_;

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
		auto& async_runtime() noexcept { return async_runtime_.get(); }
	};
};