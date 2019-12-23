#include <cobebe/Core/Component.h>
#include <glm/glm.hpp>

namespace cobebe
{
	class Transform : public Component
	{
	public:
		Transform();

		glm::vec3 m_position;
		glm::mat3 m_rotation;
		glm::vec3 m_scale;

		glm::mat4 getModel();

	private:
		glm::mat4 m_model;
		void onPreDisplay();

	};
}