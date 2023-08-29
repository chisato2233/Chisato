#pragma once
namespace cst {
	namespace platforms {
		struct CSTAPI platform_base{};
		struct CSTAPI Windows : platform_base{};
	}

	template<class P> concept cpt_plat = std::derived_from<P, platforms::platform_base>;
}