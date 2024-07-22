#include<Chisato.h>

#include "Render/Render_layer.h"


using namespace cst;

class Sandbox : public application {
public:
	Sandbox() {
		on_app_created += [this](auto&&...) {
			layers().push(std::make_shared<Render_layer>());
			
		};
		
	}

};


int main() {

	return engine_run<Sandbox>();

}

  