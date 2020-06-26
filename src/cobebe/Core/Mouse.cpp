#include <cobebe/Core/Mouse.h>
#include <cobebe/Core/Core.h>
#include <cobebe/Core/Camera.h>
#include <cobebe/Core/Environment.h>

namespace cobebe
{
	Mouse::Mouse()
	{
		m_position = glm::vec2(0);
		m_movement = glm::vec2(0);

		m_warpMouse = true;
	}

	glm::vec2 Mouse::getPosition()
	{
		return m_position;
	}

	glm::vec2 Mouse::getMovement()
	{
		return m_movement;
	}

	bool Mouse::isButton(cobebeInput::MouseButton _button)
	{
		return false;
	}

	bool Mouse::isButtonPressed(cobebeInput::MouseButton _button)
	{
		return false;
	}

	bool Mouse::isButtonReleased(cobebeInput::MouseButton _button)
	{
		return false;
	}

	void Mouse::warpMouse(bool _switch)
	{
		m_warpMouse = _switch;
	}

	glm::vec3 Mouse::getRayDirection()
	{
		std::shared_ptr<Camera> currentCam = m_core.lock()->getCurrentCamera();
		std::shared_ptr<Environment> env = m_core.lock()->getEnvironment();

		glm::vec4 camPos = glm::vec4(currentCam->m_position, 1);

		glm::vec4 mouseClip = glm::vec4(m_position.x * 2 / float(env->getWidth()) - 1,
			1 - m_position.y * 2 / float(env->getHeight()),
			0,
			1);

		glm::mat4 camModel = currentCam->getView();

		glm::vec4 mouseProj = glm::inverse(camModel) *
			glm::inverse(currentCam->getProjection()) * mouseClip;
		glm::vec3 dirProj = glm::normalize(mouseProj - camPos);

		return dirProj;
	}

	void Mouse::pressButton(cobebeInput::MouseButton _button)
	{
		m_buttons.push_back(_button);
		m_buttonsPressed.push_back(_button);
	}

	void Mouse::releaseButton(cobebeInput::MouseButton _button)
	{
		m_buttonsReleased.push_back(_button);

		int size = m_buttons.size();
		for (std::vector<cobebeInput::MouseButton>::iterator it =
			m_buttons.begin(); it != m_buttons.end();)
		{
			if ((*it) == _button)
			{
				it = m_buttons.erase(it);
			}
			else
			{
				it++;
			}
		}
	}

	void Mouse::resetButtons()
	{
		m_buttonsPressed.clear();
		m_buttonsReleased.clear();
	}
}