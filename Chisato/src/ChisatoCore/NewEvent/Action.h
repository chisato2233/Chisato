//#pragma once
//#include"../Core.h"
//#include"../Object.h"
//#include<concepts>
//#include<iostream>
//
//
//namespace Chisato {
//
//	class CSTAPI Action : public Object {
//		CST_OBJ(Action)
//	};
//
//
//	class CSTAPI Down : public Action {
//	public:
//		CST_OBJ(Down)
//	};
//
//	class CSTAPI Hold : public Down {
//		CST_OBJ(Hold)
//	private:
//		int reaptCount;
//	public:
//		Hold(int cnt) : reaptCount{ cnt } { }
//
//		constexpr int GetCount() { return reaptCount; }
//	};
//
//	class CSTAPI Up : public Action {
//		CST_OBJ(Up)
//	};
//
//	class CSTAPI Move :public Action {
//		CST_OBJ(Move)
//	private:
//		std::pair<float, float> from, to;
//		bool hasFrom = false;
//	public:
//		Move(std::pair<float, float> _from, std::pair<float, float> _to)
//			:
//			from{ _from }, to{ _to }, 
//			hasFrom{ true } 
//		{ }
//		Move(float x, float y) : to{x,y} { }
//		Move(){ }
//	};
//
//	class CSTAPI Open :public Action {
//		CST_OBJ(Open)
//	};
//
//	class CSTAPI Close :public Action {
//		CST_OBJ(Close)
//	};
//
//	class Resize :public Action {
//		CST_OBJ(Resize)
//	private:
//		int weight, height;
//	public:
//
//		constexpr int GetW() { return weight; }
//		constexpr int GetH() { return height; }
//	};
//
//
//
//	template<class T>
//	concept as_Action = std::is_base_of_v<Action, T>;
//}
//
//
