#include <cobebe/Collider/Collider.h>
#include <glm/glm.hpp>

namespace cobebe
{
	class StaticModelCollider
	{
	public:
		glm::vec3 getCollisionResponse(glm::vec3 _position,
			glm::vec3 _size, bool& _solved);

	private:

	};
}