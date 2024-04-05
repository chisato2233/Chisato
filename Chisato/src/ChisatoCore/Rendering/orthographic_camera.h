#pragma once
#include<glm/glm.hpp>
#include<ChisatoCore/Tools/property.h>

#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"


namespace cst {
	struct camera_matrix {
		glm::mat4 projection_matrix;
		glm::mat4 view_matrix;
		glm::mat4 vp_matrix;
	};

	struct transform {
		property<glm::vec3> position {.value = { 0,0,0 }};
		property<float> rotation {.value = 0.0f};
		property<glm::vec3> scale {.value = { 1,1,1 }};

		auto transform_matrix() -> glm::mat4 {
			return	position_matrix() *
					rotation_matrix() *
					scale_matrix();
		}
		auto position_matrix()-> glm::mat4 { return glm::translate(glm::mat4(1.0f), position()); }
		auto rotation_matrix() -> glm::mat4 { return glm::rotate(glm::mat4(1.0f), rotation(), glm::vec3(0, 0, 1)); }
		auto scale_matrix() -> glm::mat4 { return glm::scale(glm::mat4(1.0f), scale()); }

		operator glm::mat4() { return transform_matrix(); }
	};


	struct CSTAPI orthographic_camera {

		orthographic_camera(float left, float right, float bottom, float top) {
			matrix.projection_matrix = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
			matrix.view_matrix = glm::mat4(1.0f);
			matrix.vp_matrix = matrix.projection_matrix * matrix.view_matrix;
			auto f = [this](auto...) {
				recalcu_matrix();
			};
			transform.position.on_change().add(f);
			transform.rotation.on_change().add(f);
			
		}


		~orthographic_camera() = default;

		transform transform;
		camera_matrix matrix;

	private:
		void recalcu_matrix() {
			matrix.view_matrix = transform.transform_matrix();
			matrix.vp_matrix = matrix.projection_matrix * matrix.view_matrix;
		}
	};
}
