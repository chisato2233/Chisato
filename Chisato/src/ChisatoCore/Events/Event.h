#pragma once
#include"pch.h"
#include"ChisatoCore/Core.h"
#include"ChisatoCore//Tools/Singleton.h"


namespace Chisato {

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

	class CSTAPI Event {
		friend class EventManger;

	protected:
		int tag;
	public:
		bool isActive = true; //记录事件是否可用

		Event(int _tag = Tag::None)
			:tag(_tag) { }
		virtual ~Event() = default;

		int GetTag()const noexcept { return tag; }
		bool IsTag(int _tag) const { return GetTag() & _tag; }

		virtual std::string GetName()const noexcept = 0;
	};


	template<typename Ty> concept cpt_Event = std::is_base_of_v<Event, Ty>;

	template<std::derived_from<Event> T_Event>
	struct CSTAPI Dispatch {
		
		static auto& get() { static std::vector<std::function<void()> > funcs; return funcs; }
		Dispatch(Event& e, std::function<void(T_Event&)> f) {
			auto p = dynamic_cast<T_Event*>(&e);
			if (p) {
				get().push_back(std::bind(f, *p));
			}
		}
		void operator()()const { for (auto& i : get()) i(); }
	};


	class CSTAPI EventManger {
		Event& event;
	public:
		EventManger(Event& _event):event(_event){ }
		template<cpt_Event T> bool Dispatch(std::function<bool(T&)> func) {
			T* p_event = dynamic_cast<T*>(&event);
			if (p_event&&p_event->isActive) return func(*p_event);
			return false;
		}
	};

	
}