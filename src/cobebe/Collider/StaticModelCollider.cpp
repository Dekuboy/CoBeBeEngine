#include <cobebe/Collider/StaticModelCollider.h>

namespace cobebe
{
	glm::vec3 StaticModelCollider::getCollisionResponse(glm::vec3 _position,
		glm::vec3 _size, bool& _solved)
	{
		return glm::vec3(0);
	}
}