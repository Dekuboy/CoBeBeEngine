#include <cobebe/Renderer/GltfAnimationController.h>
#include <cobebe/Resources/RendAssets.h>
#include <cobebe/Exception.h>

namespace cobebe
{
	GltfAnimationController::GltfAnimationController(std::shared_ptr<glwrap::GltfModel> _model)
	{
		if (!_model)
		{
			throw Exception("NO MODEL ATTACHED TO ANIMATION CONTROLLER");
		}
		m_model = _model;
	}

	GltfAnimationController::~GltfAnimationController()
	{

	}

	void GltfAnimationController::setAnimationTime(int _id, float _time)
	{
		for (std::list<AnimationValues>::iterator itr = m_values.begin();
			itr != m_values.end();)
		{
			if (itr->m_id == _id)
			{
				std::shared_ptr<glwrap::ModelAnimation> ani = m_model->getAnimations().at(_id);
				ani->setRepeating(itr->m_repeating);
				ani->setCurrentFrame(_time);
				itr->m_time = ani->getCurrentFrame();
				return;
			}
		}
	}

	void GltfAnimationController::setToDraw()
	{
		m_model->disableAllAnimations();
		if (m_values.size() > 0)
		{
			std::vector<std::shared_ptr<glwrap::ModelAnimation> > animations = m_model->getAnimations();
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

	int GltfAnimationController::checkName(std::string& _name)
	{
		std::vector<std::shared_ptr<glwrap::ModelAnimation>> list = m_model->getAnimations();
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

	AnimationValues* GltfAnimationController::checkId(int _id)
	{
		for (std::list<AnimationValues>::iterator itr = m_values.begin();
			itr != m_values.end();)
		{
			if (itr->m_id == _id)
			{
				return &(*itr);
			}
		}

		std::vector<std::shared_ptr<glwrap::ModelAnimation>> list = m_model->getAnimations();
		if (_id < list.size() && _id > -1)
		{
			m_values.push_back(AnimationValues());
			return &m_values.back();
		}
		return nullptr;
	}
}