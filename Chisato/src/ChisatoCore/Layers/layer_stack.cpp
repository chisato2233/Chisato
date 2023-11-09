#include"layer.h"
namespace cst {
	
	void layer_stack::push(std::shared_ptr<layer> layer) { stack_top_ = layer_vec_.emplace(stack_top_, layer), layer->static_attach(); }
	void layer_stack::push_over(std::shared_ptr<layer> layer) { layer_vec_.emplace_back(layer), layer->static_attach(); }
	void layer_stack::pop() { (*stack_top_)->static_detach(); layer_vec_.erase(stack_top_--); }

	void layer_stack::pop_over() {
		(*(layer_vec_.end()-1))->static_detach();
		if (stack_top_ == layer_vec_.end() - 1) pop();
		else layer_vec_.pop_back();
	}

	void layer_stack::erase(const std::shared_ptr<layer>& layer) {
		const auto i = std::ranges::find(layer_vec_, layer);
		if (i != layer_vec_.end()) {
			i->get()->static_detach();
			layer_vec_.erase(i);
			--stack_top_;
		}
	}

	void layer_stack::attach() { for (auto& i : layer_vec_) i->static_attach(); }
	void layer_stack::detach() { for (auto& i : layer_vec_) i->static_detach(); }

	void layer_stack::update() {
		for (auto& i : layer_vec_) i->static_update();
	}

	void layer_stack::on_event(event& event) {
		for(auto& i : layer_vec_) i->static_event(event);
	}
}
