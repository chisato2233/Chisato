#include"events.h"

namespace cst {
	namespace new_event {
		struct foo{};
		using event_manger = event_manger_base<m_event, n_event>;
		using event_dispatch = event_dispatch_base<m_event, n_event>;
		auto test() -> void{
			event_manger em;
			em.add_event(m_event{}), em.add_event(n_event{});
			em.update();

			
			event_dispatch{}.set_event(m_event{}).update();
			event_dispatch{}.set_event(n_event{}).update();
			
		}
	}
}