﻿#include <glad/glad.h>
#include <GLFW/glfw3.h>



#include "ImGui_layer.h"

#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include"ChisatoCore/application.h"
#include "ChisatoCore/UI/test.h"
#include"GLFW/glfw3.h"


//#include "imgui_impl_glfw.h"

namespace cst {

	ImGui_layer::ImGui_layer() : layer{ "ImGui" } {} 

	void ImGui_layer::on_attach() {
		auto window = static_cast<GLFWwindow*>(application::get().window().get_wnd_ptr());
		bool show = true;

		ImGui::CreateContext();
		ImGui::StyleColorsDark();
		
		ImGuiIO& io=ImGui::GetIO();

		//io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
		//io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;
		//
		
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;       // Enable Multi-Viewport / Platform Windows

		ImGui::StyleColorsDark();
		

		// When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
		ImGuiStyle& style = ImGui::GetStyle();

		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			style.WindowRounding = 0.0f;
			style.Colors[ImGuiCol_WindowBg].w = 1.0f;
		}
		
		// Setup Platform/Renderer backend
		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init("#version 410");

	}
	
	void ImGui_layer::on_update() {
		auto window = static_cast<GLFWwindow*>(application::get().window().get_wnd_ptr());
		
		ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);


		ImGuiIO& io = ImGui::GetIO();

		//io.Fonts->AddFontFromFileTTF("path/to/your/font.ttf", 16.0f);
		//if (ImGui::GetIO().Fonts->IsBuilt()) {
		//	ImGui_ImplOpenGL3_DestroyFontsTexture();
		//}
		//ImGuiFreeType::BuildFontAtlas(io.Fonts, ImGuiFreeType::ForceAutoHint);
		//if (ImGui::GetIO().Fonts->IsBuilt()) {
		//	ImGui_ImplOpenGL3_CreateFontsTexture();
		//}



		io.DisplaySize = ImVec2(static_cast<float>(application::get().window().get_w()),static_cast<float>(application::get().window().get_h()));
		
		io.DeltaTime = max(timer::delta().count(), 1.f / 60.f);




		ImGui_ImplGlfw_NewFrame();

		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();
		//-------------------------
		draw_ui();

		//--------------------------
		ImGui::Render();


		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		GLFWwindow* backup_current_context = glfwGetCurrentContext();
		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();
		glfwMakeContextCurrent(backup_current_context);
	}

	void ImGui_layer::on_event(event& event) {
		event_manger m{event};

		auto modifier = [this] {
			auto& io = ImGui::GetIO();
			auto& input = application::get().input_info();

			io.AddKeyEvent(ImGuiMod_Ctrl,	input.is_pressed(static_cast<key_code_map>(GLFW_KEY_LEFT_CONTROL))	|| input.is_pressed(static_cast<key_code_map>(GLFW_KEY_RIGHT_CONTROL)));
			io.AddKeyEvent(ImGuiMod_Shift,	input.is_pressed(static_cast<key_code_map>(GLFW_KEY_LEFT_SHIFT))	|| input.is_pressed(static_cast<key_code_map>(GLFW_KEY_RIGHT_SHIFT)));
			io.AddKeyEvent(ImGuiMod_Alt,	input.is_pressed(static_cast<key_code_map>(GLFW_KEY_LEFT_ALT))		|| input.is_pressed(static_cast<key_code_map>(GLFW_KEY_RIGHT_ALT)));
			io.AddKeyEvent(ImGuiMod_Super,	input.is_pressed(static_cast<key_code_map>(GLFW_KEY_LEFT_SUPER))	|| input.is_pressed(static_cast<key_code_map>(GLFW_KEY_RIGHT_SUPER)));
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
			io.AddKeyEvent(translate((int)e.get_key().val), GLFW_PRESS);
			return false;
		});

		m.Dispatch<key_up_event>([modifier](const key_up_event& e) {
			auto& io = ImGui::GetIO();
			modifier();
			io.AddKeyEvent(translate((int)e.get_key().val), GLFW_RELEASE);
			return false;
		});

		m.Dispatch<key_char_event>([](const key_char_event& e) {
			ImGui::GetIO().AddInputCharacter(e.get_char());
			return false;
		});
	}

	void ImGui_layer::on_detach() {
		ImGui_ImplOpenGL3_Shutdown();
		ImGui::DestroyContext();
	}

	void ImGui_layer::draw_ui() {
		bool show = true;
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize |
			ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoSavedSettings |
			ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoBackground;

		ImGui::Begin("Overlay", nullptr, window_flags);
		//ImGui::SetWindowPos(ImVec2(20, 20)); // 根据需要调整位置
		ImGui::SetWindowFontScale(3); // 根据需要调整字体大小


		ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "FPS: %f", 1/timer::delta().count()); // 红色
		
		ImGui::End();


		ImGui::ShowDemoWindow(&show);

		UI_drawer();
	}



}
