#include <memory>
#include <list>
#include <SDL2/SDL.h>
#include <rend/rend.h>
#include "NonCopyable.h"

namespace cobebe
{
	class Environment;
	class Entity;
	class Keyboard;
	class Mouse;
	class Resources;

	class Core : private NonCopyable
	{
	public:
		Core();
		~Core();

		static const std::shared_ptr<Core> initialise();

		void run();

		void stop();

		std::shared_ptr<Entity> addEntity();

	private:

		SDL_Window *m_window;
		std::shared_ptr<rend::Context> m_context;
		std::list<std::shared_ptr<Entity>> m_entities;
		std::shared_ptr<Environment> m_environment;
		std::shared_ptr<Keyboard> m_keyboard;
		std::shared_ptr<Mouse> m_mouse;

		bool running;
	};
}