#pragma once
#include "imgui.h"
#include "shader.h"
#include "ChisatoCore/Tools/property.h"
#include"ChisatoCore/Rendering/Texture.h"
#include "glm/vec4.hpp"



namespace cst {
	namespace rendering {
		struct CSTAPI color:glm::vec4 {
			enum  type { rgb, hsv };


			color(float r = 0.f , float g=0.f, float b = 0.f, float a = 1.0f) :
				glm::vec4(r, g, b, a) {}

			color(int r, int g, int b, int a = 255) :
				glm::vec4(r / 255.f, g / 255.f, b / 255.f, a / 255.f) {}

			color(std::initializer_list<float> list) {
				if (list.size() == 4) {
					(*this)[0] = *list.begin();
					(*this)[1] = *(list.begin() + 1);
					(*this)[2] = *(list.begin() + 2);
					(*this)[3] = *(list.begin() + 3);
				}
			}



			color(color&) = default;
			color(color&&) = default;
			color& operator=(color&) = default;
			color& operator=(color&&) = default;

			color(glm::vec4& v) :glm::vec4(v) {}
			color(glm::vec4&& v) :glm::vec4(std::move(v)) {}
			color& operator=(glm::vec4& v) { glm::vec4::operator=(v); return *this; }
			color& operator=(glm::vec4&& v) { glm::vec4::operator=(std::move(v)); return *this; }

			type get_type(){ return type_; }
			auto to_rgb() ->color&{
				if(type_==hsv) {
					ImGui::ColorConvertHSVtoRGB((*this)[0], (*this)[1], (*this)[2], (*this)[0], (*this)[1], (*this)[2]);
					type_ = rgb;
				}
				return *this;
			}
			auto to_hsv()->color& {
				if (type_ == rgb) {
					ImGui::ColorConvertRGBtoHSV((*this)[0], (*this)[1], (*this)[2], (*this)[0], (*this)[1], (*this)[2]);
					type_ = hsv;
				}
				return *this;
			}
		private:
			type type_ = rgb;
			
		};
		
		struct CSTAPI colors {
			inline static color red = { 1.0,0.0,0.0,1.0 };
			inline static color blue = { 0.0,0.0,1.0,1.0 };
			inline static color green = { 0.0,1.0,0.0,1.0 };
			inline static color white = { 1.0,1.0,1.0,1.0 };
			inline static color black = { 0.0,0.0,0.0,1.0 };
		};


		struct CSTAPI material {
			material(rptr<shader_set> p_shader,rptr<texture_2D> texture = nullptr,color ambient = colors::white):
				ambient(ambient), texture(texture),p_shader(p_shader) {}

			void bind() {
				p_shader->bind();
		
				p_shader->set_uniform_float4("uColor", ambient);
				if(texture!=nullptr) {
					int slot = 0;
					texture->bind(slot);
					p_shader->set_uniform_int("uTexture", slot);
				}
			}

			auto& get_shader() const { return *p_shader; }
			void set_shader(rptr<shader_set> s) { p_shader = s; }

			color ambient;
			ptr<rendering::texture_2D> texture;
		private:
			ptr<shader_set> p_shader;

		};
	}
}
