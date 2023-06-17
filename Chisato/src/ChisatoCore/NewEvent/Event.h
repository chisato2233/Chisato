#pragma once
#include"../Core.h"

#include"Input.h"
#include"Action.h"

namespace Chisato {

	class CSTAPI Event_base {

	};

	template<
		as_Input obj,
		as_Action action
	> 
	class CSTAPI Event : public Event_base {

	};

	template<class T, class Standered>
	concept Same_as_EventType =
		std::derived_from<T, Event_base>&& std::convertible_to<Standered, T>;





}

