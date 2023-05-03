#include<Chisato.h>


class Sanbox :public Chisato::App {
public:
	Sanbox(){}
	~Sanbox(){}
};

Chisato::App* Chisato::CreateApplication() {
	return new Sanbox();
}