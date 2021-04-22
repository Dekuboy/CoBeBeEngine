#include <cobebe/Renderer/AnimationController.h>
#include <cobebe/Core/Environment.h>

namespace cobebe
{
	AnimationController::AnimationController()
	{
		m_incrementDeltaTime = false;
	}

	int AnimationController::playAnimation(std::string _name, bool _repeating, float _time, float _speed)
	{
		int id = checkName(_name);

		if (id == -1)
		{
			return id;
		}

		playAnimation(id, _repeating, _time, _speed);

		return id;
	}

	void AnimationController::playAnimation(int _id, bool _repeating, float _time, float _speed)
	{
		AnimationValues* ani = checkId(_id);

		if (!ani)
		{
			return;
		}

		ani->m_time = _time;
		ani->m_repeating = _repeating;
		ani->m_speed = _speed;
	}

	int AnimationController::playOnlyAnimation(std::string _name, bool _repeating, float _time, float _speed)
	{
		int id = checkName(_name);

		if (id == -1)
		{
			return id;
		}

		playOnlyAnimation(id, _repeating, _time, _speed);

		return id;
	}

	void AnimationController::playOnlyAnimation(int _id, bool _repeating, float _time, float _speed)
	{
		AnimationValues* ani;
		for (std::list<AnimationValues>::iterator itr = m_values.begin();
			itr != m_values.end();)
		{
			if (itr->m_id != _id)
			{
				itr = m_values.erase(itr);
			}
		}

		if (m_values.size() == 1)
		{
			ani = &(*m_values.begin());
			ani->m_time = _time;
			ani->m_repeating = _repeating;
			ani->m_speed = _speed;
			return;
		}

		ani = checkId(_id);

		if (!ani)
		{
			return;
		}

		ani->m_time = _time;
		ani->m_repeating = _repeating;
		ani->m_speed = _speed;
	}

	int AnimationController::stopAnimation(std::string _name)
	{
		int id = checkName(_name);

		if (id == -1)
		{
			return id;
		}

		stopAnimation(id);

		return id;
	}

	void AnimationController::stopAnimation(int _id)
	{
		for (std::list<AnimationValues>::iterator itr = m_values.begin();
			itr != m_values.end();)
		{
			if (itr->m_id == _id)
			{
				m_values.erase(itr);
				return;
			}
		}
	}

	void AnimationController::stopAllAnimations()
	{
		m_values.clear();
	}

	int AnimationController::setAnimationTime(std::string _name, float _time)
	{
		int id = checkName(_name);

		if (id == -1)
		{
			return id;
		}

		setAnimationTime(id, _time);

		return id;
	}

	void AnimationController::setAnimationTime(int _id, float _time)
	{
		for (std::list<AnimationValues>::iterator itr = m_values.begin();
			itr != m_values.end();)
		{
			if (itr->m_id == _id)
			{
				itr->m_time = _time;
				return;
			}
		}
	}

	int AnimationController::setAnimationSpeed(std::string _name, float _speed)
	{
		int id = checkName(_name);

		if (id == -1)
		{
			return id;
		}

		setAnimationSpeed(id, _speed);

		return id;
	}

	void AnimationController::setAnimationSpeed(int _id, float _speed)
	{
		for (std::list<AnimationValues>::iterator itr = m_values.begin();
			itr != m_values.end();)
		{
			if (itr->m_id == _id)
			{
				itr->m_speed = _speed;
				return;
			}
		}
	}

	void AnimationController::incrementAnimations(float _deltaTime)
	{
		for (std::list<AnimationValues>::iterator itr = m_values.begin();
			itr != m_values.end(); itr++)
		{
			itr->m_time += itr->m_speed * _deltaTime;
		}
	}

	void AnimationController::onTick()
	{
		if (m_incrementDeltaTime)
		{
			incrementAnimations(getEnvironment()->getDeltaTime());
		}
	}
}
