#include <cobebe/Renderer/PointLight.h>
#include <cobebe/Core/Core.h>
#include <glm/ext.hpp>

namespace cobebe
{
	PointLight::PointLight()
	{
		m_position = glm::vec3(0.0f);
		m_colour = glm::vec3(0.2f);

		float aspect = (float)1024 / (float)1024;
		float near = 1.0f;
		m_radius = 25.0f;
		glm::mat4 shadowProj = glm::perspective(glm::radians(90.0f), aspect, near, m_radius);

		m_lightSpaces.push_back(shadowProj *
			glm::lookAt(m_position, m_position + glm::vec3(1.0, 0.0, 0.0), glm::vec3(0.0, -1.0, 0.0)));
		m_lightSpaces.push_back(shadowProj *
			glm::lookAt(m_position, m_position + glm::vec3(-1.0, 0.0, 0.0), glm::vec3(0.0, -1.0, 0.0)));
		m_lightSpaces.push_back(shadowProj *
			glm::lookAt(m_position, m_position + glm::vec3(0.0, 1.0, 0.0), glm::vec3(0.0, 0.0, 1.0)));
		m_lightSpaces.push_back(shadowProj *
			glm::lookAt(m_position, m_position + glm::vec3(0.0, -1.0, 0.0), glm::vec3(0.0, 0.0, -1.0)));
		m_lightSpaces.push_back(shadowProj *
			glm::lookAt(m_position, m_position + glm::vec3(0.0, 0.0, 1.0), glm::vec3(0.0, -1.0, 0.0)));
		m_lightSpaces.push_back(shadowProj *
			glm::lookAt(m_position, m_position + glm::vec3(0.0, 0.0, -1.0), glm::vec3(0.0, -1.0, 0.0)));

		m_depthCube = std::make_shared<glwrap::DepthCube>(1024, 1024);
	}

	glm::vec3 PointLight::getPosition()
	{
		return m_position;
	}

	void PointLight::setPosition(glm::vec3 _position)
	{
		m_position = _position;
		setRadius(m_radius);
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

			m_lightSpaces.clear();

			float aspect = (float)1024 / (float)1024;
			float near = 1.0f;
			glm::mat4 shadowProj = glm::perspective(glm::radians(90.0f), aspect, near, m_radius);

			m_lightSpaces.push_back(shadowProj *
				glm::lookAt(m_position, m_position + glm::vec3(1.0, 0.0, 0.0), glm::vec3(0.0, -1.0, 0.0)));
			m_lightSpaces.push_back(shadowProj *
				glm::lookAt(m_position, m_position + glm::vec3(-1.0, 0.0, 0.0), glm::vec3(0.0, -1.0, 0.0)));
			m_lightSpaces.push_back(shadowProj *
				glm::lookAt(m_position, m_position + glm::vec3(0.0, 1.0, 0.0), glm::vec3(0.0, 0.0, 1.0)));
			m_lightSpaces.push_back(shadowProj *
				glm::lookAt(m_position, m_position + glm::vec3(0.0, -1.0, 0.0), glm::vec3(0.0, 0.0, -1.0)));
			m_lightSpaces.push_back(shadowProj *
				glm::lookAt(m_position, m_position + glm::vec3(0.0, 0.0, 1.0), glm::vec3(0.0, -1.0, 0.0)));
			m_lightSpaces.push_back(shadowProj *
				glm::lookAt(m_position, m_position + glm::vec3(0.0, 0.0, -1.0), glm::vec3(0.0, -1.0, 0.0)));
		}
	}
}