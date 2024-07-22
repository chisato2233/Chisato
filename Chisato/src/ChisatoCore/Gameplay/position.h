#pragma once
#include "glm/vec3.hpp"
#include "glm/ext/quaternion_geometric.hpp"

namespace cst::gameplay {


	struct CSTAPI position {
		position() = default;
		position(glm::vec3 pos) :data_(pos) {}

		float& x() { (*on_change_)(); return data_.x; }
		float& y() { (*on_change_)(); return data_.y; }
		float& z() { (*on_change_)(); return data_.z; }

		operator glm::vec3() const { return data_; }

		auto& when_try_change() const { return *on_change_; }
	private:
		glm::vec3 data_{};
		ptr<delegate<position, void()>> on_change_ = std::make_shared<delegate<position, void()>>(this);
	};


	struct CSTAPI direction  {
		direction () = default;
		direction(glm::vec3 dir) :data_(glm::normalize(dir)) {}

		float& x() { (*on_change_)(); return data_.x; }
		float& y() { (*on_change_)(); return data_.y; }
		float& z() { (*on_change_)(); return data_.z; }

		operator glm::vec3() const { return data_; }

		auto& when_try_change() const { return *on_change_; }
	private:
		glm::vec3 data_{};
		ptr<delegate<direction, void()>> on_change_ = std::make_shared<delegate<direction, void()>>(this);
	};


	struct CSTAPI rotation {
		rotation() = default;
		rotation(glm::vec3 rot) :data_(rot) {}

		float& pitch() { (*on_change_)(); return data_.x; }
		float& yaw() { (*on_change_)(); return data_.y; }
		float& roll() { (*on_change_)(); return data_.z; }

		operator glm::vec3() const { return data_; }

		auto& when_try_change() const { return *on_change_; }

	private:
		glm::vec3 data_{};
		ptr<delegate<rotation, void()>> on_change_ = std::make_shared<delegate<rotation, void()>>(this);
	};
}
