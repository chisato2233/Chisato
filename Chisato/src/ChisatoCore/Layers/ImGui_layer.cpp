#include "ImGui_layer.h"
#include"ChisatoCore/application.h"
namespace cst {

	ImGui_layer::ImGui_layer() : layer{ "ImGui" } {} 

	void ImGui_layer::on_attach() {
		ImGui::CreateContext();
		ImGui::StyleColorsDark();

		ImGuiIO& io=ImGui::GetIO();
		io = ImGui::GetIO();
		io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
		io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

		ImGui_ImplOpenGL3_Init("#version 410");

	}
	
	void ImGui_layer::on_update() {
		ImGuiIO& io = ImGui::GetIO();

		io.DisplaySize = ImVec2(static_cast<float>(application::get().window().get_w()),static_cast<float>(application::get().window().get_h()));
		
		const auto t = static_cast<float>(glfwGetTime());
		io.DeltaTime = time > 0.f ? (t - time) : (1.f/60.f);
		time = t;

		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();

		static bool show = true;
		ImGui::ShowDemoWindow(&show);

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());


	}

	void ImGui_layer::on_event(event& event) {
		event_manger m{event};

		auto modifier = [this] {
			auto& io = ImGui::GetIO();
			auto& input = application::get().input();

			io.AddKeyEvent(ImGuiMod_Ctrl,	input.is_key_pressed(GLFW_KEY_LEFT_CONTROL)	|| input.is_key_pressed(GLFW_KEY_RIGHT_CONTROL));
			io.AddKeyEvent(ImGuiMod_Shift,	input.is_key_pressed(GLFW_KEY_LEFT_SHIFT)	|| input.is_key_pressed(GLFW_KEY_RIGHT_SHIFT));
			io.AddKeyEvent(ImGuiMod_Alt,	input.is_key_pressed(GLFW_KEY_LEFT_ALT)		|| input.is_key_pressed(GLFW_KEY_RIGHT_ALT));
			io.AddKeyEvent(ImGuiMod_Super,	input.is_key_pressed(GLFW_KEY_LEFT_SUPER)	|| input.is_key_pressed(GLFW_KEY_RIGHT_SUPER));
		};
		//App Event*******************************************************************
		m.Dispatch<window_resize_event>([](auto& e) {
			auto& io = ImGui::GetIO();
			io.DisplaySize = ImVec2{ static_cast<float>(e.get_w()),static_cast<float>(e.get_h()) };
			io.DisplayFramebufferScale = ImVec2(1.f, 1.f);
			glViewport(0, 0, e.get_w(), e.get_h());
			return false;
		});

		//Mouse Event*******************************************************************
		m.Dispatch<mouse_down_event>([modifier](const auto& e) {
			auto& io = ImGui::GetIO();
			modifier();
			const auto button = e.get_button();
			if(0<=button&&button<=ImGuiMouseButton_COUNT) io.AddMouseButtonEvent(button, GLFW_PRESS);
			return false;
		});

		m.Dispatch<mouse_up_event>([modifier](const mouse_up_event& e) {
			auto& io = ImGui::GetIO();
			modifier();
			const auto button = e.get_button();
			if (0 <= button && button <= ImGuiMouseButton_COUNT) io.AddMouseButtonEvent(button, GLFW_RELEASE);
			return false;
		});

		m.Dispatch<mouse_move_event>([modifier](mouse_move_event& e) {
			auto& io = ImGui::GetIO();
			modifier();
			io.AddMousePosEvent(e.get_x(), e.get_y());
			return false;
		});

		m.Dispatch<mouse_scroll_event>([](mouse_scroll_event& e) {
			auto& io = ImGui::GetIO();
			io.AddMouseWheelEvent(e.get_x(), e.get_y());
			return false;
		});

		//Key Board Event*************************************************************

		m.Dispatch<key_down_event>([modifier](const key_down_event& e) {
			auto& io = ImGui::GetIO();
			modifier();
			io.AddKeyEvent(translate(e.get_key()), GLFW_PRESS);
			return false;
		});

		m.Dispatch<key_up_event>([modifier](const key_up_event& e) {
			auto& io = ImGui::GetIO();
			modifier();
			io.AddKeyEvent(translate(e.get_key()), GLFW_RELEASE);
			return false;
		});

		m.Dispatch<key_char_event>([](const key_char_event& e) {
			ImGui::GetIO().AddInputCharacter(e.get_char());
			return false;
		});
	}


}
