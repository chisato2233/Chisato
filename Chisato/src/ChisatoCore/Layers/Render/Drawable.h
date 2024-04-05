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
#include "ChisatoCore/UI/test.h"
#include "glm/gtc/type_ptr.hpp"

namespace cst {
	struct CSTAPI drawable {
		virtual async::co_task<> draw() = 0;

		virtual ~drawable() = default;
	};

	struct CSTAPI triangle : drawable {


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
		ptr<shader> shaders = shader::create(p_v_shader, p_f_shader);
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

		std::array<uint, 3> indices = { 0,1,2, };

		transform transform;

		void set_ui()const  {
			ImGui_layer::UI_drawer += [this] {
				cst::ui::window{
					.body = {
						ui::ui_element{
							.on_build = [this] {
								ImGui::ColorEdit4(
									"color",
									value_ptr(*dynamic_cast<glm::vec4*>(&material->ambient))
								);
							},
						}
					},
				}.build();
			};
		}
		auto draw() -> async::co_task<> override {
			material = std::make_shared<rendering::material>(shaders);

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


			set_ui();
			std::vector<cst::transform> transforms;
			for (int x = 0; x <= 100; x++) {
				for (int y = 0; y <= 200; y++) {
					std::random_device rd;
					std::default_random_engine eng(rd());
					std::uniform_real_distribution<float> distx(0.0f, x);
					std::uniform_real_distribution<float> disty(0.0f, y);
					

					ptr<triangle> tri = std::make_shared<triangle>();
					auto p = cst::transform{ .position = {{distx(eng), disty(eng), 0.0f} } };
					transforms.push_back(std::move(p));
				}
			}
			// draw frame loop
			while (1) {
				co_await async::wait_next_frame{};
				renderer::submit(vao, material,transform);
				//for(auto i : transforms)
				//	renderer::submit(vao, shaders, i);
			}

		}

	};
}
