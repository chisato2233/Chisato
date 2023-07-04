//#pragma once
//#include "../Core.h"
//#include<concepts>
//
//namespace Chisato {
//	class CSTAPI Controlable : public Object {
//		CST_OBJ(Controlable)
//	public:
//		template<as_Action Tact>void HandleEvent(Tact act);
//	};
//
//
//	class CSTAPI Window :public Controlable {
//		CST_OBJ(Window)
//
//	};
//	
//	template<class T> concept as_Controlable= std::is_base_of_v<Controlable, T>;
//}