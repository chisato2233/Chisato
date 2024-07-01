#pragma once
#include"ChisatoCore/window_base.h"
#include "Platforms/OpenGL/opengl_renderer_context.h"


namespace cst {
	//add more specialized is undefined behaviour. 
	template<cpt_plat P>class CSTAPI window;

	template<>
	class CSTAPI window<platforms::Windows> :public window_base {
		GLFWwindow* wnd_ptr_;
		std::unique_ptr<renderer_context> renderer_context_;

		struct WndData : wnd_props {
			bool v_sync;
			std::function<void(event&)> callback;
		} data_;

	public:
		window(const wnd_props& props);
		~window() override;

		void on_update() override;

		uint					get_w()					const noexcept override { return data_.size.first;}
		uint					get_h()					const noexcept override { return data_.size.second; }
		float					get_aspect_ratio()		const noexcept override { return static_cast<float>(data_.size.first) / data_.size.second; }
		std::pair<uint, uint>	get_size()				const noexcept override { return data_.size; }
		std::string				get_name()				const noexcept override { return std::format("Window {},from Windows", data_.title); }
		void*					get_wnd_ptr()			const noexcept override { return wnd_ptr_; }
		renderer_context*		get_renderer_context()	const noexcept override { return renderer_context_.get(); }

		void set_event_callback(const std::function<void(event&)>& _callback) override { data_.callback = _callback; }
		void set_v_sync			(bool enabled) override;
		bool is_v_sync()const noexcept override { return data_.v_sync; }



	private:
		void init(const wnd_props& props);
	};

}