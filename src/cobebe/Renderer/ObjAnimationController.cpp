#include <cobebe/Renderer/ObjAnimationController.h>
#include <cobebe/Resources/RendAssets.h>
#include <cobebe/Core/Core.h>

namespace cobebe
{
	ObjAnimationController::ObjAnimationController(std::shared_ptr<glwrap::VertexArray> _model)
	{
		m_model = _model;

		std::vector<std::shared_ptr<glwrap::ObjAnimation> > animations = m_model->getAnimations();

		for (std::vector<std::shared_ptr<glwrap::ObjAnimation> >::iterator itr = animations.begin();
			itr != animations.end(); itr++)
		{
			m_animationTimes.push_back(0);
			m_enabled.push_back(false);
			m_repeating.push_back(false);
			m_speeds.push_back(1);
		}
	}

	ObjAnimationController::~ObjAnimationController()
	{

	}

	void ObjAnimationController::loadAnimation(std::string _path)
	{
		std::shared_ptr<ObjPartAnimation> temp = getCore()->loadAsset<ObjPartAnimation>(_path);
		for (std::list<std::shared_ptr<ObjPartAnimation> >::iterator itr = m_animations.begin();
			itr != m_animations.end(); itr++)
		{
			if ((*itr) == temp)
			{
				return;
			}
		}
		if (!temp->m_internal)
		{
			temp->m_internal = m_model->addAnimation(_path);

			updateValues();
		}
		m_animations.push_back(temp);
	}

	int ObjAnimationController::playAnimation(std::string _name, bool _repeating)
	{
		int id;

		id = m_model->enableAnimation(_name);

		if (id >= m_animationTimes.size())
		{
			updateValues();
			if (id >= m_animationTimes.size())
			{
				return -1;
			}
		}

		m_repeating.at(id) = _repeating;

		if (!m_enabled.at(id))
		{
			m_animationTimes.at(id) = 0;
			m_enabled.at(id) = true;
		}

		return id;
	}

	void ObjAnimationController::playAnimation(int _id, bool _repeating)
	{
		if (_id >= m_animationTimes.size())
		{
			updateValues();
			if (_id >= m_animationTimes.size())
			{
				return;
			}
		}

		m_repeating.at(_id) = _repeating;

		if (!m_enabled.at(_id))
		{
			m_animationTimes.at(_id) = 0;
			m_enabled.at(_id) = true;
		}
	}

	int ObjAnimationController::playOnlyAnimation(std::string _name, bool _repeating)
	{
		int id;

		id = m_model->enableAnimation(_name);

		if (id >= m_animationTimes.size())
		{
			updateValues();
			if (id >= m_animationTimes.size())
			{
				return -1;
			}
		}

		int count = 0;
		std::vector<double>::iterator timeItr = m_animationTimes.begin();
		for (std::vector<bool>::iterator itr = m_enabled.begin();
			itr != m_enabled.end(); itr++)
		{
			if (count == id)
			{
				if (!(*itr))
				{
					(*itr) = true;
					(*timeItr) = 0;
				}
			}
			else
			{
				(*itr) = false;
				(*timeItr) = 0;
			}
			timeItr++;
		}

		return id;
	}

	void ObjAnimationController::playOnlyAnimation(int _id, bool _repeating)
	{
		if (_id >= m_animationTimes.size())
		{
			updateValues();
			if (_id >= m_animationTimes.size())
			{
				return;
			}
		}

		int count = 0;
		std::vector<double>::iterator timeItr = m_animationTimes.begin();
		for (std::vector<bool>::iterator itr = m_enabled.begin();
			itr != m_enabled.end(); itr++)
		{
			if (count == _id)
			{
				if (!(*itr))
				{
					(*itr) = true;
					(*timeItr) = 0;
				}
			}
			else
			{
				(*itr) = false;
				(*timeItr) = 0;
			}
			timeItr++;
		}
	}

	int ObjAnimationController::stopAnimation(std::string _name)
	{
		int id;

		id = m_model->enableAnimation(_name);

		if (id >= m_animationTimes.size())
		{
			updateValues();
			if (id >= m_animationTimes.size())
			{
				return -1;
			}
		}

		if (m_enabled.at(id))
		{
			m_enabled.at(id) = false;
		}

		return id;
	}

