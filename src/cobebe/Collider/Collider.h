#ifndef _COBEBE_COLLIDER
#define _COBEBE_COLLIDER
#include <cobebe/Core/Component.h>
#include <list>

namespace cobebe
{
	class Collider : public Component
	{
	public:
		bool checkColliding();
		const std::list<std::shared_ptr<Entity>> getColliders();

	protected:
		bool m_hasCollided;
		std::list<std::shared_ptr<Entity>> m_colliders;

	private:
		void onGUI();
	};
}
#endif