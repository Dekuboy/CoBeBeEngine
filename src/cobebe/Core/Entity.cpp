#include "Entity.h"
#include "Component.h"

namespace cobebe
{
	const std::shared_ptr<Core> Entity::getCore()
	{
		return m_core.lock();
	}

	void Entity::tick()
	{
		for (std::list<std::shared_ptr<Component>>::iterator it = m_components.begin(); it != m_components.end(); ++it)
		{
			(*it)->onTick();
		}
	}

	void Entity::display()
	{
		for (std::list<std::shared_ptr<Component>>::iterator it = m_components.begin(); it != m_components.end(); ++it)
		{
			(*it)->onDisplay();
		}
	}
}