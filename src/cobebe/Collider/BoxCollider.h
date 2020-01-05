#include <cobebe/Collider/Collider.h>
#include <glm/glm.hpp>

namespace cobebe
{
	class BoxCollider : public Collider
	{
	public:
		void setSize(glm::vec3 _size);
		void setOffset(glm::vec3 _offset);
		void setTrigger(bool _switch);
		void setStatic(bool _switch);

	private:
		glm::vec3 m_size;
		glm::vec3 m_offset;
		bool m_isTrigger;
		bool m_isStatic;
		glm::vec3 m_lastPosition;

		void collideBox();
		void collideStaticModel();

		bool isColliding(glm::vec3 _position, glm::vec3 _size);
		glm::vec3 getCollisionResponse(glm::vec3 _position, glm::vec3 _size);

		void onInit();
		void onTick();
	};
}