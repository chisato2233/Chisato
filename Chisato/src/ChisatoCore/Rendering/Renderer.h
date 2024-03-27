#pragma once
#include "orthographic_camera.h"
#include"renderer_api.h"
#include "render_command.h"
#include "shader.h"
#include "ChisatoCore/Tools/property.h"


namespace cst {

	struct CSTAPI renderer {
		static void begin_scene(rptr<orthographic_camera> camera) {
			scene_data.view_projection_matrix = ptr<glm::mat4>(&camera->matrix.vp_matrix);
		}


		static void submit(rptr<vertex_array> va,rptr<shader> shader) {
			va->bind();
			shader->bind();
			shader->set_uniform_matrix("uVpMat", scene_data.get_vp_mat());
			render_command::draw_index(va);
		}


		struct scene_data {
			ptr<glm::mat4> view_projection_matrix;
			auto& get_vp_mat() { return *view_projection_matrix; }
		};


		inline static scene_data scene_data;

		inline static render_api default_render_api = render_api::OpenGL;
		inline static render_api current_render_api = default_render_api;
	};


}
