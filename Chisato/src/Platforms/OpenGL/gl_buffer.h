#pragma once
#include"ChisatoCore/Rendering/buffer.h"
#include <glad/glad.h>



namespace cst {

	struct CSTAPI gl_vertex_buffer : vertex_buffer{
		gl_vertex_buffer(const float* data ,size_t size) :vertex_buffer(size){
			glCreateBuffers(1,&id);
			glBindBuffer(GL_ARRAY_BUFFER, id);
			glBufferData(GL_ARRAY_BUFFER, size*sizeof (float),data, GL_STATIC_DRAW);
		}

		buffer& bind() override { glBindBuffer(GL_ARRAY_BUFFER, id);  return *this; }
		vertex_buffer& bind_layout(const buffer_layout& layout) override { buffer_layout_ = layout; return *this; }
		uint32_t id;
	};


	struct CSTAPI gl_index_buffer : index_buffer {
		gl_index_buffer(const uint32_t* data, size_t count):index_buffer(count) {
			glCreateBuffers(1, &id);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), data, GL_STATIC_DRAW);
		}

		buffer& bind() override {
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
			return *this;
		}

		uint32_t id;

	};
}