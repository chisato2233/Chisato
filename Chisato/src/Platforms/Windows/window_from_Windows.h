#pragma once
#include"ChisatoCore/window_base.h"
#include"GLFW/glfw3.h"


namespace cst {
	//add more specialized is undefined behaviour. 
	template<cpt_plat P>class CSTAPI window;

	template<>
	class CSTAPI window<platforms::Windows> :public window_base {
		GLFWwindow* wnd_ptr_;
		
		struct WndData : wnd_props {
			bool v_sync;
			std::function<void(event&)> callback;
		} data_;

	public:
		window(const wnd_props& props);
		~window() override;

		void on_update() override{
			glfwPollEvents();
			glfwSwapBuffers(wnd_ptr_);
		}

		uint					get_w()			const noexcept override { return data_.size.first;}
		uint					get_h()			const noexcept override { return data_.size.second; }
		std::pair<uint, uint>	get_size()		const noexcept override { return data_.size; }
		std::string				get_name()		const noexcept override { return std::format("Window {},from Windows", data_.title); }
		void*					get_wnd_ptr()	const noexcept override { return wnd_ptr_; }

		void set_event_callback(const std::function<void(event&)>& _callback) override { data_.callback = _callback; }
		void set_v_sync			(bool enabled) override;
		bool is_v_sync()const noexcept override { return data_.v_sync; }



	private:
		void init(const wnd_props& props);
	};

}