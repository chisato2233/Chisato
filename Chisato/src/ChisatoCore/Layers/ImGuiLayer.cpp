#include "ImGuiLayer.h"
#include"ChisatoCore/App.h"
namespace Chisato {

	ImGuiLayer::ImGuiLayer() : Layer{ "ImGui" } {

	} 

	void ImGuiLayer::OnAttach() {
		ImGui::CreateContext();
		ImGui::StyleColorsDark();

		ImGuiIO& io=ImGui::GetIO();
		io = ImGui::GetIO();
		io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
		io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

		ImGui_ImplOpenGL3_Init("#version 410");

	}
	
	void ImGuiLayer::OnUpdate() {
		ImGuiIO& io = ImGui::GetIO();
		//Debug::Log<Debug::Engine>::Error("{},{}",App::get().GetWnd().GetW(), App::get().GetWnd().GetH());

		io.DisplaySize = ImVec2(static_cast<float>(App::get().GetWnd().GetW()),static_cast<float>(App::get().GetWnd().GetH()));
		
		float t = static_cast<float>(glfwGetTime());
		io.DeltaTime = time > 0.f ? (t - time) : (1.f/60.f);
		time = t;

		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();

		static bool show = true;
		ImGui::ShowDemoWindow(&show);

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());


	}

	void ImGuiLayer::OnEvent(Event& event) {
		EventManger m{event};
		m.Dispatch<MouseDownEvent>([](const MouseDownEvent& e) {
			using namespace Debug;

			auto& io = ImGui::GetIO();
			auto button = e.GetButton();
			Log<Engine>::Info("Get in ImGui!");
			if(0<=button&&button<=ImGuiMouseButton_COUNT)
				io.AddMouseButtonEvent(button, GLFW_PRESS);
			return false;
		});

		m.Dispatch<MouseDownEvent>([](const MouseDownEvent& e) {
			auto& io = ImGui::GetIO();
			auto button = e.GetButton();
			if (0 <= button && button <= ImGuiMouseButton_COUNT)
				io.AddMouseButtonEvent(button, GLFW_RELEASE);
			return false;
		});

		m.Dispatch<MouseMoveEvent>([](MouseMoveEvent& e) {
			auto& io = ImGui::GetIO();
			io.AddMousePosEvent(e.GetX(), e.GetY());
			return false;
		});

		m.Dispatch<MouseScrollEvent>([](MouseScrollEvent& e) {
			auto& io = ImGui::GetIO();
			io.AddMouseWheelEvent(e.GetX(), e.GetY());
			return false;
		});
	}


}
