#include <cobebe/Core/Keyboard.h>
#include <cobebe/Core/Core.h>
#include <SDL2/SDL.h>

namespace cobebe
{
	bool Keyboard::isKey(int _key)
	{
		return m_state[_key];
	}

	bool Keyboard::isKeyPressed(int _key)
	{
		int size = m_keysPressed.size();
		int value;
		for (int i = 0; i < size; i++)
		{
			value = m_keysPressed.at(i);
			if (value == _key)
			{
				return true;
			}
		}
		return false;
	}

	bool Keyboard::isKeyReleased(int _key)
	{
		int size = m_keysReleased.size();
		int value;
		for (int i = 0; i < size; i++)
		{
			value = m_keysReleased.at(i);
			if (value == _key)
			{
				return true;
			}
		}
		return false;
	}

	void Keyboard::onInit()
	{
		m_state = SDL_GetKeyboardState(NULL);
	}

	void Keyboard::resetKeys()
	{
		m_keysPressed.clear();
		m_keysReleased.clear();
	}
}