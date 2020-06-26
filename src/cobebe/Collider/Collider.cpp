#include <cobebe/Collider/Collider.h>

namespace cobebe
{
	bool Collider::checkColliding()
	{
		return m_hasCollided;
	}

	const std::list<std::weak_ptr<Entity>>& Collider::getColliders()
	{
		return m_colliders;
	}

	void Collider::onGUI()
	{
		m_hasCollided = false;
		m_colliders.clear();
	}
}