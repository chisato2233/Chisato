#pragma once


namespace cst {
	class CSTAPI layer_stack {
		std::vector<std::shared_ptr<layer>> layer_vec_;
		std::vector<std::shared_ptr<layer>>::iterator stack_top_=layer_vec_.begin();

	public:
		auto begin	() const noexcept { return layer_vec_.begin();	}
		auto end	() const noexcept { return layer_vec_.end();	}

		void push		(const std::shared_ptr<layer>& layer) { stack_top_ = layer_vec_.emplace(stack_top_, layer), layer->on_attach(); }
		void push_over	(const std::shared_ptr<layer>& layer) { layer_vec_.emplace_back(layer), layer->on_attach(); }

		void pop() { layer_vec_.erase(stack_top_--); }
		void pop_over() {
			if (stack_top_ == layer_vec_.end() - 1) pop();
			else layer_vec_.pop_back();
		}

		void erase(const std::shared_ptr<layer>& layer) {
			const auto i = std::ranges::find(layer_vec_, layer);
			if (i != layer_vec_.end()) {
				layer_vec_.erase(i);
				--stack_top_;
			}
		}
	};
}