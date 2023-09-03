#pragma once


namespace cst {
	template<typename T>
	concept cpt_virtual_event = requires(T t) {
		{t.update()}->std::same_as<void>;
	};

	template<typename T, typename... Ts>
	concept same_as_any = (std::same_as<T, Ts> or ...);

	namespace new_event {
		struct m_event {
			static auto update() { debug::log<>::error("m_event"); }
		};
		struct n_event {
			static auto update() { debug::log<>::error("n_event"); }
		};

		template<cpt_virtual_event... Te>
		struct event_manger_base {
			event_manger_base() {}

			auto add_event(cst::same_as_any<Te...> auto e) { std::get<std::vector<decltype(e)>>(data_).push_back(e); }

			auto update() -> void {
				std::apply([this](auto&... event_lists) {
					(update_events(event_lists), ...);
				}, data_);
			}


		private:
			auto update_events(auto& event_list) {
				for (auto& i : event_list)  i.update();
			}

			std::tuple<std::vector<Te>...> data_;
		};

		template<cpt_virtual_event... Te>
		struct event_dispatch_base{

			auto update() { std::get<0>(event_var_).update(); }

			auto& set_event(cst::same_as_any<Te...> auto e) { event_var_ = e; return *this; }
		private:
			std::variant<Te...> event_var_;
		};



		auto test() -> void;
	}


}

