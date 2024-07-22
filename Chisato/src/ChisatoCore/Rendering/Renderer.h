#pragma once
#include "matearial.h"
#include "camera.h"
#include"renderer_api.h"
#include "render_command.h"
#include "shader.h"
#include "ChisatoCore/Tools/property.h"


namespace cst {

	struct CSTAPI renderer {
		
		static void init() {
			render_command::init();
			input::window::on_resize += [](window_resize_event e) {
				set_viewport_size(e.get_w(), e.get_h());
			};
		}

		static void begin_scene(rptr<rendering::viewport> camera) {
			scene_data.view_projection_matrix = ptr<glm::mat4>(&camera->matrix.vp_matrix);
		}
		 

		static void submit(rptr<vertex_array> va,rptr<rendering::material> material,glm::mat4 trans_matrix = glm::mat4{1}) {
			va->bind();
			material->bind();
			material->get_shader().set_uniform_matrix4("uVpMat", scene_data.get_vp_mat());
			
			material->get_shader().set_uniform_matrix4("uTransMat", trans_matrix);
			render_command::draw_index(va);
		}

		static void set_back_ground_color(const glm::vec4& color) {
			render_command::set_color(color);
		}

		static void set_viewport_size(uint width, uint height) {
			render_command::set_viewport_size(width, height);
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
