#pragma once
#include<iostream>

#include<queue>
#include<map>
#include<type_traits>

#include<functional>


namespace cst {
	template<class...> inline constexpr bool always_false = false;

	template<class... A> struct delegate;

	template<class Re> struct delegate_result {
		using type = std::vector<opt<Re>>;
		using element_type = opt<Re>;
		static type null() { return {}; }
	};

	template<> struct delegate_result<void> {
		using type = void;
		using element_type = void;
		static type null() {}
	};
	namespace async {
		template<class Re, class...Args> struct _delegate_awaiter;
	}
	template<class Re, class... Args> struct _delegate_impl;





	struct delegate_id_pair_base {
		virtual ~delegate_id_pair_base() = default;
		virtual void register_new_id(uint64_t id) = 0;
		virtual void remove_ids_from_delegate() = 0;
	};

	template<class Re,class... Args>
	struct delegate_id_pair : delegate_id_pair_base {
		std::list<uint64_t> ids;
		_delegate_impl<Re, Args...>* delegate;

		delegate_id_pair(std::list<uint64_t> ids, _delegate_impl<Re, Args...>* delegate) : ids{ ids }, delegate{ delegate } {}
		void register_new_id(uint64_t id) override {
			ids.push_back(id);
		}

		void remove_ids_from_delegate() override {
			for (auto id : ids)
				delegate->remove(id);
		}
	};

	struct auto_remove_from_delegate {
		std::unordered_map<void*, uptr<delegate_id_pair_base>> delegate_map;

		auto_remove_from_delegate() = default;
		auto_remove_from_delegate(auto_remove_from_delegate&&) = default;
		auto_remove_from_delegate(auto_remove_from_delegate& other) {}

		template<typename Re, typename... Args>
		auto register_delegate(_delegate_impl<Re, Args...>* delegate, uint64_t id) {
			const auto ptr = static_cast<void*>(delegate);
			if (auto it = delegate_map.find(ptr); it == delegate_map.end())
				delegate_map[ptr] = std::make_unique<delegate_id_pair<Re, Args...>>(std::list<uint64_t>{id}, delegate);
			else it->second->register_new_id(id);

		}

		~auto_remove_from_delegate() {
			for (const auto& pair : delegate_map | std::views::values)
				pair->remove_ids_from_delegate();
		}

		
	};

	template<class Re, class... Args>
	struct _delegate_impl : no_copy {
		_delegate_impl() = default;

		using func_type = std::function<Re(Args...)>;
		/*auto begin()const noexcept { return func_map_.begin(); }
		auto end()const noexcept { return func_map_.end(); }*/



		bool empty()const noexcept { return func_map_.empty(); }
		bool is_frozen()const noexcept { return is_frozen_; }
		size_t size()const noexcept { return func_map_.size(); }

		auto on_call() noexcept->_delegate_impl<void, Args...>& {
			enable_call_next = true;
			if (!next_delegate_)
				next_delegate_ = std::make_unique<_delegate_impl<void, Args...>>();
			return *next_delegate_;
		}

		template<std::convertible_to<func_type> F>
		auto add(F&& f, int count = -1) {
			func_map_.insert({ ++next_func_id_, std::forward<F>(f) });
			
			if (count != -1) erase_queue_.emplace(count + call_count_, next_func_id_);
			return next_func_id_;
		}
		

		template<std::derived_from<auto_remove_from_delegate> Obj, std::convertible_to<func_type> F>
		auto add(Obj* obj, F&& f, int count = -1) {
			func_map_.insert({ ++next_func_id_, std::forward<F>(f) });
			if (count != -1) erase_queue_.emplace(count + call_count_, next_func_id_);
			static_cast<auto_remove_from_delegate*>(obj)->register_delegate(this,next_func_id_);
			return next_func_id_;

		}

		auto remove(uint64_t id) { func_map_.erase(id); }

		auto delay_remove(uint64_t id, int count = 1) {
			erase_queue_.emplace(count + call_count_, id);
		}

		auto clear() { func_map_.clear(); }

		void freeze() { is_frozen_ = true; }
		void unfreeze() { is_frozen_ = false; }

		auto call_all(Args&&... args) -> typename delegate_result<Re>::type {
			if (!is_frozen_) {
				++call_count_;
				_call_next(std::forward<Args>(args)...);
			}

			if (is_banned || empty() || is_frozen_) {
				return delegate_result<Re>::null();
			}

			_update_erase_queue();
			return _for_each_call(std::forward<Args>(args)...);
		}

		template<std::convertible_to<func_type> F>
		_delegate_impl& operator +=(F&& f) {
			add(std::forward<F>(f));
			return *this;
		}

		auto& operator -=(uint64_t id) {
			remove(id);
			return *this;
		}

		auto operator()(Args... args) {
			return call_all(std::forward<Args>(args)...);
		}

		auto operator co_await() {
			return async::_delegate_awaiter<Re, Args...>{this};
		}


	private:
		auto _for_each_call(Args&&... args) -> typename delegate_result<Re>::type {
			if constexpr (std::is_same_v<Re, void>) {
				for (auto& [_, f] : func_map_)
					std::invoke(f, std::forward<Args>(args)...);
				return;
			}
			else {
				std::vector<opt<Re>> res;
				for (auto& [_, f] : func_map_)
					res.emplace_back(opt<Re>{
					std::invoke(f, std::forward<Args>(args)...)
				});
				return res;
			}

		}

