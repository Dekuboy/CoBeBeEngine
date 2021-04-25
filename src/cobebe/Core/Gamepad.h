#include <vector>
#include <SDL2/SDL.h>

#ifndef _COBEBE_GAMEPAD_LIMIT
#define _COBEBE_GAMEPAD_LIMIT 4
#endif

namespace cobebeInput
{
	/** 
	* \brief Converts sdl input button to controller input button
	*/
	enum GamepadButton
	{
		aButton				= SDL_CONTROLLER_BUTTON_A,
		bButton				= SDL_CONTROLLER_BUTTON_B,
		xButton				= SDL_CONTROLLER_BUTTON_X,
		yButton				= SDL_CONTROLLER_BUTTON_Y,
		backButton			= SDL_CONTROLLER_BUTTON_BACK,
		guideButton			= SDL_CONTROLLER_BUTTON_GUIDE,
		startButton			= SDL_CONTROLLER_BUTTON_START,
		leftStickButton		= SDL_CONTROLLER_BUTTON_LEFTSTICK,
		rightStickButton	= SDL_CONTROLLER_BUTTON_RIGHTSTICK,
		leftShoulderButton	= SDL_CONTROLLER_BUTTON_LEFTSHOULDER,
		rightShoulderButton	= SDL_CONTROLLER_BUTTON_RIGHTSHOULDER,
		upButton			= SDL_CONTROLLER_BUTTON_DPAD_UP,
		downButton			= SDL_CONTROLLER_BUTTON_DPAD_DOWN,
		leftButton			= SDL_CONTROLLER_BUTTON_DPAD_LEFT,
		rightButton			= SDL_CONTROLLER_BUTTON_DPAD_RIGHT
	};

	/**
	* \brief Converts sdl input axis to controller input axis
	*/
	enum GamepadAxis
	{
		leftXAxis			= SDL_CONTROLLER_AXIS_LEFTX,
		leftYAxis			= SDL_CONTROLLER_AXIS_LEFTY,
		rightXAxis			= SDL_CONTROLLER_AXIS_RIGHTX,
		rightYAxis			= SDL_CONTROLLER_AXIS_RIGHTY,
		leftTriggerAxis		= SDL_CONTROLLER_AXIS_TRIGGERLEFT,
		rightTriggerAxis	= SDL_CONTROLLER_AXIS_TRIGGERRIGHT
	};
}

namespace cobebe
{
	class Core;

	/**
	* \brief Stores inputs for a controller
	*/
	class GamepadInputs
	{
	public:
		GamepadInputs();

	private:
		friend class Gamepad;
		std::vector<cobebeInput::GamepadButton> m_buttons; //!< Vector of buttons currently down
		std::vector<cobebeInput::GamepadButton> m_buttonsPressed; //!< Vector of buttons pressed on tick
		std::vector<cobebeInput::GamepadButton> m_buttonsReleased; //!< Vector of buttons released on tick

		std::vector<int> m_axisValues; //!< Vector of ints corresponding to axis values

		/**
		* \brief Clears pressed and released buttons
		*/
		void resetButtons();

	};

	/**
	* \brief Stores input values of _COBEBE_GAMEPAD_LIMIT (number of) Gamepads
	* -define _COBEBE_GAMEPAD_LIMIT before include to alter total Gamepad support
	*/
	class Gamepad
	{
	public:
		Gamepad();
		~Gamepad();

		/**
		* \brief Retrieves corresponding button input from input Gamepad
		*/
		bool isButton(int _controllerId, cobebeInput::GamepadButton _button);
		/**
		* \brief Retrieves corresponding button press from input Gamepad
		*/
		bool isButtonPressed(int _controllerId, cobebeInput::GamepadButton _button);
		/**
		* \brief Retrieves corresponding button release from input Gamepad
		*/
		bool isButtonReleased(int _controllerId, cobebeInput::GamepadButton _button);

		/**
		* \brief Retrieves corresponding axis value from input Gamepad
		*/
		int getAxis(int _controllerId, cobebeInput::GamepadAxis _axis);

	private:
		friend class Core;

		std::vector<SDL_GameController*> m_controllerHandles; //!< Currently attached game controllers

		std::vector<GamepadInputs> m_inputs; //!< Stored inputs for each Gamepad

		/**
		* \brief Retrieves corresponding controller Id if attached
		*/
		int getControllerId(Sint32 _gamepadId);

		/**
		* \brief Sets button as pressed on Gamepad
		*/
		void pressButton(int _controllerId, cobebeInput::GamepadButton _button);
		/**
		* \brief Sets button as released on Gamepad
		*/
		void releaseButton(int _controllerId, cobebeInput::GamepadButton _button);

		/**
		* \brief Sets axis value on Gamepad
		*/
		void setAxis(int _controllerId, cobebeInput::GamepadAxis _axis, int _value);

		/**
		* \brief Adds a Gamepad if available
		*/
		void addController(Sint32 _gamepadId);
		/**
		* \brief Removes a Gamepad if necessary
		*/
		void removeController(Sint32 _gamepadId);

		/**
		* \brief Clears pressed and released buttons on all Gamepads
		*/
		void resetButtons();

	};
}