#ifndef _COBEBE_COLLIDER
#define _COBEBE_COLLIDER
#include <cobebe/Core/Component.h>
#include <list>

namespace cobebe
{
	/**
	* \brief Collider parent store entities collided with
	*/
	class Collider : public Component
	{
	public:
		/**
		* \brief Returns true if collision has occured
		*/
		bool checkColliding();
		/**
		* \brief return list of all collided 
		*/
		const std::list<std::shared_ptr<Entity>> getColliders();

	protected:
		bool m_hasCollided; /// Has the object collided this tick?
		std::list<std::shared_ptr<Entity>> m_colliders; /// List of collided entities

	private:
		virtual void onGUI();
	};
}
#endif