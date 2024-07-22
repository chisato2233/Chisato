#pragma once
#include"gl_shader.h"
namespace cst {
	void gl_shader_source::compile() {
		const auto src = source.c_str();
		glShaderSource(id, 1, &src, nullptr);
		glCompileShader(id);

		int success;
		glGetShaderiv(id, GL_COMPILE_STATUS, &success);
		if (!success) {
			char infoLog[512];
			glGetShaderInfoLog(id, 512, nullptr, infoLog);
			debug::log<>::error("vertex shader_set compile error\n{}", infoLog);

		}

	}

	gl_vertex_shader::gl_vertex_shader(std::string_view _source):
		shader_source(_source), vertex_shader{_source}, gl_shader_source{_source} {
		id = glCreateShader(GL_VERTEX_SHADER);
	}

	gl_fragment_shader::gl_fragment_shader(std::string_view _source):
		shader_source(_source), fragment_shader(_source), gl_shader_source{_source} {
		id = glCreateShader(GL_FRAGMENT_SHADER);
	}

	gl_shader_program::~gl_shader_program() {
		for (auto& i : shader_src)
			glDetachShader(id, dynamic_cast<gl_shader_source&>(*i).id);
		glDeleteProgram(id);
	}

	void gl_shader_program::compile() {
		for (auto i : shader_src) {
			i->compile();
		}
	}

	void gl_shader_program::link() {
		for (auto& i : shader_src) {
			glAttachShader(id, dynamic_cast<gl_shader_source&>(*i).id);
		}
		glLinkProgram(id);

		int success = 0;
		glGetProgramiv(id, GL_LINK_STATUS, &success);
		if (!success) {
			char infoLog[512];
			glGetProgramInfoLog(id, 512, nullptr, infoLog);
			debug::log<>::error("shader_set program link error:\n{}", infoLog);

		}
	}

	gl_shader::gl_shader(std::filesystem::path path) :shader(std::make_unique<gl_shader_program>()) {
		auto in = std::ifstream{ path,std::ios::in,std::ios::binary };
		if(in) {
			std::string source;
			in.seekg(0, std::ios::end);
			source.resize(in.tellg());
			in.seekg(0, std::ios::beg);
			in.read(source.data(), source.size());
			in.close();

			auto type_token = "#type";
			auto pos = source.find(type_token, 0);
			while (pos != std::string::npos) {
				const auto eol = source.find_first_of("\r\n", pos);
				auto type = source.substr(pos + strlen(type_token), eol - pos - strlen(type_token));

				auto start = type.begin();
				while (start != type.end() && std::isspace(*start)) {
					++start;
				}

				auto end = type.end();
				do {
					--end;
				} while (std::distance(start, end) > 0 && std::isspace(*end));

				type = std::string(start, end + 1);

				auto next_pos = source.find(type_token, eol);
				auto shader_src = source.substr(eol + 1, next_pos- eol - 1);
				if (type ==  "vertex") {
					add_shader(std::make_shared<gl_vertex_shader>(shader_src));
				}
				else if (type == "fragment" || type == "pixel") {
					add_shader(std::make_shared<gl_fragment_shader>(shader_src));
				}
				else debug::log<>::error("Invalid shader type: {}", type);
				pos = next_pos;
			}

			auto& gl_program = dynamic_cast<gl_shader_program&>(*program);
			gl_program.compile();
			gl_program.link();
		}
		else debug::log<>::error("Failed to open file: {}", path.string());
	}

	gl_shader::gl_shader(const ptr<vertex_shader>& vertex_shader, const ptr<fragment_shader>& fragment_shader):
		shader(std::make_unique<gl_shader_program>()) {
			
		add_shader(vertex_shader);
		add_shader(fragment_shader);

		auto& gl_program = dynamic_cast<gl_shader_program&>(*program);
		gl_program.compile();
		gl_program.link();
	}

	void gl_shader::bind() {
		const auto& gl_program = dynamic_cast<gl_shader_program&>(*program);
		gl_program.use();
	}

	void gl_shader::set_uniform_matrix4(const std::string_view name, const glm::mat4& mat) {
		const auto& gl_program = dynamic_cast<gl_shader_program&>(*program);

		auto location = glGetUniformLocation(gl_program.id, name.data());
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(mat));
	}

	void gl_shader::set_uniform_matrix3(const std::string_view name, const glm::mat3& mat) {
		const auto& gl_program = dynamic_cast<gl_shader_program&>(*program);

		auto location = glGetUniformLocation(gl_program.id, name.data());
		glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(mat));
	}

	void gl_shader::set_uniform_matrix2(const std::string_view name, const glm::mat2& mat) {
		const auto& gl_program = dynamic_cast<gl_shader_program&>(*program);

		auto location = glGetUniformLocation(gl_program.id, name.data());
		glUniformMatrix2fv(location, 1, GL_FALSE, glm::value_ptr(mat));
	}

	void gl_shader::set_uniform_float4(const std::string_view name, const glm::vec4& vec) {
		const auto& gl_program = dynamic_cast<gl_shader_program&>(*program);

		auto location = glGetUniformLocation(gl_program.id, name.data());
		glUniform4f(location, vec.x, vec.y, vec.z, vec.w);
	}

	void gl_shader::set_uniform_float3(const std::string_view name, const glm::vec3& vec) {
		const auto& gl_program = dynamic_cast<gl_shader_program&>(*program);

		auto location = glGetUniformLocation(gl_program.id, name.data());
		glUniform3f(location, vec.x, vec.y, vec.z);
	}

	void gl_shader::set_uniform_float2(const std::string_view name, const glm::vec2& vec) {
		const auto& gl_program = dynamic_cast<gl_shader_program&>(*program);

		auto location = glGetUniformLocation(gl_program.id, name.data());
		glUniform2f(location, vec.x, vec.y);
	}

	void gl_shader::set_uniform_float(const std::string_view name, float f) {
		const auto& gl_program = dynamic_cast<gl_shader_program&>(*program);

		auto location = glGetUniformLocation(gl_program.id, name.data());
		glUniform1f(location, f);
	}

	void gl_shader::set_uniform_int(const std::string_view name, int i) {
		const auto& gl_program = dynamic_cast<gl_shader_program&>(*program);

		auto location = glGetUniformLocation(gl_program.id, name.data());
		glUniform1i(location, i);
	}
}