		auto _update_erase_queue() {
			while (!erase_queue_.empty() && call_count_ >= erase_queue_.top().index) {
				func_map_.erase(erase_queue_.top().get<0>());
				erase_queue_.pop();
			}
		}

		auto _call_next(Args&&... args) {
			if (next_delegate_ && enable_call_next) {
				next_delegate_->call_all(std::forward<Args>(args)...);
				if (next_delegate_->empty())
					enable_call_next = false, next_delegate_ = nullptr;
			}
		}

	public:
		bool is_banned = false;
		bool enable_call_next = false;
	private:

		std::map<uint64_t, func_type> func_map_;

		std::priority_queue <
			unit<unsigned, uint64_t>,
			std::vector<unit<unsigned, uint64_t>>,
			std::greater<>
		> erase_queue_;

		uint32_t next_func_id_ = 0;


		unsigned int call_count_ = 0;
		bool is_frozen_ = false;
		uptr<_delegate_impl<void, Args...>> next_delegate_ = nullptr;
	};





	template<class... T> struct _get_delegate_impl {
		static_assert(always_false<T...>, "this is not a function type");
	};



	template<class Re, class... Args>
	struct _get_delegate_impl<Re(Args...)> {
		using type = _delegate_impl<Re, Args...>;
		using return_type = Re;
		using params = std::tuple<Args...>;
	};

	template<class Obj, class Re, class... Args>
	struct _get_delegate_impl<Obj, Re(Args...)> {
		using type = struct _ :_delegate_impl<Re, Obj*, Args...> {
			auto operator()(Args&&... args) {
				std::invoke(
					&_delegate_impl<Re, Obj*, Args...>::operator(),
					this,
					std::move(static_cast<delegate<Obj, Re(Args...)>*>(this)->obj_),
					std::forward<Args>(args)...
				);
			}
		};
	};




	template<class Fx>
	struct delegate<Fx> :_get_delegate_impl<Fx>::type {
		delegate() = default;
		explicit operator bool() const { return !this->empty(); }
	};


	template<class Obj, class Fx>
	struct delegate<Obj, Fx> :_get_delegate_impl<Obj, Fx>::type {
		friend struct _get_delegate_impl<Obj, Fx>;

		delegate(Obj* obj) : obj_{ obj } {}

		void bind(Obj* obj) { obj_ = obj; }
		auto get() const->Obj* { return obj_; }

		explicit operator bool()const { return obj_ && !this->empty(); }
	private:
		Obj* obj_ = nullptr;
	};

	template<class Obj, class Fx> delegate(Obj*) -> delegate<Obj, Fx>;

	template<typename... A>struct delegate_ptr;

	template<class Fx >
	struct delegate_ptr<Fx> : ptr<delegate<Fx>> {
		using return_type = typename delegate_result<typename _get_delegate_impl<Fx>::return_type>::type;
		using impl_type = typename _get_delegate_impl<Fx>::type;

		impl_type& get_impl() { return *std::dynamic_pointer_cast<impl_type>(*this); }

		delegate_ptr() :ptr<delegate<Fx>>{ std::make_shared<delegate<Fx>>() } {}

		template<typename F> requires requires (F f) { std::declval<delegate< Fx>>().operator+=(std::forward<F>(f)); }
		impl_type& operator+=(F&& f) {
			return get_impl().operator+=(std::forward<F>(f));
		}

		template<typename... Args> requires requires(Args... args) { std::declval<delegate<Fx>>().operator()(std::forward<Args>(args)...); }
		return_type operator()(Args&&... args) {
			return get_impl().operator()(std::forward<Args>(args)...);
		}
	};


	template<class Obj,class Fx >
	struct delegate_ptr<Obj,Fx> : ptr<delegate<Obj,Fx>> {
		delegate_ptr(Obj* self) : ptr<delegate<Obj,Fx>>{ std::make_shared<delegate<Obj,Fx>>(self) } {}

		using return_type = typename delegate_result<typename _get_delegate_impl<Fx>::return_type>::type;
		using impl_type = typename _get_delegate_impl<Obj, Fx>::type;

		impl_type& get_impl() { return *std::dynamic_pointer_cast<impl_type>(*this); }

		template<typename F> requires requires (F f){ std::declval<delegate<Obj,Fx>>().operator+=(std::forward<F>(f)); }
		impl_type& operator+=(F&& f) {
			static_assert(requires (F) { std::declval<delegate<Obj, Fx>>().operator+=(std::forward<F>(f)); });
			return static_cast<impl_type&>(get_impl().operator+=(std::forward<F>(f)));
		}

		template<typename... Args> requires requires(Args... args) { std::declval<delegate<Obj, Fx>>().operator()(std::forward<Args>(args)...); }
		return_type operator()(Args&&... args) {
			static_assert(requires(Args...) { std::declval<delegate<Obj, Fx>>().operator()(std::forward<Args>(args)...); });
			return get_impl().operator()(std::forward<Args>(args)...);
		}
	};
}
