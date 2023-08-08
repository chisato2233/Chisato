#pragma once
#include"pch.h"
#include"ChisatoCore/Core.h"
#include"ChisatoCore//Tools/Singleton.h"


namespace Chisato{

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

		Event(int _tag = Tag::None)
			:tag(_tag){ }
		virtual ~Event() = default;

		int GetTag()const noexcept { return tag; }
		inline bool IsTag(int _tag) { return GetTag() & _tag; }

		virtual std::string GetName()const noexcept = 0;
	
		operator std::string() { return GetName(); }
	};

	template<typename Ty>
	concept cpt_Event = std::is_base_of_v<Event, Ty>;

	template<cpt_Event T_Event>
	class EventSpace :Singleton<EventSpace<T_Event> > {
		friend class Event;
	private:
		std::vector<std::function<void(T_Event*)>> funcPool;
	public:
		inline void operator+= (std::function<void(T_Event*)> fun) { funcPool.push_back(fun); }
	};


	class CSTAPI EventManger {
	public:
		EventManger(Event& _event):event(_event){ }
		template<typename T>
		bool Dispatch(std::function<bool(T&)> func) {
			T* pevent = dynamic_cast<T*>(&event);
			if (pevent) {
				return func(*pevent);
			}
			else return false;
		}
	private:
		Event& event;
	};

	
}