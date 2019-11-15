#include <glm/glm.hpp>

namespace cobebe
{
	class Mouse
	{
	public:
		glm::vec2 getPosition();
		glm::vec2 getMovement();
	private:
		glm::vec2 m_position;
		glm::vec2 m_movement;
	};
}