#pragma once
#include "ChisatoCore/Rendering/matearial.h"
#include"ChisatoCore/Tools/property.h"
#include "glm/gtc/type_ptr.hpp"

namespace cst {
	namespace ui {
		struct CSTAPI ui_element {
			void build() const {
				on_build();
			}
			std::function<void()> on_build;
		};

		struct CSTAPI button: ui_element {
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


		
		struct CSTAPI element_layout {
			template<class... Args>
			element_layout(Args&&... args) :
				data(std::make_shared<tuple_wrapper<Args...>>(std::forward<Args>(args)...)) {}

			template<class... Args>
			auto add(Args&&... args) {
				dynamic_data.push_back(std::make_shared<tuple_wrapper<Args...>>(std::forward<Args>(args)...));
			}

			void build() {
				data->build();
				for (auto&& item : dynamic_data) {
					item->build();
				}
			}


			ptr<tuple_wrapper_base_> data;
			std::vector<ptr<tuple_wrapper_base_>> dynamic_data;
		};


		
		struct CSTAPI window : ui_element{

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
			bool auto_resize = true;
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

		struct CSTAPI text : ui_element {
			std::string content = " ";
			void build() {
				ImGui::Text(content.c_str());
				
			}
		};

		
		struct CSTAPI slider : ui_element {
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

		struct CSTAPI checkbox : ui_element {
			std::string label = "check box";
			bool default_checked = false;
			ptr<bool> is_checked = std::make_shared<bool>(false);

			void build()  {
				ImGui::Checkbox(label.c_str(), is_checked.get());
			}
		};

		struct CSTAPI input_text : ui_element {
			std::string label = "input text";
			
			ptr<std::string>input_content = std::make_shared<std::string>();
			size_t buffer_size = 256;
			std::function<void(const input_text&)> on_change = [](auto&&...) {};
			void build()  {
				input_content->resize(buffer_size);
				if(ImGui::InputText(label.c_str(),input_content->data(), buffer_size)) {
					on_change(*this);
				}
			}
		};

		struct CSTAPI color_editor {
			std::string label = "color editor";
			rendering::color default_color = rendering::color_library::white;
			ptr<rendering::color> color = std::make_shared<rendering::color>(default_color);


			std::function<void(const color_editor&)> on_change = [](auto&&...) {};
			void build() {
				float data[] = { (*color)[0],(*color)[1],(*color)[2],(*color)[3] };

				if(ImGui::ColorEdit4(label.c_str(),glm::value_ptr(dynamic_cast<glm::vec4&>(*color)))){
					on_change(*this);
				}
				
			}
		};

		struct CSTAPI color_picker {
			std::string label = "color picker";
			rendering::color default_color = rendering::color_library::white;
			ptr<rendering::color> color = std::make_shared<rendering::color>(default_color);

			std::function<void(const color_picker&)> on_change = [](auto&&...) {};
			void build() {
				float data[] = { (*color)[0],(*color)[1],(*color)[2],(*color)[3] };
				if(ImGui::ColorPicker4(label.c_str(), glm::value_ptr(dynamic_cast<glm::vec4&>(*color)))) {
					on_change(*this);
				}
			}
		};

	}

}
