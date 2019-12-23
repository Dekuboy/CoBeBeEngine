#include <cobebe/Core/Camera.h>
#include <glm/ext.hpp>

namespace cobebe
{
	Camera::Camera()
	{
		m_position = glm::vec3(0.0f);
		m_rotation = glm::mat3(1.0f);
		m_isOn = false;
	}

	glm::mat4 Camera::getView()
	{
		glm::mat4 camModel(1.0f);
		camModel = glm::translate(camModel, m_position);
		camModel = camModel * glm::mat4(m_rotation);
		return camModel;
	}

	glm::mat4 Camera::getProjection()
	{
		return m_projection;
	}


	void Camera::setProjection(float _angle, float _width, float _height, float _near, float _far)
	{
		m_projection = glm::perspective(glm::radians(_angle), _width / _height, _near, _far);
	}
}