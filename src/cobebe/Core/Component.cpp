#include <cobebe/Core/Component.h>
#include <cobebe/Core/Entity.h>

namespace cobebe
{
	std::shared_ptr<Entity> Component::getEntity()
	{
		return m_entity.lock();
	}

	std::shared_ptr<Core> Component::getCore()
	{
		return m_entity.lock()->getCore();
	}

	void Component::onInit()
	{

	}

	void Component::onTick()
	{

	}

	void Component::onPreDisplay()
	{

	}

	void Component::onDisplay()
	{

	}

	void Component::onPostDisplay()
	{

	}

	void Component::onGUI()
	{

	}
}