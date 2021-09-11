#pragma once

#include "glm/glm.hpp"
#include "glm/vec3.hpp"

class Camera
{
public:
	Camera();
	~Camera();
private:
	glm::mat4 m_ViewMatrix;
	glm::vec3 m_CameraPosition;
	glm::vec3 m_CameraDirection;
	glm::vec3 m_WorldUp;
	glm::vec3 m_CameraRight;
	glm::vec3 m_CameraUp;
};
