#pragma once

#include"../Core.h"

#include<string>
#include<functional>

namespace Chisato::Events{

	enum Tag {
		None = 0,
		App = 1,
		Input = 1 << 1,
		Keybord = 1 << 2,
		Mouse = 1 << 3,
		MouseButton = 1 << 4
	};


	class CSTAPI Event {
		friend class EventManger;

	public:

	protected:
		int tag;
	public:

		Event(int _tag = Tag::None)
			:tag(_tag){ }

		int GetTag()const noexcept { return tag; }
		inline bool IsTag(int _tag) { return GetTag() & _tag; }
			
		virtual std::string GetName()const noexcept = 0;

	};
}