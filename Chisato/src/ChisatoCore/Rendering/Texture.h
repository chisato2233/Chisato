#pragma once


namespace cst::rendering {
	struct CSTAPI texture {
		virtual uint get_width() const noexcept = 0;
		virtual uint get_height() const noexcept = 0;
		virtual ~texture() = default;
		virtual void bind(uint i =0) = 0;
	};

	struct CSTAPI texture_2D : texture {
		virtual ~texture_2D() = default;
		static ptr<texture_2D> create(std::filesystem::path path);
	};
}