#include "../include/components/camera.hpp"
#include <glm/gtc/matrix_transform.hpp>

namespace Dolly {
    // Move directions (forward/backward/0, left/right/0, up/down/0). Each direction could be 1, -1 or 0.
    // Rotations - (horizontal_amount, vertical_amount)
    void Camera::move(glm::vec3 directions, glm::vec2 rotations, float deltaTime)
    {
	auto pitch = glm::quat(glm::vec3(-rotations.y, 0, 0.f));
	auto yaw = glm::quat(glm::vec3(0, -rotations.x, 0.f));

	camera_orientation_ = glm::normalize(yaw * camera_orientation_ * pitch);

	auto camera_roll_direction = camera_orientation_ * glm::vec3(0, 0, -1);
	auto camera_pitch_direction = camera_orientation_ * glm::vec3(-1, 0, 0);

	// forward/backward move - all axes could be affected
	camera_pos_ += directions[0] * camera_roll_direction * deltaTime; /* Multiply by the speed here */

	// left/right strafe - only xz could be affected
	camera_pos_ += directions[1] * camera_pitch_direction * deltaTime;

	// up/down flying - only y-axis could be affected
	camera_pos_.y += directions[2] * deltaTime;

	view_ = glm::lookAt(camera_pos_, camera_pos_ + camera_roll_direction,
			    glm::cross(camera_roll_direction, camera_pitch_direction));
    }
}
