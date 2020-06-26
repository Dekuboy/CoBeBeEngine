#include <glm/glm.hpp>
#include <memory>
#include <vector>
#include <SDL2/SDL.h>

namespace cobebeInput
{
	/**
	* \brief Converts sdl input button to mouse input button
	*/
	enum MouseButton
	{
		leftClick = SDL_BUTTON_LEFT,
		rightClick = SDL_BUTTON_RIGHT,
		middleClick = SDL_BUTTON_MIDDLE,
		extraClick1 = SDL_BUTTON_X1,
		extraClick2 = SDL_BUTTON_X2
	};
}

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
		* \brief Retrieves corresponding button input
		*/
		bool isButton(cobebeInput::MouseButton _button);
		/**
		* \brief Retrieves corresponding button press
		*/
		bool isButtonPressed(cobebeInput::MouseButton _button);
		/**
		* \brief Retrieves corresponding button release
		*/
		bool isButtonReleased(cobebeInput::MouseButton _button);

		/**
		* \brief Sets whether the mouse should warp to the screen centre
		*/
		void warpMouse(bool _switch);

		/**
		* \brief Creates ray shooting from the current camera through the mouse
		*/
		glm::vec3 getRayDirection();

	private:
		friend class Core;

		std::vector<cobebeInput::MouseButton> m_buttons; ///< Vector of buttons currently down
		std::vector<cobebeInput::MouseButton> m_buttonsPressed; ///< Vector of buttons pressed on tick
		std::vector<cobebeInput::MouseButton> m_buttonsReleased; ///< Vector of buttons released on tick

		glm::vec2 m_position; ///< Current mouse position on screen
		glm::vec2 m_movement; ///< Current mouse movement detected

		bool m_warpMouse; ///< Determine if mouse warps to centre

		std::weak_ptr<Core> m_core; ///< Pointer to Core for retrieving Environment class

		/**
		* \brief Sets button as pressed
		*/
		void pressButton(cobebeInput::MouseButton _button);
		/**
		* \brief Sets button as released
		*/
		void releaseButton(cobebeInput::MouseButton _button);
		/**
		* \brief Clears pressed and released buttons on all Gamepads
		*/
		void resetButtons();

	};
}