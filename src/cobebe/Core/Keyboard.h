#include <vector>
#include <memory>
#include <SDL2/SDL.h>

namespace cobebeInput
{
	enum KeyboardKey
	{
		aKey = SDL_SCANCODE_A,
		bKey = SDL_SCANCODE_B,
		cKey = SDL_SCANCODE_C,
		dKey = SDL_SCANCODE_D,
		eKey = SDL_SCANCODE_E,
		fKey = SDL_SCANCODE_F,
		gKey = SDL_SCANCODE_G,
		hKey = SDL_SCANCODE_H,
		iKey = SDL_SCANCODE_I,
		jKey = SDL_SCANCODE_J,
		kKey = SDL_SCANCODE_K,
		lKey = SDL_SCANCODE_L,
		mKey = SDL_SCANCODE_M,
		nKey = SDL_SCANCODE_N,
		oKey = SDL_SCANCODE_O,
		pKey = SDL_SCANCODE_P,
		qKey = SDL_SCANCODE_Q,
		rKey = SDL_SCANCODE_R,
		sKey = SDL_SCANCODE_S,
		tKey = SDL_SCANCODE_T,
		uKey = SDL_SCANCODE_U,
		vKey = SDL_SCANCODE_V,
		wKey = SDL_SCANCODE_W,
		xKey = SDL_SCANCODE_X,
		yKey = SDL_SCANCODE_Y,
		zKey = SDL_SCANCODE_Z,
		enterKey = SDL_SCANCODE_RETURN,
		backspaceKey = SDL_SCANCODE_BACKSPACE,
		spaceKey = SDL_SCANCODE_SPACE,
		escKey = SDL_SCANCODE_ESCAPE
	};
}

namespace cobebe
{
	class Core;

	class Keyboard
	{
	public:
		bool isKey(int _key);
		bool isKeyPressed(int _key);
		bool isKeyReleased(int _key);

	private:
		friend class Core;

		const uint8_t* m_state;

		std::vector<int> m_keysPressed;
		std::vector<int> m_keysReleased;

		void onInit();
		void resetKeys();

	};
}