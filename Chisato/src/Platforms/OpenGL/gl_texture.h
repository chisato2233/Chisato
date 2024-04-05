#pragma once
#include"ChisatoCore/Rendering/Texture.h"

#include"stb_image.h"
namespace cst::rendering {


	struct gl_texture_2D:texture_2D {
		gl_texture_2D(std::string_view path) : path(path) {
			

		}
		~gl_texture_2D() override = default;

		uint get_width() const noexcept override { return width_; }
		uint get_height() const noexcept override { return height_; }

		void bind() override {
			
		}

	public:

		std::string_view path;
		uint id;
	private:
		uint width_, height_;
	};
}