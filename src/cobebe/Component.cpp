#include "Component.h"
#include "Entity.h"

std::shared_ptr<Entity> Component::getEntity()
{
	return m_entity.lock();
}

std::shared_ptr<Core> Component::getCore()
{
	return m_entity.lock()->getCore();
}