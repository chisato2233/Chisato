#pragma once
#include <glm/gtc/quaternion.hpp> // 包含四元数操作
#include <glm/gtx/quaternion.hpp> // 从欧拉角到四元数的转换
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"

namespace cst {
	struct transform {
		glm::mat4 transform_matrix();

		operator glm::mat4() { return transform_matrix(); }


		glm::vec3 forward() const;
		glm::vec3 right() const;
		glm::vec3 up() const;
		glm::vec3 backward() const;
		glm::vec3 left() const;
		glm::vec3 down() const;

	private:
        void update_quaternion_from_euler() {
            rotation_quaternion = glm::quat(rotation());
        }

	public:
        property<glm::vec3> position {.value = { 0, 0, 0 }};
		property<glm::vec3> rotation {
			.value = { 0, 0, 0 },
			.setter = [this](const glm::vec3& value) {
				rotation.get_ref() = value;
				update_quaternion_from_euler();
			}
		};
        property<glm::vec3> scale {.value = { 1, 1, 1 }};

    private:
        glm::quat rotation_quaternion{ glm::quat(glm::vec3(0, 0, 0)) };
	};


	inline glm::mat4 transform::transform_matrix() {
		glm::mat4 mat = glm::mat4(1.0f);
		mat = glm::translate(mat, position.get_ref());
		mat *= glm::toMat4(rotation_quaternion);
		mat = glm::scale(mat, scale.get_ref());
		return mat;
	}

	inline glm::vec3 transform::forward() const {
		return glm::rotate(rotation_quaternion, glm::vec3(0, 0, -1));
	}

	inline glm::vec3 transform::right() const {
		return glm::rotate(rotation_quaternion, glm::vec3(1, 0, 0));
	}

	inline glm::vec3 transform::up() const {
		return glm::rotate(rotation_quaternion, glm::vec3(0, 1, 0));
	}

	inline glm::vec3 transform::backward() const {
		return glm::rotate(rotation_quaternion, glm::vec3(0, 0, 1));
	}

	inline glm::vec3 transform::left() const {
		return glm::rotate(rotation_quaternion, glm::vec3(-1, 0, 0));
	}

	inline glm::vec3 transform::down() const {
		return glm::rotate(rotation_quaternion, glm::vec3(0, -1, 0));
	}
}
