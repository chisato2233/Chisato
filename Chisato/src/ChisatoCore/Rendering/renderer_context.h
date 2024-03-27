#pragma once
namespace cst {

	struct CSTAPI renderer_context {
		virtual void init() = 0;
		virtual void swap_buffers() = 0;
		
	};
}