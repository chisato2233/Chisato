#pragma once


#include <random>
 
#include"ChisatoCore/Layers/Layer.h"


#include"ChisatoCore/Rendering/Renderer.h"
#include"ChisatoCore/Rendering/vertex_array.h"
#include "ChisatoCore/Async/awaiter.h"
#include "ChisatoCore/Layers/ImGui/ImGui_layer.h"
#include "ChisatoCore/Rendering/render_command.h"
#include "ChisatoCore/Rendering/shader.h"
#include"ChisatoCore/Rendering/camera.h"
#include "ChisatoCore/Rendering/Texture.h"
#include "ChisatoCore/UI/test.h"
#include "glm/gtc/type_ptr.hpp"
#include "Platforms/OpenGL/gl_shader.h"

namespace cst {
	


	namespace graph {
		struct  drawable : virtual auto_remove_from_delegate {
			virtual async::co_task<> draw() = 0;
			virtual std::string shape_name() = 0;
			virtual ~drawable() = default;


			ptr<shader> shader;
			ptr<rendering::color> color = std::make_shared<rendering::color>(rendering::color_library::white);
			ptr<rendering::material> material;
			transform transform;


			async::runtime* runtime;
		};


		struct  triangle :drawable {

			ptr<vertex_array> vao;
			ptr<vertex_buffer> vbo;
			ptr<index_buffer> ibo;

			std::array <float, 3 * 5> vertices = {
				-0.5f,-0.5f,0.0f,  0.f,0.f,
				0.0f,0.5f,0.0f,    0.f,0.5f,
				0.5f,-0.5f,0.0f,   1.f,0.f,
			};					   
			std::array<uint, 3> indices = { 0,1,2, };

			//======================================================================

			triangle() {
				shader = shader_library::texture->load();
				material = std::make_shared<rendering::material>(shader, rendering::texture_2D::create(file_path::game_root_path / "Assest/test.png"),color);
			}


			std::string shape_name() override { return "Triangle"; }
			void set_ui(rptr<rendering::color> p_color) {
			}

			auto draw() -> async::co_task<>  override {
				
			
				vao = vertex_array::create();
				vbo = vertex_buffer::create(vertices.data(), vertices.size());
				ibo = index_buffer::create(indices.data(), indices.size());


				buffer_layout layout = {
					{shader_type::Float<3>,"aPos"},
					{shader_type::Float<2>,"aTexCoord"}
				};



				vbo->bind_layout(layout);
				
				vao->add_vertex_buffer(vbo);
				vao->set_index_buffer(ibo);


				//=======================

				
				transform.scale.set(glm::vec3(1.5f));
				// draw frame loop
				shader->bind();
				shader->set_uniform_int("uTexture", 0);
				
				while (1) {
					co_await async::wait_next_frame{};

					renderer::submit(
						vao,
						material,
						transform
					);
				}

			}
		};

		struct quad :drawable{


			ptr<rendering::texture_2D> texture;
			quad() {
				shader = shader_library::texture->load();
				texture = rendering::texture_2D::create(file_path::game_root_path/ "Assest/test.png");
				material = std::make_shared<rendering::material>(shader,texture, color);
			}

			std::string shape_name() override { return "Quad"; }

			auto draw()->async::co_task<> override {
				ptr<vertex_array> squre_VA = vertex_array::create();

				ptr<vertex_buffer> squre_VB = vertex_buffer::create(squre_vertex.data(), squre_vertex.size());
				squre_VB->bind_layout({
					{shader_type::Float<3>,"aPos"},
					{shader_type::Float<2>,"aTexCoord" }
				});
				squre_VA->add_vertex_buffer(squre_VB);

				ptr<index_buffer> IB = index_buffer::create(squre_indices.data(), squre_indices.size());
				squre_VA->set_index_buffer(IB);

				// draw frame loop

				while (1) {
					co_await async::wait_next_frame{};


					shader->bind();
					shader->set_uniform_int("uTexture", 0);
					renderer::submit(
						squre_VA,
						material,
						transform
					);
				}

			}
			std::array<float, 5 * 4> squre_vertex = {
				-0.5f,	-0.5f,	0.0f,	0.f,0.f,
				0.5f,	-0.5f,	0.0f,	1.f,0.f,
				-0.5f,	0.5f,	0.0f,	0.f,1.f,
				0.5f,	0.5f,	0.0f,	1.f,1.f,
			};
			std::array<uint, 6> squre_indices = { 0,1,2,1,3,2 };

			
		};
	}

	
}
