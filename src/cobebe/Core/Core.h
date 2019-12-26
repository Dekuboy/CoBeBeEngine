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

	/**
	* The Core of the engine
	* -to be instantiated once in main via Core::initialise
	* -manages game systems and entities
	* -use to access access game systems
	* -use to add entities to game
	*/
	class Core : private NonCopyable
	{
	public:
		Core();
		~Core();

		/**
		* \brief Use to instantiate Core class
		*/
		static const std::shared_ptr<Core> initialise();

		/**
		* \brief Use to run the Core gameplay loop
		*/
		void run();

		/**
		* \brief Use to stop the gameplay loop
		*/
		void stop();

		/**
		* \brief Adds entity to the game loop
		*/
		std::shared_ptr<Entity> addEntity();

		/**
		* \brief Returns first entity with the input Component
		*/
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

		/**
		* \brief Adds Camera to list using screen size for the RenderTexture
		*/
		std::shared_ptr<Camera> addCamera();
		/**
		* \brief Adds Camera to list using input size for the RenderTexture
		*/
		std::shared_ptr<Camera> addCamera(int _renderWidth, int _renderHeight);
		/**
		* \brief Returns the Camera currently drawing to screen
		*/
		std::shared_ptr<Camera> getCurrentCamera();
		/**
		* \brief Gets Camera specified
		*/
		std::shared_ptr<Camera> getCamera();

		/**
		* \brief Returns Asset of file path
		*/
		template <class T>
		std::shared_ptr<T> loadAsset(std::string _path)
		{
			std::shared_ptr<T> asset = m_resources->load<T>(_path);
			return asset;
		}

	private:
		std::weak_ptr<Core> m_self; /// Pointer to self to be placed in added entities

		SDL_Window *m_window;
		std::shared_ptr<glwrap::ShaderProgram> m_nullShader; /// Draws RenderTexture

		std::shared_ptr<glwrap::Context> m_context; /// Safely instantiates OpenGL objects
		std::list<std::shared_ptr<Entity>> m_entities; /// List of entities in game loop
		std::list<std::shared_ptr<Camera>> m_cameras; /// List of cameras in game loop
		std::weak_ptr<Camera> m_currentCamera; /// Holds Camera currently drawing to the screen
		std::shared_ptr<Environment> m_environment; /// Holds deltaTime and window size
		std::shared_ptr<Keyboard> m_keyboard; /// Holds keyboard inputs
		std::shared_ptr<Mouse> m_mouse; /// Holds mouse inputs

		std::shared_ptr<Resources> m_resources; /// Holds loaded file paths

		bool m_running; /// Controls the game loop
	};
}