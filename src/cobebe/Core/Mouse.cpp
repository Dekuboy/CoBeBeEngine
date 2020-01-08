#include <cobebe/Core/Mouse.h>

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

	void Mouse::warpMouse(bool _switch)
	{
		m_warpMouse = _switch;
	}
}