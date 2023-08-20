#include<Chisato.h>
#include"ChisatoCore/Log.h"

using namespace Chisato;
struct ExampleLayer : Layer {

	ExampleLayer():Layer("Example") {}

	void OnEvent( Event& event) override {
		////event.GetName();
		//event.isActive = false;
		//Debug::Log<Debug::Engine>::Trace(event.GetName());
	}
	

	void OnUpdate() override {
		//Chisato::Log::Engine::Trace("Layer Update");
	}

};


class Sandbox :public Chisato::App {
public:
	Sandbox() {
		layerStack.push(std::make_shared<ExampleLayer>());
	}
	~Sandbox()override = default;
};

Chisato::App* Chisato::Create() { return new Sandbox{ }; }