	void ObjAnimationController::stopAnimation(int _id)
	{
		if (_id >= m_animationTimes.size())
		{
			updateValues();
			if (_id >= m_animationTimes.size())
			{
				return;
			}
		}

		if (m_enabled.at(_id))
		{
			m_enabled.at(_id) = false;
		}
	}

	void ObjAnimationController::stopAllAnimations()
	{
		for (std::vector<bool>::iterator itr = m_enabled.begin();
			itr != m_enabled.end(); itr++)
		{
			(*itr) = false;
		}
	}

	int ObjAnimationController::setAnimationSpeed(std::string _name, double _speed)
	{
		int id;

		id = m_model->enableAnimation(_name);

		if (id >= m_animationTimes.size())
		{
			updateValues();
			if (id >= m_animationTimes.size())
			{
				return -1;
			}
		}

		m_speeds.at(id) = _speed;
		return id;
	}

	void ObjAnimationController::setAnimationSpeed(int _id, double _speed)
	{
		if (_id >= m_animationTimes.size())
		{
			updateValues();
			if (_id >= m_animationTimes.size())
			{
				return;
			}
		}

		m_speeds.at(_id) = _speed;
	}

	int ObjAnimationController::getAnimationId(std::string _name)
	{
		return m_model->enableAnimation(_name);
	}

	void ObjAnimationController::incrementAnimations(float _deltaTime)
	{
		std::vector<std::shared_ptr<glwrap::ObjAnimation> > animations = m_model->getAnimations();

		if (m_animationTimes.size() != animations.size())
		{
			updateValues();
			if (m_animationTimes.size() != animations.size())
			{
				return;
			}
		}

		std::vector<bool>::iterator enableItr = m_enabled.begin();
		std::vector<bool>::iterator repeatItr = m_repeating.begin();
		std::vector<double>::iterator timeItr = m_animationTimes.begin();
		std::vector<double>::iterator speedItr = m_speeds.begin();

		for (std::vector<std::shared_ptr<glwrap::ObjAnimation> >::iterator itr = animations.begin();
			itr != animations.end(); itr++)
		{
			if (*enableItr)
			{
				(*itr)->setEnabled(true);
				(*itr)->setRepeating(*repeatItr);
				(*itr)->setCurrentFrame(*timeItr);
				(*itr)->nextFrame(_deltaTime * (*speedItr));
				(*enableItr) = (*itr)->getEnabled();
				(*timeItr) = (*itr)->getTrueCurrentFrame();
			}

			enableItr++;
			repeatItr++;
			timeItr++;
			speedItr++;
		}
	}

	void ObjAnimationController::setToDraw()
	{
		std::vector<std::shared_ptr<glwrap::ObjAnimation> > animations = m_model->getAnimations();

		if (m_animationTimes.size() != animations.size())
		{
			updateValues();
			if (m_animationTimes.size() != animations.size())
			{
				return;
			}
		}

		std::vector<bool>::iterator enableItr = m_enabled.begin();
		std::vector<bool>::iterator repeatItr = m_repeating.begin();
		std::vector<double>::iterator timeItr = m_animationTimes.begin();

		for (std::vector<std::shared_ptr<glwrap::ObjAnimation> >::iterator itr = animations.begin();
			itr != animations.end(); itr++)
		{
			(*itr)->setEnabled(*enableItr);
			(*itr)->setRepeating(*repeatItr);
			(*itr)->setCurrentFrame(*timeItr);

			enableItr++;
			repeatItr++;
			timeItr++;
		}
	}

	void ObjAnimationController::updateValues()
	{
		std::vector<std::shared_ptr<glwrap::ObjAnimation> > animations = m_model->getAnimations();
		for (int i = m_animationTimes.size(); i < animations.size(); i++)
		{
			m_animationTimes.push_back(0);
			m_enabled.push_back(false);
			m_repeating.push_back(false);
			m_speeds.push_back(1);
		}
	}
}