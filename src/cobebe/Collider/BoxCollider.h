#include <cobebe/Collider/Collider.h>
#include <glm/glm.hpp>

namespace cobebe
{
	/**
	* \brief Simple AABB collider
	*/
	class BoxCollider : public Collider
	{
	public:
		BoxCollider();
		BoxCollider(int _mask);

		/**
		* \brief Gets the scale of the BoxCollider
		*/
		glm::vec3 getSize();
		/**
		* \brief Sets the scale of the BoxCollider
		*/
		void setSize(glm::vec3 _size);
		/**
		* \brief Sets the offest position from the origin(transform position)
		*/
		void setOffset(glm::vec3 _offset);
		/**
		* \brief Sets the Box to trigger and not interact
		*/
		void setTrigger(bool _switch);
		/**
		* \brief Sets the box to collide but not move
		*/
		void setStatic(bool _switch);

	private:
		glm::vec3 m_size; ///< Size of BozCollider
		glm::vec3 m_offset; ///< Position from the origin(transform position)
		bool m_isTrigger; ///< Does BoxCollider ghost
		bool m_isStatic; ///< Does BoxCollider stay still
		glm::vec3 m_lastPosition; ///< Stores last position in case of new position failure

		void collideBox(); ///< Checks collision with all entities with BoxCollider
		void collideStaticModel(); ///< Checks collision with all entities with StaticModelCollider

		/**
		* \brief Checks if box is colliding
		*/
		bool isColliding(glm::vec3 _position, glm::vec3 _size);
		/**
		* \brief Finds position where collision no onger occurs
		*/
		glm::vec3 getCollisionResponse(glm::vec3 _position, glm::vec3 _size);

		void onInit();
		void onTick();
	};
}