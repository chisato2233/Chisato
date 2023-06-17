#include "MouseEvent.h"

namespace Chisato::Events {
	std::string MouseDownEvent::GetName()const noexcept {
		std::ostringstream oss;
		oss << "\n"
			<< "[Event]: Mouse Down \n"
			<< "[Position]: " << pos.first << pos.second << "\n\n";
		return oss.str();
	}


	std::string MouseHoldEvent::GetName() const noexcept {
		std::ostringstream oss;
		oss << "\n"
			<< "[Event]: Mouse Hold \n"
			<< "[Position]: " << pos.first << pos.second << '\n'
			<< "[Repeat Count]: " << repeatCount << "\n\n";
		return oss.str();
	}

	std::string MouseUpEvent::GetName() const noexcept {
		std::ostringstream oss;
		oss << "[Event]: Mouse Up \n"
			<< "[Position]: " << pos.first << pos.second << "\n\n";
		return oss.str();
	}

	template<typename e>
	concept cpt_MouseEvent = cpt_Event<e> && std::is_base_of_v<MouseEvent, e>;

	template<typename e>
	concept cpt_MouseDownEvent = cpt_MouseEvent<e> && std::is_same_v<MouseDownEvent, e>;

	template<typename e>
	concept cpt_MouseUpEvent = cpt_MouseEvent<e> && std::is_same_v<MouseUpEvent, e>;

	template<typename e>
	concept cpt_MouseHoldEvent = cpt_MouseEvent<e> && std::is_same_v<MouseHoldEvent, e>;


}
