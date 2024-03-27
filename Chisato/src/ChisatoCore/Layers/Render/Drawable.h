#pragma once


#include"ChisatoCore/Layers/Layer.h"

#include"ChisatoCore/Rendering/Renderer.h"
#include"ChisatoCore/Rendering/vertex_array.h"
#include "ChisatoCore/Async/awaiter.h"
#include "ChisatoCore/Rendering/render_command.h"
#include "ChisatoCore/Rendering/shader.h"
#include"ChisatoCore/Rendering/orthographic_camera.h"

namespace cst {
	struct CSTAPI drawable {
		virtual async::co_task<> draw() = 0;

		virtual ~drawable() = default;
	};

	struct CSTAPI triangle : drawable {

		
		ptr<vertex_shader> p_v_shader = vertex_shader::create( R"(
			#version 330 core
			layout(location = 0) in vec3 aPos;
			layout(location = 1) in vec4 aColor;
			
			uniform mat4 uVpMat;
			out vec4 vColor;

			void main(){
			
				vColor = aColor;
				gl_Position = uVpMat * vec4(aPos.x,aPos.y,aPos.z,1.0);
			}
		)" );

		ptr<fragment_shader> p_f_shader = fragment_shader::create(R"(
			#version 330 core
			out vec4 FragColor;
			in vec4 vColor;
			uniform mat4 uVpMat;
			
			void main(){
				FragColor = vColor;
			}
		)" );
		ptr<shader> shaders = shader::create(p_v_shader,p_f_shader);

		ptr<vertex_array> vao;
		ptr<vertex_buffer> vbo;
		ptr<index_buffer> ibo;

		std::array <float,3*7> vertices = {
			-0.5f,-0.5f,0.0f,  0.3f,0.0f,1.0f,1.0f,
			0.0f,0.5f,0.0f,    0.0f,0.6f,0.7f,1.0f,
			0.5f,-0.5f,0.0f,   0.9f,0.0f,0.0f,1.0f,
		};

		std::array<uint, 3> indices = { 0,1,2, };

		auto draw()-> async::co_task<> override{
			co_await input::mouse::on_scroll;

			debug::log<>::info("draw triangle");


			vao = vertex_array::create();

			vbo = vertex_buffer::create(vertices.data(),vertices.size());
			debug::log<>::info("vbo created");

			ibo = index_buffer::create(indices.data(),indices.size());
			debug::log<>::info("ibo created");


			buffer_layout layout = {
				{shader_type::Float<3>,"aPos"},
				{shader_type::Float<4>,"aColor"}

			};
			vbo->bind_layout(layout);

			vao->add_vertex_buffer(vbo);
			vao->set_index_buffer(ibo);
	


			//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

			// draw frame loop
			while(1) {
				co_await async::wait_next_frame{};
				renderer::submit(vao, shaders);
			}

		}

	};
}
