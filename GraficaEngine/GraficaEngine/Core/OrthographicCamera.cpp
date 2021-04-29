#include "OrthographicCamera.h"

namespace Engine
{
	OrthographicCamera::OrthographicCamera(
		glm::vec3 position,
		glm::vec3 up,
		float yaw,
		float pitch
	) : Camera(position, up, yaw, pitch) {};

	glm::mat4 OrthographicCamera::getProjectionMatrix() const
	{
		return glm::ortho(-8.0f, 8.0f, -6.0f, 6.0f, -10.0f, 10.0f); // TODO: Change parameters
	}
}