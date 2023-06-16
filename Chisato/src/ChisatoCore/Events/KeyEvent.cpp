#include "KeyEvent.h"

namespace Chisato::Events{
	std::string KeyDownEvent::GetName()const noexcept{
		std::ostringstream oss;
		oss <<"\n"
			<< "[Event]: Key Down \n"
			<< "[Key]: " << keycode << "\n\n";
		return oss.str();
	}


	std::string KeyHoldEvent::GetName() const noexcept {
		std::ostringstream oss;
		oss <<"\n"
			<< "[Event]: Key Down \n"
			<< "[Key]: " << keycode << '\n'
			<< "[Repeat Count]: " << repeatCount << "\n\n";
		return oss.str();
	}

	std::string KeyUpEvent::GetName() const noexcept{
		std::ostringstream oss;
		oss << "[Event]: Key Up \n"
			<< "[Key]: " << keycode << "\n\n";
		return oss.str();
	}

}
