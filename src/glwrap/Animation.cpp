#include <glwrap/Animation.h>

namespace glwrap
{
	void Animation::setRepeating(bool _switch)
	{
		m_repeating = _switch;
	}

	void Animation::setEnabled(bool _switch)
	{
		if (m_enabled != _switch)
		{
			m_time = 0;
			m_enabled = _switch;
		}
	}

	Animation::Animation()
	{
		m_enabled = false;
		m_repeating = false;
		m_time = 0;
	}

	bool Animation::getEnabled()
	{
		return m_enabled;
	}

	std::string Animation::getName()
	{
		return m_name;
	}

	void Animation::setName(std::string _name)
	{
		m_name = _name;
	}

	int Animation::getCurrentFrame()
	{
		return m_time;
	}

	double Animation::getTrueCurrentFrame()
	{
		return m_time;
	}

	int Animation::getMaxFrames()
	{
		return 0;
	}

	void Animation::nextFrame(float _deltaTime)
	{

	}

	void Animation::setCurrentFrame(double _currentFrame)
	{
		m_time = _currentFrame;
		if (m_time >= m_totalTime)
		{
			if (m_repeating == false)
			{
				m_time = 0;
				m_enabled = false;
			}
			else
			{
				int diff = m_time / m_totalTime;
				if (diff)
				{
					m_time -= (float)diff * m_totalTime;
				}
			}
		}
	}
}