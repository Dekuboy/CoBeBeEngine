#include <memory>
#include <list>
#include <SDL2/SDL.h>
#include <cobebe/NonCopyable.h>
#include <cobebe/Core/Entity.h>
#include <cobebe/Resources/Resources.h>
#include <glwrap/glwrap.h>
#include <AL/al.h>
#include <AL/alc.h>

namespace cobebe
{
	class Environment;
	class Transform;
	class Camera;
	class Lighting;
	class Canvas;
	class Keyboard;
	class Mouse;
	class Gamepad;
	class Shader;

	/**
	* \brief The Core of the engine
	* -to be instantiated once in main via Core::initialise
	* -manages game systems and entities
	* -use to: access access game systems
	*          add entities to game
	*          load assets into game
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
		* \brief Pass through the Core gameplay loop once
		*/
		void iterateCoreLoop();

		/**
		* \brief Use to stop the gameplay loop
		*/
		void stop();

		/**
		* \brief Adds Entity to the game loop
		*/
		std::shared_ptr<Entity> addEntity();

		/**
		* \brief Adds class inheriting Entity to the game loop
		*/
		template <class T, typename ... Args>
		std::shared_ptr<T> addEntity(Args&& ... _args)
		{
			// Initialise Entity before pushing to list
			std::shared_ptr<T> tempInheritor = std::make_shared<T>(std::forward<Args>(_args)...);
			std::shared_ptr<Entity> tempEntity = tempInheritor;
			std::shared_ptr<Transform> tempTransform = tempEntity->addComponent<Transform>();
			tempEntity->m_transform = tempTransform;
			tempEntity->m_self = tempEntity;
			tempEntity->m_core = m_self;
			m_entities.push_back(tempEntity);
			return tempEntity;
		}

		/**
		* \brief Returns first Entity with the input Component
		*/
		template <class T>
		std::shared_ptr<Entity> getEntityByComponent()
		{
			if (!m_entities.empty())
			{
				std::shared_ptr<T> cmp;

				for (std::list<std::shared_ptr<Entity> >::iterator it = m_entities.begin(); it != m_entities.end(); ++it)
				{
					cmp = (*it)->getComponent<T>();
					if (cmp)
					{
						return (*it);
					}
				}
			}
			return NULL;
		}
		/**
		* \brief Returns all entities with the input Component
		*/
		template <class T>
		std::list<std::shared_ptr<Entity> > getAllEntitiesByComponent()
		{
			std::list<std::shared_ptr<Entity> > rtn;

			if (!m_entities.empty())
			{
				std::shared_ptr<T> cmp;

				for (std::list<std::shared_ptr<Entity> >::iterator it = m_entities.begin(); it != m_entities.end(); ++it)
				{
					cmp = (*it)->getComponent<T>();
					if (cmp)
					{
						rtn.push_back(*it);
					}
				}
			}
			return rtn;
		}

		/**
		* \brief Gets the current gl Context
		*/
		std::shared_ptr<glwrap::Context> getGLContext();
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
		* \brief Returns Camera specified
		*/
		std::shared_ptr<Camera> getCamera();
		/**
		* \brief Returns the null shader for drawing RenderTextures
		*/
		std::shared_ptr<glwrap::ShaderProgram> getNullPassShader();
		/**
		* \brief
		*/
		std::shared_ptr<glwrap::ShaderProgram> getLightPassShader();
		/**
		* \brief Returns Lighting
		*/
		std::shared_ptr<Lighting> getLighting();
		/**
		* \brief Returns GUI Canvas
		*/
		std::shared_ptr<Canvas> getCanvas();

		/**
		* \brief Polls events and updates inputs
		*/
		void pollSDLEvent();
		/**
		* \brief Returns Keyboard inputs
		*/
		std::shared_ptr<Keyboard> getKeyboard();
		/**
		* \brief Returns Mouse inputs
		*/
		std::shared_ptr<Mouse> getMouse();
		/**
		* \brief Returns Gamepad inputs
		*/
		std::shared_ptr<Gamepad> getGamepad();
		/**
		* \brief Returns Environment inputs
		*/
		std::shared_ptr<Environment> getEnvironment();

		/**
		* \brief Returns Asset of file path
		*/
		template <class T, typename ... Args>
		std::shared_ptr<T> loadAsset(std::string _path, Args&& ... _args)
		{
			std::shared_ptr<T> asset = m_resources->load<T>
				(_path, std::forward<Args>(_args)...);
			return asset;
		}

	private:

		std::weak_ptr<Core> m_self; ///< Pointer to self to be placed in added entities

		SDL_Window* m_window; ///< Engine window
		std::shared_ptr<Shader> m_nullShader; ///< Draws RenderTexture
		std::shared_ptr<Shader> m_lightPassShader; ///< Draws deferred lighting

		ALCdevice* m_device; ///< Engine sound device
		ALCcontext* m_alContext; ///< Engine sound context

		std::shared_ptr<glwrap::Context> m_context; ///< Safely instantiates OpenGL objects
		std::list<std::shared_ptr<Entity> > m_entities; ///< List of entities in game loop
		std::list<std::shared_ptr<Camera> > m_cameras; ///< List of cameras in game loop
		std::weak_ptr<Camera> m_currentCamera; ///< Holds Camera currently drawing to the screen
		std::shared_ptr<Lighting> m_lighting; ///< Holds all variables regarding Lighting
		std::shared_ptr<Canvas> m_canvas; ///< Draws GUI to screen
		std::list<std::string> m_maskNames; ///< Masks to limit certain interactions

		std::shared_ptr<Keyboard> m_keyboard; ///< Holds keyboard inputs
		std::shared_ptr<Mouse> m_mouse; ///< Holds mouse inputs
		std::shared_ptr<Gamepad> m_gamepad; ///< Holds gamepad inputs

		std::shared_ptr<Environment> m_environment; ///< Holds deltaTime and window size

		std::shared_ptr<Resources> m_resources; ///< Holds loaded file paths

		bool m_running; ///< Controls the game loop
		bool m_inLoop; ///< Controls within single loop

		/**
		* \brief Passes current Cameras RenderTexture to screen
		*/
		void drawToScreen();
	};
}