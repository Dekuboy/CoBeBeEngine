#include <glwrap/glwrap.h>
#include <glm/glm.hpp>
#include <memory>
#include <vector>

namespace cobebe
{
	class Lighting;
	class Shader;
	class Core;

	class PointLight
	{
	public:
		PointLight();

		glm::vec3 getPosition();
		void setPosition(glm::vec3 _position);

		glm::vec3 getColour();
		void setColour(glm::vec3 _lightCol);

		float getRadius();
		void setRadius(float _radius);

	private:
		friend class Lighting;
		glm::vec3 m_position;
		glm::vec3 m_colour;
		float m_radius;
		std::vector<glm::mat4> m_lightSpaces;

		std::shared_ptr<glwrap::DepthCube> m_depthCube;

		std::weak_ptr<Core> m_core;

	};
}