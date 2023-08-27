#pragma once
#include"pch.h"
#include"ChisatoCore/Core.h"
#include"ChisatoCore//Tools/Singleton.h"


namespace cst {

	namespace Tag {
		enum {
			None = 0,
			App = 1,
			Window = 1 << 1,
			Input = 1 << 2,
			Keybord = 1 << 3,
			Mouse = 1 << 4,
			MouseButton = 1 << 5
		};
	}

	class CSTAPI event {
		friend struct event_manger;

	protected:
		int tag_;
	public:
		bool is_active = true; //记录事件是否可用

		event(int _tag = Tag::None)
			:tag_(_tag) { }
		virtual ~event() = default;

		int get_tag()const noexcept { return tag_; }
		bool is_tag(int _tag) const { return get_tag() & _tag; }

		virtual std::string get_name()const noexcept = 0;
	};


	template<typename Ty> concept cpt_Event = std::is_base_of_v<event, Ty>;

	
	template<std::derived_from<event> T>
	struct CSTAPI event_dispatch {
		std::function<void(T&)> func;

		template<class F> requires std::invocable<F,T&> event_dispatch(F&& f) : func{std::forward<F>(f)} { }
		void operator()(event& e) {
			if (T* p = dynamic_cast<T*>(&e)) return func(*p);
		}
	};
	
	
	struct CSTAPI event_manger {
		event_manger(event& _e):event_(_e){ }

		template<std::derived_from<event> E, std::invocable<E&> F >
		void Dispatch(F&& f) {
			cst::event_dispatch<E>{std::forward<F>(f) }(event_);
		}
	private:
		event& event_;
	};

}

