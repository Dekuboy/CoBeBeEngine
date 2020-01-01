#include <cobebe/Core/Component.h>
#include <cobebe/Core/Entity.h>
#include <cobebe/Core/Core.h>

namespace cobebe
{
	Component::Component()
	{
		m_kill = false;
	}

	std::shared_ptr<Entity> Component::getEntity()
	{
		return m_entity.lock();
	}

	std::shared_ptr<Core> Component::getCore()
	{
		return m_entity.lock()->getCore();
	}

	std::shared_ptr<Keyboard> Component::getKeyboard()
	{
		return m_entity.lock()->getCore()->getKeyboard();
	}

	std::shared_ptr<Mouse> Component::getMouse()
	{
		return m_entity.lock()->getCore()->getMouse();
	}

	std::shared_ptr<Environment> Component::getEnvironment()
	{
		return m_entity.lock()->getCore()->getEnvironment();
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