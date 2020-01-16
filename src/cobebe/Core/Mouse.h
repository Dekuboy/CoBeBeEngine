#include <glm/glm.hpp>

namespace cobebe
{
	class Core;

	/**
	* \brief Stores input values from the mouse
	*/
	class Mouse
	{
	public:
		Mouse();

		/**
		* \brief Retrieves current mouse position
		*/
		glm::vec2 getPosition();
		/**
		* \brief Retrieves current mouse movement
		*/
		glm::vec2 getMovement();

		/**
		* \brief Sets whether the mouse should warp to the screen centre
		*/
		void warpMouse(bool _switch);

	private:
		friend class Core;

		glm::vec2 m_position; ///< Current mouse position on screen
		glm::vec2 m_movement; ///< Current mouse movement detected

		bool m_warpMouse; ///< Determine if mouse warps to centre

	};
}