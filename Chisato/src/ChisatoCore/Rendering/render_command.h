#pragma once

#include"renderer_api.h"
#include"Platforms/OpenGL/gl_renderer_impl.h"


namespace cst {
	struct CSTAPI render_command {

		static void init() { renderer_impl_->init(); }
		static void clear() { renderer_impl_->clear(); }
		static void set_color(const glm::vec4& color) { renderer_impl_->set_color(color); }
		static void draw_index(rptr<vertex_array> va) { renderer_impl_->draw_index(va); }
		static void set_viewport_size(uint width, uint height) { renderer_impl_->set_viewport(0,0,width, height); };

	private:
		inline static uptr<renderer_impl> renderer_impl_{ new gl_renderer_impl() };
	};
}