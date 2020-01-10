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

	void Entity::kill()
	{
		m_kill = true;
	}

	void Entity::tick()
	{
		for (std::list<std::shared_ptr<Component>>::iterator it = m_components.begin(); it != m_components.end(); ++it)
		{
			(*it)->onTick();
		}

		// Iterate through each Component and delete any marked as killed
		for (std::list<std::shared_ptr<Component>>::iterator it = m_components.begin(); it != m_components.end();)
		{
			if ((*it)->m_kill)
			{
				it = m_components.erase(it);
			}
			else
			{
				it++;
			}
		}
	}

	void Entity::preDisplay()
	{
		for (std::list<std::shared_ptr<Component>>::iterator it = m_components.begin(); it != m_components.end(); ++it)
		{
			(*it)->onPreDisplay();
		}
	}

	void Entity::display()
	{
		for (std::list<std::shared_ptr<Component>>::iterator it = m_components.begin(); it != m_components.end(); ++it)
		{
			(*it)->onDisplay();
		}
	}
	void Entity::postDisplay()
	{
		for (std::list<std::shared_ptr<Component>>::iterator it = m_components.begin(); it != m_components.end(); ++it)
		{
			(*it)->onPostDisplay();
		}
	}

	void Entity::gui()
	{
		for (std::list<std::shared_ptr<Component>>::iterator it = m_components.begin(); it != m_components.end(); ++it)
		{
			(*it)->onGUI();
		}
	}
}