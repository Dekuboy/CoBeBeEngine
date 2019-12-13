#include <memory>
#include <list>
#include <SDL2/SDL.h>
#include <cobebe/NonCopyable.h>

namespace cobebe
{
	class Environment;
	class Entity;
	class Camera;
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
		std::weak_ptr<Core> m_self;

		SDL_Window *m_window;
		//std::shared_ptr<Context> m_context;
		std::list<std::shared_ptr<Entity>> m_entities;
		std::weak_ptr<Camera> m_currentCamera;
		std::shared_ptr<Environment> m_environment;
		std::shared_ptr<Keyboard> m_keyboard;
		std::shared_ptr<Mouse> m_mouse;

		std::shared_ptr<Resources> m_resources;

		bool running;
	};
}