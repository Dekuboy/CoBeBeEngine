#include <glm/glm.hpp>

namespace cobebe
{
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
		glm::vec3 m_colour;
		float m_radius;

	};
}