#include "Environment.h"

namespace cobebe
{
	float Environment::getDeltaTime()
	{
		return deltaTime;
	}

	unsigned int Environment::getWidth()
	{
		return m_width;
	}

	unsigned int Environment::getHeight()
	{
		return m_height;
	}
}