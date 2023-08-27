#pragma once

namespace cst {
	namespace platform {
		struct CSTAPI Windows { };
		struct CSTAPI Andorid { };
		struct CSTAPI Linux	{ };
		struct CSTAPI Apple { };
	}

	template<typename P> concept depended_paltforms = std::is_same_v<P,platform::Windows>;
}