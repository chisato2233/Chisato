#pragma once
#include"ChisatoCore/window.h"
#include"GLFW/glfw3.h"

namespace cst {

	class CSTAPI window_from_Windows :public window {
		GLFWwindow* wnd_ptr_;

		struct WndData : wnd_props {
			bool v_sync;
			std::function<void(event&)> callback;
		} data_;

	public:
		window_from_Windows(const wnd_props& props);
		~window_from_Windows() override;

		void on_update() override{
			glfwPollEvents();
			glfwSwapBuffers(wnd_ptr_);
		}

		uint					get_w()			const noexcept override { return data_.size.first;}
		uint					get_h()			const noexcept override { return data_.size.second; }
		bool					get_key(int key)const noexcept override { return GLFW_PRESS==glfwGetKey(wnd_ptr_, key); }
		std::pair<uint, uint>	get_size()		const noexcept override { return data_.size; }
		std::string				get_name()		const noexcept override { return std::format("Window {},from Windows", data_.title); }
		void*					get_wnd_ptr()	const noexcept override { return wnd_ptr_; }

		void set_event_callback(const std::function<void(event&)>& _callback) override { data_.callback = _callback; }
		void set_v_sync			(bool enabled) override;
		bool is_v_sync()const noexcept override { return data_.v_sync; }



	private:
		void Init(const wnd_props& props);
	};
}