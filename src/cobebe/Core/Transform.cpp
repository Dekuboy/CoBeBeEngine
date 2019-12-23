#include <cobebe/Core/Transform.h>
#include <glm/ext.hpp>

namespace cobebe
{
	Transform::Transform()
	{
		m_position = glm::vec3(0.0f);
		m_rotation = glm::mat3(1.0f);
		m_scale = glm::vec3(1.0f);
	}

	glm::mat4 Transform::getModel()
	{
		m_model = glm::translate(glm::mat4(1.0f), m_position);
		m_model = m_model * glm::mat4(m_rotation);
		m_model = glm::scale(m_model, m_scale);
		return m_model;
	}

	void Transform::onPreDisplay()
	{
		m_model = glm::translate(glm::mat4(1.0f), m_position);
		m_model = m_model * glm::mat4(m_rotation);
		m_model = glm::scale(m_model, m_scale);
	}
}