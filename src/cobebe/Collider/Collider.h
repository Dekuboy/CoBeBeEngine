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
		Collider(int _mask);

		/**
		* \brief Set to collide with a specific mask
		*/
		void setMask(int _mask);
		/**
		* \brief Get mask list
		*/
		std::list<int>& getMasks();

		/**
		* \brief Returns true if collision has occured
		*/
		bool checkColliding();
		/**
		* \brief Return list of all collided Entities
		*/
		const std::list<std::weak_ptr<Entity>>& getColliders();

	protected:
		std::list<int> m_maskList; ///< Collision masks to limit collisions with objects

		bool m_hasCollided; ///< Has the object collided this tick?
		std::list<std::weak_ptr<Entity> > m_colliders; ///< List of collided entities

		/**
		* \brief Check for common masks
		*/
		bool checkMask(std::shared_ptr<Collider> _collider);

	private:
		virtual void onGUI();
	};
}
#endif