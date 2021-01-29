#include <cobebe/Core/Environment.h>

namespace cobebe
{
	Environment::Environment()
	{
		m_deltaTime = 1.0f / 60.0f;
		m_width = 1920;
		m_height = 1080;
	}

	const float Environment::getDeltaTime()
	{
		return m_deltaTime;
	}

	const int Environment::getCurrentTick()
	{
		return m_currentTick;
	}

	const int Environment::getWidth()
	{
		return m_width;
	}

	const int Environment::getHeight()
	{
		return m_height;
	}
}