#pragma once
#include<glm/glm.hpp>
#include<ChisatoCore/Tools/property.h>

#include "ChisatoCore/application.h"
#include"transform.h"


namespace cst::rendering {
	struct camera_matrix {
		glm::mat4 projection_matrix;
		glm::mat4 view_matrix;
		glm::mat4 vp_matrix;
	};



	class CSTAPI viewport {
	public:
		viewport() {
			auto f = [this](auto...) { recalculate_matrices(); };
			transform.position.on_change->add(f);
			transform.rotation.on_change->add(f);
			transform.scale.on_change->add(f);

			zoom_factor.on_change += [this](auto...) {
				update_projection();
			};

		};
		virtual ~viewport() = default;

		virtual void update_projection() = 0;

		void recalculate_matrices() {
			glm::mat4 inverseTransform = glm::inverse(static_cast<glm::mat4>(transform));
			matrix.view_matrix = inverseTransform;
			matrix.vp_matrix = matrix.projection_matrix * matrix.view_matrix;
		}

		void zoom(float factor) {
			zoom_factor += factor;
			update_projection();
		}

		transform transform;
		camera_matrix matrix;
		property<float> zoom_factor {1.5f};

	};
	
	class CSTAPI orthographic_viewport : public viewport {
	public:
		orthographic_viewport(float left, float right, float bottom, float top)
			: left_(left), right_(right), bottom_(bottom), top_(top)
		{
			orthographic_viewport::update_projection();
		}

		void update_projection() override {
			const float aspectRatio = application::window().get_aspect_ratio();
			matrix.projection_matrix = glm::ortho(
				left_ * aspectRatio * zoom_factor.get(), 
				right_ * aspectRatio*zoom_factor.get(),
				bottom_*zoom_factor.get(), 
				top_*zoom_factor.get(), 
				-1.0f, 1.0f
			);
			recalculate_matrices();
		}

	private:
		float left_, right_, bottom_, top_;
	};




	class CSTAPI perspective_viewport : public viewport {
	public:
		perspective_viewport(float fov, float aspectRatio, float nearPlane, float farPlane)
			: fov_(fov), aspect_ratio_(aspectRatio), near_(nearPlane), far_(farPlane)
		{
			perspective_viewport::update_projection();
		}

		void update_projection() override {
			matrix.projection_matrix = glm::perspective(glm::radians(fov_), aspect_ratio_, near_, far_);
			recalculate_matrices();
		}

	private:
		float fov_, aspect_ratio_, near_, far_;
	};
	

}


