#pragma once
#include"pch.h"
#include"ChisatoCore/Core.h"

namespace Chisato::Events{

	enum Tag {
		None = 0,
		App = 1,
		Window=1 << 1,
		Input = 1 << 2,
		Keybord = 1 << 3,
		Mouse = 1 << 4,
		MouseButton = 1 << 5
	};


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

		inline operator std::string() { return GetName(); }
	};

	template<typename Ty>
	concept cpt_Event = std::is_base_of_v<Event, Ty>;

	class EventManger {
		  
	};

}