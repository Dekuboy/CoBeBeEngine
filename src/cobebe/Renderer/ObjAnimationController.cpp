#include <cobebe/Renderer/ObjAnimationController.h>
#include <cobebe/Resources/RendAssets.h>
#include <cobebe/Core/Core.h>

namespace cobebe
{
	ObjAnimationController::ObjAnimationController(std::shared_ptr<glwrap::VertexArray> _model)
	{
		if (!_model)
		{
			throw Exception("NO MODEL ATTACHED TO ANIMATION CONTROLLER");
		}
		m_model = _model;
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
		}
		m_animations.push_back(temp);
	}

	void ObjAnimationController::setAnimationTime(int _id, float _time)
	{
		for (std::list<AnimationValues>::iterator itr = m_values.begin();
			itr != m_values.end();)
		{
			if (itr->m_id == _id)
			{
				std::shared_ptr<glwrap::ObjAnimation> ani = m_model->getAnimations().at(_id);
				ani->setRepeating(itr->m_repeating);
				ani->setCurrentFrame(_time);
				itr->m_time = ani->getCurrentFrame();
				return;
			}
		}
	}

	void ObjAnimationController::setToDraw()
	{
		m_model->disableAllAnimations();
		if (m_values.size() > 0)
		{
			std::vector<std::shared_ptr<glwrap::ObjAnimation> > animations = m_model->getAnimations();
			int id;
			for (std::list<AnimationValues>::iterator itr = m_values.begin(); itr != m_values.end(); itr++)
			{
				id = itr->m_id;
				animations.at(id)->setEnabled(true);
				animations.at(id)->setRepeating(itr->m_repeating);
				animations.at(id)->setCurrentFrame(itr->m_time);
			}
		}
	}

	int ObjAnimationController::checkName(std::string& _name)
	{
		std::vector<std::shared_ptr<glwrap::ObjAnimation>> list = m_model->getAnimations();
		int id = -1;

		for (int i = 0; i < list.size(); i++)
		{
			if (list.at(i)->getName() == _name)
			{
				id = i;
				break;
			}
		}

		return id;
	}

	AnimationValues* ObjAnimationController::checkId(int _id)
	{
		for (std::list<AnimationValues>::iterator itr = m_values.begin();
			itr != m_values.end();)
		{
			if (itr->m_id == _id)
			{
				return &(*itr);
			}
		}

		std::vector<std::shared_ptr<glwrap::ObjAnimation>> list = m_model->getAnimations();
		if (_id < list.size() && _id > -1)
		{
			m_values.push_back(AnimationValues());
			return &m_values.back();
		}
		return nullptr;
	}
}