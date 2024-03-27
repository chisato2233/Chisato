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
		property<float> rotation {.value = 1.0f};
	};


	struct CSTAPI orthographic_camera {

		orthographic_camera(float left, float right, float bottom, float top) {
			matrix.projection_matrix = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
			matrix.view_matrix = glm::mat4(1.0f);
			matrix.vp_matrix = matrix.projection_matrix * matrix.view_matrix;
			auto f = [this](auto...) {
				recalcu_matrix();
			};
			transform.position.on_change->add(f);
			transform.rotation.on_change->add(f);
		}


		~orthographic_camera() = default;

		transform transform;
		camera_matrix matrix;

	private:
		void recalcu_matrix() {
			matrix.view_matrix =
				glm::translate(glm::mat4(1.0f), transform.position()) *
				glm::rotate(glm::mat4(1.0f), transform.rotation(), glm::vec3(0, 0, 1));

			matrix.vp_matrix = matrix.projection_matrix * matrix.view_matrix;
		}
	};
}
