#include <cobebe/Renderer/PointLight.h>

namespace cobebe
{
	PointLight::PointLight()
	{
		m_position = glm::vec3(0.0f);
		m_colour = glm::vec3(1.0f);
	}

	glm::vec3 PointLight::getColour()
	{
		return m_colour;
	}

	void PointLight::setColour(glm::vec3 _lightCol)
	{
		if (_lightCol != glm::vec3(0, 0, 0))
		{
			m_colour = _lightCol;
		}
	}

	float PointLight::getRadius()
	{
		return m_radius;
	}

	void PointLight::setRadius(float _radius)
	{
		if (_radius > 0.0f)
		{
			m_radius = _radius;
		}
	}
}