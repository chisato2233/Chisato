#pragma once
#include "imgui.h"
#include"ChisatoCore/Rendering/Texture.h"

#include"stb_image.h"
namespace cst::rendering {


	struct CSTAPI gl_texture_2D:texture_2D {
		gl_texture_2D(std::filesystem::path path) : path(path) {
			stbi_set_flip_vertically_on_load(true);
			int width, height, channels;
			auto f_path = path.string();
			stbi_uc* data = stbi_load(f_path.c_str(), &width, &height, &channels, STBI_rgb);
			if(!data) {
				debug::log<>::error("Failed to load texture: {}", f_path);
				return; // 确保在失败时不继续执行
			}
			
			width_ = width;
			height_ = height;

			load_image_data(data, width, height, channels);

			stbi_image_free(data);


		}

		gl_texture_2D(void* data, uint width, uint height,int channels = 3) : width_(width), height_(height) {
			load_image_data(data, width, height, channels);
		}
		
		~gl_texture_2D() override {
			glDeleteTextures(1, &id);
		}

		void load_image_data(void* data, uint width, uint height, int channels = 3) {
			const GLenum internal_format = channels == 3 ? GL_RGB8 : GL_RGBA8;
			const GLenum format = channels == 3 ? GL_RGB : GL_RGBA;
			glCreateTextures(GL_TEXTURE_2D, 1, &id);
			glTextureStorage2D(id, 1, internal_format, width, height);

			glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

			glTextureSubImage2D(id, 0, 0, 0, width, height, format, GL_UNSIGNED_BYTE, data);

		}


		uint get_width() const noexcept override { return width_; }
		uint get_height() const noexcept override { return height_; }

		void bind(uint slot = 0) override {
			glActiveTexture(GL_TEXTURE0 + slot);
			glBindTextureUnit(slot, id);
		}

	public:

		std::filesystem::path path;
		uint id;
	private:
		uint width_, height_;
	};
}