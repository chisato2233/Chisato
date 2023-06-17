#pragma once
#include"../Core.h"
#include<concepts>




namespace Chisato {
	class CSTAPI Input {

	};

	class CSTAPI Key : public Input {

	};

	class CSTAPI Mouse : public Input {

	};

	template<class T>
	concept as_Input = std::is_base_of_v<Input, T>;
}