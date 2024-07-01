#pragma once
#include<ChisatoCore/Async/runtime.h>



namespace cst {


	struct CSTAPI layer_runtime {

		void init() { run_ptr_ = std::make_unique<async::runtime>(); }
		auto& get()  noexcept { return *run_ptr_; }
	private:
		ptr<async::runtime> run_ptr_ = nullptr;
	};
}