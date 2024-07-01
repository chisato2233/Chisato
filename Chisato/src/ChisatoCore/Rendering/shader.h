#pragma once
#include<glm/glm.hpp>
namespace cst {

	struct CSTAPI shader_source {
		shader_source(std::string_view source) :source(source) {
			
		}
		virtual ~shader_source() = default;

		virtual void compile() = 0;

		std::string source;
	};

	struct CSTAPI vertex_shader: virtual shader_source {
		vertex_shader(std::string_view source) :shader_source(source) {}

		static ptr<vertex_shader> create(std::string_view source);
		virtual ~vertex_shader() = default;
	};

	struct CSTAPI fragment_shader : virtual shader_source {
		fragment_shader(std::string_view source) :shader_source(source) {}

		static ptr<fragment_shader> create(std::string_view source);
		virtual ~fragment_shader() = default;
	};


	struct CSTAPI shader_program : no_copy {
		virtual ~shader_program() = default;

		virtual void link() = 0;
		virtual void compile() = 0;

		virtual void use()const = 0;
		std::vector<ptr<shader_source>> shader_src;
	};


	struct CSTAPI shader_set {
		shader_set(uptr<shader_program>&& sp):program(std::move(sp)) {}

		virtual ~shader_set() = default;
		virtual void bind() = 0;
		virtual void set_uniform_matrix4(const std::string_view name, const glm::mat4& mat) = 0;
		virtual void set_uniform_matrix3(const std::string_view name, const glm::mat3& mat) =0;
		virtual void set_uniform_matrix2(const std::string_view name, const glm::mat2& mat) =0;
		virtual void set_uniform_float4(const std::string_view name, const glm::vec4& vec)=0;
		virtual void set_uniform_float3(const std::string_view name, const glm::vec3& vec) =0;
		virtual void set_uniform_float2(const std::string_view name, const glm::vec2& vec) =0;
		virtual void set_uniform_float(const std::string_view name, float f) =0;
		virtual void set_uniform_int(const std::string_view name, int i) =0;







		inline static ptr<shader_set> create(const ptr<vertex_shader>& v_shader,const ptr<fragment_shader>& f_shader);

		void add_shader(const ptr<shader_source>& shader) const { program->shader_src.push_back(shader); }

		uptr<shader_program> program;
		
	};
}