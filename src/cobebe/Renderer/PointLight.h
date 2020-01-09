#include <glm/glm.hpp>
#include <memory>
#include <vector>

namespace cobebe
{
	class Lighting;
	class Shader;

	class PointLight
	{
	public:
		PointLight();

		glm::vec3 m_position;

		glm::vec3 getColour();
		void setColour(glm::vec3 _lightCol);

		float getRadius();
		void setRadius(float _radius);

	private:
		friend class Lighting;
		glm::vec3 m_colour;
		float m_radius;
		std::vector<glm::mat4> m_lightSpaces;

	};
}