#include "mouse_event.h"

namespace cst {
	std::string mouse_move_event::get_name()const noexcept {
		return std::format("[Event]: Mouse ({}, {})", get_x(),get_y());
	}

	std::string mouse_down_event::get_name()const noexcept {
		return std::format("[Event]: Mouse Down ({})", button_);
	}


	std::string mouse_hold_event::get_name() const noexcept {
		return std::format("[Event]: Mouse Hold ({}, cnt:{})", button_, get_count());
	}

	std::string mouse_up_event::get_name() const noexcept {
		return std::format("[Event]: Mouse Up ({})", button);
	}

	template<typename e>
	concept cpt_MouseEvent = cpt_Event<e> && std::is_base_of_v<mouse_event, e>;

	template<typename e>
	concept cpt_MouseDownEvent = cpt_MouseEvent<e> && std::is_same_v<mouse_down_event, e>;

	template<typename e>
	concept cpt_MouseUpEvent = cpt_MouseEvent<e> && std::is_same_v<mouse_up_event, e>;

	template<typename e>
	concept cpt_MouseHoldEvent = cpt_MouseEvent<e> && std::is_same_v<mouse_hold_event, e>;


}
