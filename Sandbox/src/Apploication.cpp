#include<Chisato.h>


using namespace cst;

struct ExampleLayer : layer {

	ExampleLayer():layer("Example") {}

	void on_event( event& event) override {
		////event.GetName();
		//event.isActive = false;
		//Debug::Log<Debug::Engine>::Trace(event.GetName());
	}
	

	void on_update() override {
		//Chisato::Log::Engine::Trace("Layer Update");
	}

};


class Sandbox : public application {
public:
	Sandbox() {
		layers().push_over(std::make_shared<ImGui_layer>());
	}
};

int main() {
	return engine_run<Sandbox>();
}

  