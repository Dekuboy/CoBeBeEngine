#include <cobebe/Core/Entity.h>
#include <cobebe/Core/Component.h>

namespace cobebe
{
	Entity::Entity()
	{
		m_kill = false;
	}

	const std::shared_ptr<Core> Entity::getCore()
	{
		return m_core.lock();
	}

	std::shared_ptr<Transform> Entity::getTransform()
	{
		return m_transform.lock();
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