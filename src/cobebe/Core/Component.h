#ifndef _ENTITY_COMPONENT
#define _ENTITY_COMPONENT
#include <memory>
#include <cobebe/NonCopyable.h>

namespace cobebe
{
	class Core;
	class Entity;
	class Keyboard;
	class Mouse;
	class Environment;

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
		virtual ~Component() {}

		/**
		* \brief Retrieve attached entity
		*/
		std::shared_ptr<Entity> getEntity();
		/**
		* \brief Retrieve engine core
		*/
		std::shared_ptr<Core> getCore();
		/**
		* \brief Retrieve keyboard inputs
		*/
		std::shared_ptr<Keyboard> getKeyboard();
		/**
		* \brief Retrieve mouse inputs
		*/
		std::shared_ptr<Mouse> getMouse();
		/**
		* \brief Retrieve engine environment
		*/
		std::shared_ptr<Environment> getEnvironment();

	private:
		friend class Entity;

		std::weak_ptr<Entity> m_entity; ///< Pointer to entity to

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