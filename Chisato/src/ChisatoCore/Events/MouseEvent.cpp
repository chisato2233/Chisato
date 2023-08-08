#include "MouseEvent.h"

namespace Chisato {
	std::string MouseMoveEvent::GetName()const noexcept {
		return std::format("[Event] Mouse ({}, {})", GetX(), GetY());
	}

	std::string MouseDownEvent::GetName()const noexcept {
		return std::format("[Event] Mouse Down ({})", button);
	}


	std::string MouseHoldEvent::GetName() const noexcept {
		return std::format("[Event] Mouse Hold ({}, cnt:{})", button, GetCount());
	}

	std::string MouseUpEvent::GetName() const noexcept {
		return std::format("[Event] Mouse Up ({})", button);
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
