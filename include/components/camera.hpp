#ifndef COMPONENTS_CAMERA_HPP
#define COMPONENTS_CAMERA_HPP

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

namespace Dolly {
    class Camera {
    public:
	void move(glm::vec3 directions, glm::vec2 rotations, float deltaTime);
    private:
	glm::mat4 view_;
	glm::vec3 camera_pos_;
	glm::quat camera_orientation_;
    };
}

#endif /* COMPONENTS_CAMERA_HPP */
