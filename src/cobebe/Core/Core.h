#include <memory>
#include <list>
#include <SDL2/SDL.h>
#include <cobebe/NonCopyable.h>
#include <glwrap/glwrap.h>

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

		template <class T>
		std::shared_ptr<Entity> getEntityByComponent()
		{
			std::shared_ptr<T> cmp

			for (std::list<std::shared_ptr<Entity>>::iterator it = m_entities.begin(); it != m_entities.end(); ++it)
			{
				try
				{
					cmp = (*it)->getComponent<T>();
					if (cmp)
					{
						return (*it);
					}
				}
				catch (const Exception& e)
				{

				}
			}
			return NULL;
		}

		std::shared_ptr<Camera> addCamera();
		std::shared_ptr<Camera> addCamera(int _renderWidth, int _renderHeight);
		std::shared_ptr<Camera> getCurrentCamera();
		std::shared_ptr<Camera> getCamera(int _id);

		template <class T>
		std::shared_ptr<T> loadAsset(std::string _path)
		{
			std::shared_ptr<T> asset = m_resources->load<T>(_path);
			return asset;
		}

	private:
		std::weak_ptr<Core> m_self;

		SDL_Window *m_window;
		std::shared_ptr<glwrap::ShaderProgram> m_nullShader;

		std::shared_ptr<glwrap::Context> m_context;
		std::list<std::shared_ptr<Entity>> m_entities;
		std::list<std::shared_ptr<Camera>> m_cameras;
		std::weak_ptr<Camera> m_currentCamera;
		std::shared_ptr<Environment> m_environment;
		std::shared_ptr<Keyboard> m_keyboard;
		std::shared_ptr<Mouse> m_mouse;

		std::shared_ptr<Resources> m_resources;

		bool running;
	};
}