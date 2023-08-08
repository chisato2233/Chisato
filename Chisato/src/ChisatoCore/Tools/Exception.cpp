#include "Exception.h"

const char* ChisatoException::what() const noexcept{ return whatr.c_str(); }
std::string ChisatoException::GetType() const noexcept{ return "Unkown Exception"; }

void ChisatoException::GetWhat() noexcept{
	whatr = std::format(
		"\nException!"
		"[Type]: {}\n"
		"[Information]: none\n {}",
		GetType(),
		GetOriginal()
	);
}

std::string ChisatoException::GetOriginal() noexcept{
	return std::format(
		"[Line]: {}\n"
		"[Flie]: {}\n",
		line, file
	);
}
