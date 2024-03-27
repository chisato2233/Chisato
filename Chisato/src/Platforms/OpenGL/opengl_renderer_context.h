#pragma once
#include"ChisatoCore/Rendering/renderer_context.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>


namespace cst {


	struct CSTAPI opengl_renderer_context : renderer_context {
		opengl_renderer_context(GLFWwindow* window_ptr) : window_ptr(window_ptr) { }

		void init() override {
			glfwMakeContextCurrent(window_ptr);
			int _ = gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress));
			CST_ASSERT(_, "Could not initialize GLAD!!")


			debug::log<>::trace("\nOpenGL Information:\n Vender:{}\n Renderer:{}\n Version:{} \n",
				(char*)glGetString(GL_VENDOR),
				(char*)glGetString(GL_RENDERER), 
				(char*)glGetString(GL_VERSION)
			);

		}


		void swap_buffers() override { glfwSwapBuffers(window_ptr); }

		auto get_window_ptr() const -> GLFWwindow* { return window_ptr; }

	private:
		GLFWwindow* window_ptr;
	};
}