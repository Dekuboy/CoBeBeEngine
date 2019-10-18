#include "Entity.h"

const std::shared_ptr<Core> Entity::getCore()
{
	return m_core.lock();
}

void Entity::tick()
{

}

void Entity::display()
{

}