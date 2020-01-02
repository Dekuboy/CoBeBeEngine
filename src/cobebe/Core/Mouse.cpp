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
		return glm::vec2();
	}

	glm::vec2 Mouse::getMovement()
	{
		return glm::vec2();
	}

	void Mouse::warpMouse(bool _switch)
	{

	}
}