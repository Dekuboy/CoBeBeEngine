#ifndef _COBEBE_COMPONENT
#define _COBEBE_COMPONENT
#include <memory>
#include <cobebe/NonCopyable.h>

namespace cobebe
{
	class Core;
	class Entity;
	class Transform;
	class Keyboard;
	class Mouse;
	class Gamepad;
	class Environment;
	class Resources;

	/**
	* Parent class ready to attach to an Entity
	* -provides virtual void functions:
	* --onInit();
	* --onTick();
	* --onPreDisplay();
	* --onDisplay();
	* --onPostDisplay();
	* --onGUI();
	*/
	class Component : private NonCopyable
	{
	public:
		Component();
		virtual ~Component() {}

		/**
		* \brief Retrieve attached Entity
		*/
		std::shared_ptr<Entity> getEntity();
		/**
		* \brief Retrieve Transform component attached to Entity
		*/
		std::shared_ptr<Transform> getTransform();
		/**
		* \brief Retrieve engine Core
		*/
		std::shared_ptr<Core> getCore();
		/**
		* \brief Retrieve Keyboard inputs
		*/
		std::shared_ptr<Keyboard> getKeyboard();
		/**
		* \brief Retrieve Mouse inputs
		*/
		std::shared_ptr<Mouse> getMouse();
		/**
		* \brief Retrieve Gamepad inputs
		*/
		std::shared_ptr<Gamepad> getGamepad();
		/**
		* \brief Retrieve engine Environment
		*/
		std::shared_ptr<Environment> getEnvironment();

	private:
		friend class Entity;
		bool m_kill; /// Marks Component for destruction

		std::weak_ptr<Entity> m_entity; ///< Pointer to entity

		/**
		* \brief Activates when added to Entity
		*/
		virtual void onInit();
		/**
		* \brief Activates once per frame
		*/
		virtual void onTick();
		/**
		* \brief Activates before being drawn to screen
		*/
		virtual void onPreDisplay();
		/**
		* \brief Activates once drawing to screen
		*/
		virtual void onDisplay();
		/**
		* \brief Activates after drawing to screen
		*/
		virtual void onPostDisplay();
		/**
		* \brief Activates when the GUI is drawn to screen
		*/
		virtual void onGUI();
	};
}
#endif