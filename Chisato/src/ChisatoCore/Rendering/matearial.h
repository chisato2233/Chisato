#pragma once
#include "shader.h"
#include "ChisatoCore/Tools/property.h"
#include "glm/vec4.hpp"



namespace cst {
	namespace rendering {
		struct CSTAPI color:glm::vec4 {
			color(float r = 0.f , float g=0.f, float b = 0.f, float a = 1.0f) :
				glm::vec4(r, g, b, a) {}
			color(color&) = default;
			color(color&&) = default;
			color& operator=(color&) = default;
			color& operator=(color&&) = default;

			color(glm::vec4& v) :glm::vec4(v) {}
			color(glm::vec4&& v) :glm::vec4(std::move(v)) {}
			color& operator=(glm::vec4& v) { glm::vec4::operator=(v); return *this; }
			color& operator=(glm::vec4&& v) { glm::vec4::operator=(std::move(v)); return *this; }

		};
		
		struct CSTAPI colors {
			inline static color red = { 1.0,0.0,0.0,1.0 };
			inline static color blue = { 0.0,0.0,1.0,1.0 };
			inline static color green = { 0.0,1.0,0.0,1.0 };
			inline static color white = { 1.0,1.0,1.0,1.0 };
			inline static color black = { 0.0,0.0,0.0,1.0 };
		};


		struct CSTAPI material {
			material(rptr<shader> p_shader,color ambient = colors::white):
				ambient(ambient), p_shader(p_shader) {}

			void bind() {
				p_shader->bind();
				p_shader->set_uniform_float4("uColor", ambient);
			}

			auto& get_shader() const { return *p_shader; }
			void set_shader(rptr<shader> s) { p_shader = s; }

			color ambient;
		private:
			ptr<shader> p_shader;

		};
	}
}
