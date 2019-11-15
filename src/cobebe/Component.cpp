#include "Component.h"
#include "Entity.h"

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

	void Component::onBegin()
	{

	}

	void Component::onTick()
	{

	}

	void Component::onDisplay()
	{

	}
}