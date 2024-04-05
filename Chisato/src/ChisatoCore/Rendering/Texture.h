#pragma once


namespace cst::rendering {
	struct texture {
		virtual uint get_width() const noexcept = 0;
		virtual uint get_height() const noexcept = 0;
		virtual ~texture() = default;
		virtual void bind() = 0;
	};

	struct texture_2D : texture {
		virtual ~texture_2D() = default;
		static ptr<texture_2D> create(std::string_view path);
	};
}