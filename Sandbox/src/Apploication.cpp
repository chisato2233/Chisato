#include<Chisato.h>
#include<ChisatoCore/Layers/LayerLib.h>

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


class Sandbox : public App {
public:
	Sandbox() {
		layerStack.push(std::make_shared<ExampleLayer>());
		layerStack.push_over(std::make_shared<ImGuiLayer>());

		handle = this;
	}
	~Sandbox()override = default;
};

Chisato::App* Chisato::Create() { return new Sandbox{ }; }