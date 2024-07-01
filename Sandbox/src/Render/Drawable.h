#pragma once


#include <random>
 
#include"ChisatoCore/Layers/Layer.h"


#include"ChisatoCore/Rendering/Renderer.h"
#include"ChisatoCore/Rendering/vertex_array.h"
#include "ChisatoCore/Async/awaiter.h"
#include "ChisatoCore/Layers/ImGui/ImGui_layer.h"
#include "ChisatoCore/Rendering/render_command.h"
#include "ChisatoCore/Rendering/shader.h"
#include"ChisatoCore/Rendering/orthographic_camera.h"
#include "ChisatoCore/Rendering/Texture.h"
#include "ChisatoCore/UI/test.h"
#include "glm/gtc/type_ptr.hpp"
#include "Platforms/OpenGL/gl_shader.h"

namespace cst {
	struct  drawable {
		virtual async::co_task<> draw() = 0;
		virtual ~drawable() = default;
		async::runtime* runtime;
	};

	struct  triangle : drawable {
		uint ui_drawer_id = 0;

		ptr<vertex_shader> p_v_shader = vertex_shader::create(R"(
			#version 330 core
			layout(location = 0) in vec3 aPos;
			layout(location = 1) in vec4 aColor;
			
			uniform mat4 uVpMat;
			uniform mat4 uTransMat;
			out vec4 vColor;

			void main(){
			
				vColor = aColor;
				gl_Position = uVpMat * uTransMat * vec4(aPos.x,aPos.y,aPos.z,1.0);
			}
		)");

		ptr<fragment_shader> p_f_shader = fragment_shader::create(R"(
			#version 330 core
			out vec4 FragColor;
			in vec4 vColor;
			uniform mat4 uVpMat;
			uniform mat4 uTransMat;
			uniform vec4 uColor;
			void main(){
				FragColor = uColor;
			}
		)");
		ptr<shader_set> shaders = shader_set::create(p_v_shader, p_f_shader);

		//======================================================================


		ptr<vertex_shader> texture_v_shader = vertex_shader::create(R"(
			#version 330 core
			layout(location = 0) in vec3 aPos;
			layout(location = 1) in vec2 aTexCoord;
			
			out vec3 vPos;
			out vec2 vTexCoord;
			
			uniform mat4 uVpMat;
			uniform mat4 uTransMat;
			uniform vec4 uColor;
			uniform sampler2D uTexture;
			

			void main(){
				vTexCoord = aTexCoord;
				vPos = aPos;
				gl_Position = uVpMat * uTransMat * vec4(aPos.x,aPos.y,aPos.z,1.0);
			}
		)");

		ptr<fragment_shader> texture_f_shader = fragment_shader::create(R"(
			#version 330 core

			in vec2 vTexCoord;
			in vec3 vPos;

			layout(location = 0)out vec4 FragColor;
			
			
			uniform mat4 uVpMat;
			uniform mat4 uTransMat;
			uniform vec4 uColor;
			uniform sampler2D uTexture;

			void main(){
				FragColor = texture(uTexture,vTexCoord);
			}
		)");
		

		


		~triangle(){
			ImGui_layer::UI_drawer.remove(ui_drawer_id);
		}










		ptr<rendering::material> material ;

		rendering::color color = { 1.0f,1.0f,1.0f,1.0f };
		ptr<vertex_array> vao;
		ptr<vertex_buffer> vbo;
		ptr<index_buffer> ibo;

		std::array <float, 3 * 7> vertices = {
			-0.5f,-0.5f,0.0f,  0.3f,0.0f,1.0f,1.0f,
			0.0f,0.5f,0.0f,    0.0f,0.6f,0.7f,1.0f,
			0.5f,-0.5f,0.0f,   0.9f,0.0f,0.0f,1.0f,
		};


		std::array<float, 5 * 4> squre_vertex = {
			-0.5f,	-0.5f,	0.0f,	0.f,0.f,
			0.5f,	-0.5f,	0.0f,	1.f,0.f,
			-0.5f,	0.5f,	0.0f,	0.f,1.f,
			0.5f,	0.5f,	0.0f,	1.f,1.f,
		};


		std::array<uint, 3> indices = { 0,1,2, };
		std::array<uint, 6> squre_indices = { 0,1,2,1,3,2};

		transform transform;

		void set_ui(rptr<rendering::color> p_color)  {
			auto ui_drawer_id = ImGui_layer::UI_drawer.add( [this,p_color] {
				ui::window{
					.body = {
						ui::color_editor{
							.label = "Edit",
							.color = p_color
						}
					},
				}.build();
			});


		}

		auto draw() -> async::co_task<> override {
			runtime->start_task(random_position());
			runtime->start_task(draw_impl());
		}

		auto random_position()->async::co_task<> {
			while(1) {
				co_await async::wait_time{ 1.0f };
				transform.position.set(glm::vec3(random::range(-10.0, 10.0), random::range(-10.0, 10.0), 0.0f));
			}

		}

		auto draw_impl()->async::co_task<> {
			material = std::make_shared<rendering::material>(shaders);
			auto p_color = ptr<rendering::color>(&material->ambient);

			vao = vertex_array::create();
			vbo = vertex_buffer::create(vertices.data(), vertices.size());
			ibo = index_buffer::create(indices.data(), indices.size());


			buffer_layout layout = {
				{shader_type::Float<3>,"aPos"},
				{shader_type::Float<4>,"aColor"}
			};

			vbo->bind_layout(layout);
			vao->add_vertex_buffer(vbo);
			vao->set_index_buffer(ibo);



			//=======================
			ptr<vertex_array> squre_VA = vertex_array::create();

			ptr<vertex_buffer> squre_VB = vertex_buffer::create(squre_vertex.data(), squre_vertex.size());
			squre_VB->bind_layout({
				{shader_type::Float<3>,"aPos"},
				{shader_type::Float<2>,"aTexCoord" }
				});
			squre_VA->add_vertex_buffer(squre_VB);

			ptr<index_buffer> IB = index_buffer::create(squre_indices.data(), squre_indices.size());
			squre_VA->set_index_buffer(IB);


			set_ui(p_color);

			std::vector<cst::transform> transforms;
			transform.scale.set(glm::vec3(1.5f));

			ptr<rendering::texture_2D> texture = rendering::texture_2D::create("./Assest/test.png");
			ptr<shader_set> texture_shaders = shader_set::create(texture_v_shader, texture_f_shader);



			// draw frame loop

			while (1) {
				co_await async::wait_next_frame{};

				debug::log<>::info("test");
				texture_shaders->bind();
				texture_shaders->set_uniform_int("uTexture", 0);
				renderer::submit(
					squre_VA,
					std::make_shared<rendering::material>(texture_shaders, texture),
					transform
				);
			}

		}
	};
}
