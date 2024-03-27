#pragma once
#include "ChisatoCore/Rendering/shader.h"
#include <glad/glad.h>

#include "glm/gtc/type_ptr.inl"

namespace cst {
	struct CSTAPI gl_shader_source : virtual shader_source {
		gl_shader_source(std::string_view src) :shader_source(src){}
		~gl_shader_source()override = default;

		void compile() override {
			const auto src = source.c_str();
			glShaderSource(id, 1, &src, nullptr);
			glCompileShader(id);

			int success;
			glGetShaderiv(id, GL_COMPILE_STATUS, &success);
			if (!success) {
				char infoLog[512];
				glGetShaderInfoLog(id, 512, nullptr, infoLog);
				debug::log<>::error("vertex shader compile error\n{}", infoLog);

			}

		}

		uint32_t id = 0;;
	};


	struct CSTAPI gl_vertex_shader:vertex_shader,gl_shader_source{
		gl_vertex_shader(std::string_view _source):
			shader_source(_source), vertex_shader{_source}, gl_shader_source{_source} {
			id = glCreateShader(GL_VERTEX_SHADER);
		}
		
	};

	struct CSTAPI gl_fragment_shader : fragment_shader,gl_shader_source{
		gl_fragment_shader(std::string_view _source) :
			shader_source(_source), fragment_shader(_source), gl_shader_source{_source} {
			id = glCreateShader(GL_FRAGMENT_SHADER);
		}
	};

	struct CSTAPI gl_shader_program : shader_program {
		gl_shader_program() { id = glCreateProgram(); }

		~gl_shader_program()override {
			for (auto& i : shader_src)
				glDetachShader(id, dynamic_cast<gl_shader_source&>(*i).id);
			glDeleteProgram(id);
		}

		void compile()override {
			for (auto i : shader_src) {
				i->compile();
			}
		}

		void link() override {
			for (auto& i : shader_src) {
				glAttachShader(id, dynamic_cast<gl_shader_source&>(*i).id);
			}
			glLinkProgram(id);

			int success = 0;
			glGetProgramiv(id, GL_LINK_STATUS, &success);
			if (!success) {
				char infoLog[512];
				glGetProgramInfoLog(id, 512, nullptr, infoLog);
				debug::log<>::error("shader program link error:\n{}", infoLog);

			}
		}

		void use()const override { glUseProgram(id); }


		uint id = 0;
	};

	struct CSTAPI gl_shader : shader {
		gl_shader(const ptr<vertex_shader> &vertex_shader,const ptr<fragment_shader>& fragment_shader) :
			shader(std::make_unique<gl_shader_program>()) {
			
			add_shader(vertex_shader);
			add_shader(fragment_shader);

			auto& gl_program = dynamic_cast<gl_shader_program&>(*program);
			gl_program.compile();
			gl_program.link();
		}

		void bind() override {
			const auto& gl_program = dynamic_cast<gl_shader_program&>(*program);
			gl_program.use();
		}

		void set_uniform_matrix(const std::string_view name, const glm::mat4& mat) override {
			const auto& gl_program = dynamic_cast<gl_shader_program&>(*program);

			auto location = glGetUniformLocation(gl_program.id, name.data());
			glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(mat));
		}
	};
}
