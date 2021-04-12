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
		return m_model;
	}

	void Transform::setModelMatrix()
	{
		glm::mat4 modelRotation = glm::mat4(m_rotation);
		glm::quat tempQuat = glm::normalize(glm::quat_cast(modelRotation));
		m_rotation = glm::mat3_cast(tempQuat);

		m_model = glm::translate(glm::mat4(1.0f), m_position);
		m_model = m_model * glm::mat4(m_rotation);
		m_model = glm::scale(m_model, m_scale);
		m_rotation = m_rotation;
	}

	void Transform::onPreDisplay()
	{
		setModelMatrix();
	}
}