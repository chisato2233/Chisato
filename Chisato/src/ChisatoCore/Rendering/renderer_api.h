#pragma once
#include<glm/glm.hpp>

namespace cst {
	enum class render_api {
		None, OpenGL
	};

	struct vertex_array;

	struct CSTAPI renderer_impl {
		virtual ~renderer_impl() = default;

		virtual void clear() = 0;
		virtual void set_color(glm::vec4) = 0;
		virtual void draw_index(rptr<vertex_array> va) = 0;
	};







}