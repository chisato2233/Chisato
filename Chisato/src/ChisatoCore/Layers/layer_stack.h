#pragma once


namespace cst {
	class layer;
	/*template<typename U,typename V>
	concept same_ptr<V> = std::same_as<V, std::shared_ptr<typename V::elemeny_type>> && std::derived_from<U, typename V::element_type>;*/

	class CSTAPI layer_stack {
		std::vector<std::shared_ptr<layer>> layer_vec_;
		std::vector<std::shared_ptr<layer>>::iterator stack_top_=layer_vec_.begin();

	public:
		auto begin	() const noexcept { return layer_vec_.begin();	}
		auto end	() const noexcept { return layer_vec_.end();	}

		void push		(std::shared_ptr<layer> layer);
		void push_over	(std::shared_ptr<layer> layer);

		void pop();
		void pop_over();

		void erase(const std::shared_ptr<layer>& layer);
		auto size()const->size_t { return layer_vec_.size(); }
		void attach();
		void detach();
		void update();
		void on_event(event& event);
	};
}
