#pragma once
#include"ChisatoCore/Macro.h"
#include"buffer.h"

namespace cst {
	struct CSTAPI vertex_array : no_copy {
		uint id;

		virtual ~vertex_array() = default;

		inline static ptr<vertex_array> create();
		virtual vertex_array& bind() = 0;
		virtual vertex_array& unbind() = 0;


		virtual void add_vertex_buffer(rptr<vertex_buffer> vertex_buffer) = 0;
		virtual void set_index_buffer(rptr<index_buffer> index_buffer) = 0;


		auto& get_vertex_buffers() const noexcept { return vertex_buffers_; }
		auto& get_index_buffer()const noexcept { return index_buffer_; }

	protected:
		std::vector<ptr<vertex_buffer>> vertex_buffers_;
		ptr<index_buffer> index_buffer_;
	};
}
