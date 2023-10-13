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

async::task my1() {
	while (1) {
		debug::log<>::trace("1");
		co_await async::next_frame{};
	}
	
}
async::task my2() {
	while (1) {
		debug::log<>::trace("2");
		co_await async::next_frame{};
	}

}

class Sandbox : public application {
public:
	Sandbox() {
		layers().push_over(std::make_shared<ImGui_layer>());
		async::system::get().start_task(my1());
		async::system::get().start_task(my2());
	}
};

int main() {
	return engine_run<Sandbox>();

}

  