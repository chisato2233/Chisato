#pragma once
#include<glm/glm.hpp>
#include<ChisatoCore/Tools/property.h>

#include "ChisatoCore/application.h"
#include"transform.h"


namespace cst {
	struct camera_matrix {
		glm::mat4 projection_matrix;
		glm::mat4 view_matrix;
		glm::mat4 vp_matrix;
	};



	class CSTAPI camera {
	public:
		camera() {
			auto f = [this](auto...) { recalculate_matrices(); };
			transform.position.on_change().add(f);
			transform.rotation.on_change().add(f);
			input::window::on_resize += [this](window_resize_event e) {
				update_projection();
			};
		};
		virtual ~camera() = default;

		virtual void update_projection() = 0;

		void recalculate_matrices() {
			glm::mat4 inverseTransform = glm::inverse(static_cast<glm::mat4>(transform));
			matrix.view_matrix = inverseTransform;
			matrix.vp_matrix = matrix.projection_matrix * matrix.view_matrix;
		}

		transform transform;
		camera_matrix matrix;
	};
	
	class CSTAPI orthographic_camera : public camera {
	public:
		orthographic_camera(float left, float right, float bottom, float top)
			: left_(left), right_(right), bottom_(bottom), top_(top)
		{
			update_projection();
		}

		void update_projection() override {
			float aspectRatio = application::get().window().get_w() / (float)application::get().window().get_h();
			matrix.projection_matrix = glm::ortho(left_ * aspectRatio, right_ * aspectRatio, bottom_, top_, -1.0f, 1.0f);
			recalculate_matrices();
		}

	private:
		float left_, right_, bottom_, top_;
	};




	class CSTAPI perspective_camera : public camera {
	public:
		perspective_camera(float fov, float aspectRatio, float nearPlane, float farPlane)
			: fov_(fov), aspect_ratio_(aspectRatio), near_(nearPlane), far_(farPlane)
		{
			update_projection();
		}

		void update_projection() override {
			matrix.projection_matrix = glm::perspective(glm::radians(fov_), aspect_ratio_, near_, far_);
			recalculate_matrices();
		}

	private:
		float fov_, aspect_ratio_, near_, far_;
	};
	

}
