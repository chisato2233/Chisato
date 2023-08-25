#pragma once
#include"../Events/EventLib.h"

namespace Chisato {
	class CSTAPI Layer {
		std::string name;
	public:
		Layer(std::string&& name = "Layer") :name{ name } { }
		virtual ~Layer() = default;

		virtual void OnAttach() { }
		virtual void OnDetach() { }
		virtual void OnUpdate() { }
		virtual void OnEvent(Event& event) { }

		auto GetName()const noexcept { return name; }
	};
};