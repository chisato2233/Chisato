#pragma once
#include "ChisatoCore/Rendering/shader.h"
#include <glad/glad.h>

#include "glm/gtc/type_ptr.hpp"

namespace cst {
	struct CSTAPI gl_shader_source : virtual shader_source {
		gl_shader_source(std::string_view src) :shader_source(src){}
		~gl_shader_source()override {
			glDeleteShader(id);
		}

		void compile() override;
		uint32_t id = 0;
	};


	struct CSTAPI gl_vertex_shader:vertex_shader,gl_shader_source{
		gl_vertex_shader(std::string_view _source);
	};

	struct CSTAPI gl_fragment_shader : fragment_shader,gl_shader_source{
		gl_fragment_shader(std::string_view _source);
	};

	struct CSTAPI gl_shader_program : shader_program {
		gl_shader_program() { id = glCreateProgram(); }
		~gl_shader_program()override;

		void compile()override;
		void link() override;
		void use()const override { glUseProgram(id); }


		uint id = 0;
	};

	struct CSTAPI gl_shader : shader_set {
		gl_shader(const ptr<vertex_shader> &vertex_shader,const ptr<fragment_shader>& fragment_shader);

		void bind() override;

		void set_uniform_matrix4(const std::string_view name, const glm::mat4& mat) override;
		void set_uniform_matrix3(const std::string_view name, const glm::mat3& mat) override;
		void set_uniform_matrix2(const std::string_view name, const glm::mat2& mat) override;


		void set_uniform_float4(const std::string_view name, const glm::vec4& vec)override;
		void set_uniform_float3(const std::string_view name, const glm::vec3& vec) override;
		void set_uniform_float2(const std::string_view name, const glm::vec2& vec) override;
		void set_uniform_float(const std::string_view name, float f) override;

		void set_uniform_int(const std::string_view name, int i) override;
	};
}
