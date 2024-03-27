#pragma once
#include"ChisatoCore/Rendering/vertex_array.h"
namespace cst {

	struct CSTAPI gl_vertex_array : vertex_array {
		gl_vertex_array() { glCreateVertexArrays(1, &id); }
		~gl_vertex_array() {
			glDeleteVertexArrays(1, &id);
		}

		vertex_array& bind() override {
			glBindVertexArray(id);
			return *this;
		}
		vertex_array& unbind() override {
			glBindVertexArray(0);
			return *this;
		}

		void add_vertex_buffer(rptr<vertex_buffer> vertex_buffer) override {
			glBindVertexArray(id);
			vertex_buffer->bind();

			uint32_t index = 0;
			for (auto& elements : vertex_buffer->get_layout()) {
				glEnableVertexAttribArray(index);
				glVertexAttribPointer(
					index,
					elements.count,
					elements.gl_type,
					elements.normalized ? GL_TRUE : GL_FALSE,
					vertex_buffer->get_layout().stride,
					reinterpret_cast<const void*>(elements.offset)
				);
				index++;
			}
			vertex_buffers_.push_back(vertex_buffer);
		}

		void set_index_buffer(rptr<index_buffer> index_buffer) override {
			glBindVertexArray(id);
			index_buffer->bind();

			index_buffer_ = index_buffer;
		}


		uint32_t id = -1;
	};
}