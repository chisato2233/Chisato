#pragma once
#include"pch.h"
#include"../Core.h"




namespace cst {
	struct CSTAPI Object {
		virtual				~Object	()		= default;
		virtual void		OnCreate()		= 0;
		virtual void		OnUpdate()		= 0;
		virtual void		OnEvent	(event&)= 0;
		virtual void		OnDie	()		= 0;
		virtual std::string GetName	()		= 0;
	};

	template<class T>concept as_Object = std::is_base_of_v<Object, T>;
}

#define CST_OBJ(type)	public:\
						virtual std::string GetName()const override{return #type;}\
						private:
						