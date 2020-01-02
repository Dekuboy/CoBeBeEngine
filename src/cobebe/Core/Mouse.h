#include <glm/glm.hpp>

namespace cobebe
{
	class Core;

	class Mouse
	{
	public:
		Mouse();

		glm::vec2 getPosition();
		glm::vec2 getMovement();

		void warpMouse(bool _switch);

	private:
		friend class Core;

		glm::vec2 m_position;
		glm::vec2 m_movement;

		bool m_warpMouse;

	};
}