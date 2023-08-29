//#pragma once
//#include"../Core.h"
//#include"Action.h"
//#include"../Object.h"
//
//#include<string>
//#include<map>
//#include<concepts>
//
//
////现在实现的是输入源的类型
//
//namespace Chisato {
//
//
//	class CSTAPI Input : public Object{
//		CST_OBJ( Input )
//
//	public:
//		template<as_Action Tact> void HandleEvent(Tact act){ }
//	};
//
//	class CSTAPI Keybored : public Input {
//		CST_OBJ(Keybored)
//	private:
//		int keycode;
//	public:
//		Keybored(int _keycode) :keycode(_keycode) { }
//
//		constexpr int GetCode() { return keycode; }
//	};
//
//	class CSTAPI Mouse : public Input {
//		CST_OBJ(Mouse)
//	private:
//		std::pair<float, float> pos;
//
//	public:
//		Mouse(float x, float y)
//			:
//			pos({ x,y }) {
//			
//		}
//
//		constexpr float GetX(){ return pos.first; }
//		constexpr float GetY(){ return pos.second; }
//		constexpr std::pair<float, float> GetPos(){ return pos; }
//
//	};
//
//
//	//辅助类型判断的概念
//	template<class T> concept as_Input = std::is_base_of_v<Input, T>;
//}