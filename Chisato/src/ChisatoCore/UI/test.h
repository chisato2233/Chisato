#pragma once
#include"ChisatoCore/Tools/property.h"

namespace cst {
	namespace ui {
		struct ui_element {
			void build() const {
				on_build();
			}
			std::function<void()> on_build;
		};

		struct button: ui_element {
			std::string text = " ";
			std::function<void()> on_click = []{};
			void build() {
				if (ImGui::Button(text.c_str())) {
					on_click();
				}
			}
		};

		struct tuple_wrapper_base_ {
			virtual void build() = 0;
			virtual ~tuple_wrapper_base_() = default;
		};

		template<class... Args>
		struct tuple_wrapper final :tuple_wrapper_base_{
			tuple_wrapper(Args&&... args) : data(std::forward<Args>(args)...) {}
			~tuple_wrapper() override = default;

			void build() override {
				std::apply([](auto&&... args) {
					((args.build()), ...);
				}, data);
			}

			std::tuple<Args...> data;
		};


		
		struct element_layout {
			template<class... Args>
			element_layout(Args&&... args) :
				data(std::make_shared<tuple_wrapper<Args...>>(std::forward<Args>(args)...)) {}

			void build() {
				data->build();
			}


			ptr<tuple_wrapper_base_> data;
		};


		
		struct window : ui_element{

			void build() {

				ImGuiWindowFlags window_flags = ImGuiWindowFlags_None;

				if (!title_bar) window_flags |= ImGuiWindowFlags_NoTitleBar;
				if (!enable_resize) window_flags |= ImGuiWindowFlags_NoResize;
				if (!enable_move) window_flags |= ImGuiWindowFlags_NoMove;
				if (!scroll_bar) window_flags |= ImGuiWindowFlags_NoScrollbar;
				if (!scroll_with_mouse) window_flags |= ImGuiWindowFlags_NoScrollWithMouse;
				if (!collapse) window_flags |= ImGuiWindowFlags_NoCollapse;
				if (auto_resize) window_flags |= ImGuiWindowFlags_AlwaysAutoResize;
				if (translate) window_flags |= ImGuiWindowFlags_NoBackground; 
				if (!saved) window_flags |= ImGuiWindowFlags_NoSavedSettings;
				if (!mouse_input) window_flags |= ImGuiWindowFlags_NoMouseInputs;
				if (menu_bar) window_flags |= ImGuiWindowFlags_MenuBar;
				if (horizontal_scroll) window_flags |= ImGuiWindowFlags_HorizontalScrollbar;
				if (!focus) window_flags |= ImGuiWindowFlags_NoFocusOnAppearing;
				if (!bring_to_front_on_focus) window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus;
				if (vertical_scroll_bar) window_flags |= ImGuiWindowFlags_AlwaysVerticalScrollbar;
				if (horizontal_scroll_bar) window_flags |= ImGuiWindowFlags_AlwaysHorizontalScrollbar;
				if (!use_window_padding) window_flags |= ImGuiWindowFlags_AlwaysUseWindowPadding;
				if (!nav_input) window_flags |= ImGuiWindowFlags_NoNavInputs;
				if (unsaved_document) window_flags |= ImGuiWindowFlags_UnsavedDocument;


				ImGui::Begin(title.c_str(), nullptr,  window_flags);
				body.build();
				ImGui::End();
			}

			std::string title = "window";
			element_layout body = {};
			
			bool title_bar = true;
			bool enable_resize = true;
			bool enable_move = true;
			bool scroll_bar = true;
			bool scroll_with_mouse = true;
			bool collapse = true;
			bool auto_resize = false;
			bool translate = false;
			bool saved = false;
			bool mouse_input = true;
			bool menu_bar = false;
			bool horizontal_scroll = false;
			bool focus = true;
			bool bring_to_front_on_focus = true;
			bool vertical_scroll_bar = false;
			bool horizontal_scroll_bar = false;
			bool use_window_padding = false;
			bool nav_input = true;
			bool unsaved_document = false;
		};

		struct text : ui_element {
			std::string content = " ";
			void build() {
				ImGui::Text(content.c_str());
				
			}
		};

		
		struct slider : ui_element {
			void build() {
				
				if(ImGui::SliderFloat(lable.c_str(), value.get(), min, max)) {
					on_change(*this);
				}
			}

			std::string lable = "slider";
			
			float min = 0.0f;
			float max = 1.0f;
			float default_value = min;
			ptr<float> value = std::make_shared<float>(default_value);
			
			std::function<void(const slider&)> on_change = [](auto&&...) {};

			
		};

		struct checkbox : ui_element {
			std::string label = "check box";
			bool default_checked = false;
			ptr<bool> is_checked = std::make_shared<bool>(false);

			void build()  {
				ImGui::Checkbox(label.c_str(), is_checked.get());
			}
		};

		struct input_text : ui_element {
			std::string label = "input text";
			
			ptr<std::string>input_content = std::make_shared<std::string>();
			size_t buffer_size = 256;
			std::function<void(const input_text&)> on_change = [](auto&&...) {};
			void build()  {
				input_content->resize(buffer_size);
				if(ImGui::InputText(label.c_str(),input_content->data(), buffer_size)) {
					on_change(*this);
				};
			}
		};


	}

}