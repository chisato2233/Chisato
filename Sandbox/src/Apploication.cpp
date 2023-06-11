#include<Chisato.h>


class Sanbox :public Chisato::App {
public:
	Sanbox(){}
	~Sanbox(){}
};

std::unique_ptr<Chisato::App> Chisato::CreateApplication() 
	{ return std::make_unique<Chisato::App>(Sanbox{ }); }