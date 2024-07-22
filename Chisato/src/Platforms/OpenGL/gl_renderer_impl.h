#pragma once
#include "ChisatoCore/Rendering/renderer_api.h"
#include"gl_buffer.h"
#include"gl_vertex_array.h"
#include "glad/glad.h"

namespace cst {


	struct CSTAPI gl_renderer_impl:renderer_impl {
		void init() override {
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		}
		void clear() override {
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}

		void set_color(glm::vec4 color) override {
			glClearColor(color.r, color.g, color.b, color.a);
		}

		void draw_index(rptr<vertex_array> va)override {
			auto& gva = dynamic_cast<gl_vertex_array&>(*va);
			glDrawElements(GL_TRIANGLES, gva.get_index_buffer()->count, GL_UNSIGNED_INT,nullptr);
		}

		void set_viewport(uint x, uint y, uint width, uint height) override {
			glViewport(x, y, width, height);
		}
	};
}
