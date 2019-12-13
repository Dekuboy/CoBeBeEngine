#include "Component.h"
#include "glm/glm.hpp"

namespace cobebe
{
	class Transform : public Entity
	{
	public:
		glm::mat4 getModel();

	private:
		glm::vec3 m_poisition;
		glm::mat4 m_rotation;
		glm::vec3 m_scale;

	};
}