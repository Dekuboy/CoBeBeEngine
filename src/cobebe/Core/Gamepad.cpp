#include <cobebe/Core/Gamepad.h>

namespace cobebe
{
	GamepadInputs::GamepadInputs()
	{
		for (int i = 0; i < 6; i++)
		{
			m_axisValues.push_back(0);
		}
	}

	void GamepadInputs::resetButtons()
	{
		m_buttonsPressed.clear();
		m_buttonsReleased.clear();
	}

	Gamepad::Gamepad()
	{
		for (int i = 0; i < _COBEBE_GAMEPAD_LIMIT; i++)
		{
			m_inputs.push_back(GamepadInputs());
			m_controllerHandles.push_back(NULL);
		}
	}

	Gamepad::~Gamepad()
	{
		for (int controllerIndex = 0; controllerIndex < _COBEBE_GAMEPAD_LIMIT; ++controllerIndex)
		{
			if (m_controllerHandles.at(controllerIndex))
			{
				SDL_GameControllerClose(m_controllerHandles.at(controllerIndex));
			}
		}
	}

	bool Gamepad::isButton(int _controllerId, cobebeInput::GamepadButton _button)
	{
		if (_controllerId >= 0 && _controllerId < _COBEBE_GAMEPAD_LIMIT)
		{
			GamepadInputs * controller = &m_inputs.at(_controllerId);
			int size = controller->m_buttons.size();
			for (int i = 0; i < size; i++)
			{
				if (controller->m_buttons.at(i) == _button)
				{
					return true;
				}
			}
		}
		return false;
	}

	bool Gamepad::isButtonPressed(int _controllerId, cobebeInput::GamepadButton _button)
	{
		if (_controllerId >= 0 && _controllerId < _COBEBE_GAMEPAD_LIMIT)
		{
			GamepadInputs * controller = &m_inputs.at(_controllerId);
			int size = controller->m_buttonsPressed.size();
			for (int i = 0; i < size; i++)
			{
				if (controller->m_buttonsPressed.at(i) == _button)
				{
					return true;
				}
			}
		}
		return false;
	}

	bool Gamepad::isButtonReleased(int _controllerId, cobebeInput::GamepadButton _button)
	{
		if (_controllerId >= 0 && _controllerId < _COBEBE_GAMEPAD_LIMIT)
		{
			GamepadInputs * controller = &m_inputs.at(_controllerId);
			int size = controller->m_buttonsReleased.size();
			for (int i = 0; i < size; i++)
			{
				if (controller->m_buttonsReleased.at(i) == _button)
				{
					return true;
				}
			}
		}
		return false;
	}

	int Gamepad::getAxis(int _controllerId, cobebeInput::GamepadAxis _axis)
	{
		if (_controllerId >= 0 && _controllerId < _COBEBE_GAMEPAD_LIMIT)
		{
			GamepadInputs * controller = &m_inputs.at(_controllerId);
			return controller->m_axisValues.at(_axis);
		}
		return 0;
	}

	int Gamepad::getControllerId(Sint32 _gamepadId)
	{
		for (int i = 0; i < _COBEBE_GAMEPAD_LIMIT; i++)
		{
			if (_gamepadId == SDL_JoystickInstanceID(SDL_GameControllerGetJoystick(m_controllerHandles.at(i))))
			{
				return i;
			}
		}
		return -1;
	}

	void Gamepad::pressButton(int _controllerId, cobebeInput::GamepadButton _button)
	{
		if (_controllerId >= 0 && _controllerId < _COBEBE_GAMEPAD_LIMIT)
		{
			GamepadInputs * controller = &m_inputs.at(_controllerId);
			controller->m_buttons.push_back(_button);
			controller->m_buttonsPressed.push_back(_button);
		}
	}

	void Gamepad::releaseButton(int _controllerId, cobebeInput::GamepadButton _button)
	{
		if (_controllerId >= 0 && _controllerId < _COBEBE_GAMEPAD_LIMIT)
		{
			GamepadInputs * controller = &m_inputs.at(_controllerId);
			controller->m_buttonsReleased.push_back(_button);

			int size = controller->m_buttons.size();
			for (std::vector<cobebeInput::GamepadButton>::iterator it =
				controller->m_buttons.begin(); it != controller->m_buttons.end();)
			{
				if ((*it) == _button)
				{
					it = controller->m_buttons.erase(it);
				}
				else
				{
					it++;
				}
			}
		}
	}

	void Gamepad::setAxis(int _controllerId, cobebeInput::GamepadAxis _axis, int _value)
	{
		if (_controllerId >= 0 && _controllerId < _COBEBE_GAMEPAD_LIMIT)
		{
			GamepadInputs * controller = &m_inputs.at(_controllerId);
			controller->m_axisValues.at(_axis) = _value;
		}
	}

	void Gamepad::addController(Sint32 _gamepadId)
	{
		if (!SDL_IsGameController(_gamepadId))
		{
			return;
		}
		else
		{
			for (int i = 0; i < _COBEBE_GAMEPAD_LIMIT; i++)
			{
				if (m_controllerHandles.at(i) == NULL)
				{
					m_controllerHandles.at(i) = SDL_GameControllerOpen(_gamepadId);
					return;
				}
			}
		}
	}

	void Gamepad::removeController(Sint32 _gamepadId)
	{
		for (int i = 0; i < _COBEBE_GAMEPAD_LIMIT; i++)
		{
			if (_gamepadId == SDL_JoystickInstanceID(SDL_GameControllerGetJoystick(m_controllerHandles.at(i))))
			{
				SDL_GameControllerClose(m_controllerHandles.at(i));
				m_controllerHandles.at(i) = NULL;
				m_inputs.at(i) = GamepadInputs();
				return;
			}
		}
	}

	void Gamepad::resetButtons()
	{
		for (int i = 0; i < _COBEBE_GAMEPAD_LIMIT; i++)
		{
			m_inputs.at(i).resetButtons();
		}
	}
}