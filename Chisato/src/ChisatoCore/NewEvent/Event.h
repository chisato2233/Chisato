//#pragma once
//#include"../Core.h"
//
//#include"Input.h"
//#include"Controlable.h"
//
//namespace Chisato {
//
//	//Event »ùÀà
//	class CSTAPI Event_base : public Object{
//		CST_OBJ(Event_base)
//	public:
//	};
//
//	template<class T>
//	concept has_OnEvent =
//		std::is_base_of_v<Input,T> ||
//		std::is_base_of_v<Controlable, T> ||
//		requires{ T::OnEvent(); };
//
//	template<
//		as_Object T_Obj,
//		as_Action T_Action
//	> 
//	class CSTAPI Event : public Event_base {
//	private:
//		T_Obj obj;
//		T_Action action;
//	public:
//		void OnEvent() override { obj.HandleEvent(action); }
//	};
//	
//
//	template<class T, class Standered>
//	concept Same_as_EventType =
//		std::derived_from<T, Event_base> && std::convertible_to<Standered, T>;
//
//	template<class T>
//	concept Input_EventType =
//		Same_as_EventType<T, Event<Input, Action> >;
//
//	template<class T>
//	concept Controlable_EventType =
//		Same_as_EventType<T, Event<Controlable, Action> >;
//
//	template<class T>
//	concept Standered_EventType =
//		Input_EventType<T> || Controlable_EventType<T>;
//}
//
