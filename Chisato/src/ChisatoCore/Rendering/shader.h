#pragma once
#include<glm/glm.hpp>

#include "ChisatoCore/Tools/FilePathes.h"

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


	struct CSTAPI shader {
		shader(uptr<shader_program>&& sp):program(std::move(sp)) {}

		virtual ~shader() = default;
		virtual void bind() = 0;
		virtual void set_uniform_matrix4(const std::string_view name, const glm::mat4& mat) = 0;
		virtual void set_uniform_matrix3(const std::string_view name, const glm::mat3& mat) =0;
		virtual void set_uniform_matrix2(const std::string_view name, const glm::mat2& mat) =0;
		virtual void set_uniform_float4(const std::string_view name, const glm::vec4& vec)=0;
		virtual void set_uniform_float3(const std::string_view name, const glm::vec3& vec) =0;
		virtual void set_uniform_float2(const std::string_view name, const glm::vec2& vec) =0;
		virtual void set_uniform_float(const std::string_view name, float f) =0;
		virtual void set_uniform_int(const std::string_view name, int i) =0;



		inline static ptr<shader> create(const ptr<vertex_shader>& v_shader,const ptr<fragment_shader>& f_shader);
		inline static ptr<shader> create(std::filesystem::path shader_file_path);
		void add_shader(const ptr<shader_source>& shader) const { program->shader_src.push_back(shader); }

		uptr<shader_program> program;
		
	};


	struct CSTAPI shader_info {
		virtual ptr<shader> load() = 0;
	};

	struct CSTAPI shader_file_path:shader_info {
		shader_file_path(std::filesystem::path path) :path(std::move(path)) {}
		ptr<shader> load() override {
			return shader::create(path);
		}
		std::filesystem::path path;
	};

	struct CSTAPI shader_src:shader_info {
		shader_src(std::string_view v_shader, std::string_view f_shader) :v_shader(v_shader), f_shader(f_shader) {}
		ptr<shader> load() override {
			return shader::create(vertex_shader::create(v_shader), fragment_shader::create(f_shader));
		}
		std::string_view v_shader;
		std::string_view f_shader;
	};


	struct CSTAPI shader_library {
		inline static ptr<shader_info> texture;
		inline static ptr<shader_info> flat_color;


		inline static void init() {
			std_shader_library = new shader_library();

			texture = std_shader_library->register_shader("cst::std::Texture", file_path::shader_path/"Texture.glsl");
			flat_color = std_shader_library->register_shader("cst::std::FlatColor", file_path::shader_path/"FlatColor.glsl");

		}

		ptr<shader_info> register_shader(std::string_view name, std::filesystem::path path) {
			return add_shader(name, shader_file_path(path));
		}

		ptr<shader_info> register_shader(std::string_view name, std::string_view v_shader, std::string_view f_shader) {
			return add_shader(name, shader_src{ v_shader, f_shader });
		}

		template<std::derived_from<shader_info> SI>
		ptr<shader_info> add_shader(std::string_view name, SI shader) {
			if (const auto it = shader_map.find(name.data()); it != shader_map.end()) {
				debug::log<>::error("shader with name {} already exists", name);
				return nullptr;
			}
			else return shader_map[name.data()] = std::make_shared<SI>(shader);
			
		}

		ptr<shader_info> get(std::string_view name) {
			if (const auto it = shader_map.find(name.data()); it != shader_map.end()) {
				return it->second;
			}
			else {
				debug::log<>::error("shader with name {} not found", name);
				return nullptr;
			}
		}

		std::unordered_map<std::string, ptr<shader_info>> shader_map;

	private:
		inline static shader_library* std_shader_library;
	};





}
