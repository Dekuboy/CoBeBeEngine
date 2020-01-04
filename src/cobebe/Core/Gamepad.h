#include <vector>
#include <SDL2/SDL.h>

#ifndef _COBEBE_GAMEPAD_LIMIT
#define _COBEBE_GAMEPAD_LIMIT 4
#endif

namespace cobebe
{
	enum GamepadButton
	{
		aButton,
		bButton,
		xButton,
		yButton,
		back,
		guide,
		start,
		leftStick,
		rightStick,
		leftShoulder,
		rightShoulder,
		up,
		down,
		left,
		right
	};

	enum GamepadAxis
	{
		leftX,
		leftY,
		rightX,
		rightY,
		leftTrigger,
		rightTrigger
	};

	class Core;

	class GamepadInputs
	{
	public:
		GamepadInputs();

	private:
		friend class Gamepad;
		std::vector<GamepadButton> m_buttons;
		std::vector<GamepadButton> m_buttonsPressed;
		std::vector<GamepadButton> m_buttonsReleased;

		std::vector<int> m_axisValues;

		void resetButtons();

	};

	class Gamepad
	{
	public:
		Gamepad();
		~Gamepad();

		bool isButton(int _controllerId, GamepadButton _button);
		bool isButtonPressed(int _controllerId, GamepadButton _button);
		bool isButtonReleased(int _controllerId, GamepadButton _button);

		int getAxis(int _controllerId, GamepadAxis _axis);

	private:
		friend class Core;

		std::vector<SDL_GameController*> m_controllerHandles;

		std::vector<GamepadInputs> m_inputs;

		int getControllerId(Sint32 _gamepadId);

		void pressButton(int _controllerId, GamepadButton _button);
		void releaseButton(int _controllerId, GamepadButton _button);

		void setAxis(int _controllerId, GamepadAxis _axis, int _value);

		void addController(Sint32 _gamepadId);
		void removeController(Sint32 _gamepadId);

		void resetButtons();

	};
}