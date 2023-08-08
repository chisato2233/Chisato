#pragma once
#include"pch.h"
#include"../Core.h"




namespace Chisato {
	class CSTAPI Object {
	public:
		virtual std::string GetName() const { return "Base Object"; }
		virtual void OnEvent() { }

	private:

	};



	template<class T>concept as_Object = std::is_base_of_v<Object, T>;
}

#define CST_OBJ(type)	public:\
						virtual std::string GetName()const override{return #type;}\
						private:
						