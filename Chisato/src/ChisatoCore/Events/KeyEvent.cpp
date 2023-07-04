#include "KeyEvent.h"

namespace Chisato::Events{
	std::string KeyDownEvent::GetName()const noexcept{
		std::ostringstream oss;
		oss 
			<< "[Event]: Key Down \n"
			<< "[Key]: " << keycode;
		return oss.str();
	}


	std::string KeyHoldEvent::GetName() const noexcept {
		std::ostringstream oss;
		oss 
			<< "[Event]: Key Down \n"
			<< "[Key]: " << keycode << '\n'
			<< "[Repeat Count]: " << repeatCount;
		return oss.str();
	}

	std::string KeyUpEvent::GetName() const noexcept{
		std::ostringstream oss;
		oss << "[Event]: Key Up \n"
			<< "[Key]: " << keycode;
		return oss.str();
	}

	template<typename e>
	concept cpt_KeyEvent = cpt_Event<e> && std::is_base_of_v<KeyEvent, e>;

	template<typename e>
	concept cpt_KeyDownEvent = cpt_KeyEvent<e> && std::is_same_v<KeyDownEvent, e>;
	
	template<typename e>
	concept cpt_KeyUpEvent = cpt_KeyEvent<e> && std::is_same_v<KeyUpEvent, e>;
	
	template<typename e>
	concept cpt_KeyHoldEvent = cpt_KeyEvent<e> && std::is_same_v<KeyHoldEvent, e>;


}
