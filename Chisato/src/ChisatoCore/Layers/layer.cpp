#include"Layer.h"

namespace cst {
	
	void layer::static_attach() {
		sub_layer_stack_.attach();
		async_runtime_.init();
		on_attach();
	}

	void layer::static_detach() {
		sub_layer_stack_.detach();
		on_detach();
	}

	void layer::static_update() {
		
		sub_layer_stack_.update();
		async_runtime_.get().update();
		on_update();
	}

	void layer::static_event(event& event) {
		sub_layer_stack_.on_event(event);
		on_event(event);
	}
}
