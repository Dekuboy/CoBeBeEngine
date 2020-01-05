#include <vector>
#include <SDL2/SDL.h>

#ifndef _COBEBE_GAMEPAD_LIMIT
#define _COBEBE_GAMEPAD_LIMIT 4
#endif

namespace cobebeInput
{
	enum GamepadButton
	{
		aButton = SDL_CONTROLLER_BUTTON_A,
		bButton,
		xButton,
		yButton,
		backButton,
		guideButton,
		startButton,
		leftStickButton,
		rightStickButton,
		leftShoulderButton,
		rightShoulderButton,
		upButton,
		downButton,
		leftButton,
		rightButton
	};

	enum GamepadAxis
	{
		leftXAxis,
		leftYAxis,
		rightXAxis,
		rightYAxis,
		leftTriggerAxis,
		rightTriggerAxis
	};
}

namespace cobebe
{
	class Core;

	class GamepadInputs
	{
	public:
		GamepadInputs();

	private:
		friend class Gamepad;
		std::vector<cobebeInput::GamepadButton> m_buttons;
		std::vector<cobebeInput::GamepadButton> m_buttonsPressed;
		std::vector<cobebeInput::GamepadButton> m_buttonsReleased;

		std::vector<int> m_axisValues;

		void resetButtons();

	};

	class Gamepad
	{
	public:
		Gamepad();
		~Gamepad();

		bool isButton(int _controllerId, cobebeInput::GamepadButton _button);
		bool isButtonPressed(int _controllerId, cobebeInput::GamepadButton _button);
		bool isButtonReleased(int _controllerId, cobebeInput::GamepadButton _button);

		int getAxis(int _controllerId, cobebeInput::GamepadAxis _axis);

	private:
		friend class Core;

		std::vector<SDL_GameController*> m_controllerHandles;

		std::vector<GamepadInputs> m_inputs;

		int getControllerId(Sint32 _gamepadId);

		void pressButton(int _controllerId, cobebeInput::GamepadButton _button);
		void releaseButton(int _controllerId, cobebeInput::GamepadButton _button);

		void setAxis(int _controllerId, cobebeInput::GamepadAxis _axis, int _value);

		void addController(Sint32 _gamepadId);
		void removeController(Sint32 _gamepadId);

		void resetButtons();

	};
}