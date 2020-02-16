#include <memory>
#include <list>
#include <cobebe/Exception.h>

namespace cobebe
{
	class Core;
	class Component;
	class Transform;

	/**
	* \brief Represents an object in the game loop
	*/
	class Entity
	{
	public:
		Entity();
		virtual ~Entity() {}

		/**
		* \brief Returns pointer to Core
		*/
		const std::shared_ptr<Core> getCore();

		/**
		* \brief Adds Component of type to Entity
		*/
		template <class T>
		std::shared_ptr<T> addComponent()
		{
			std::shared_ptr<T> comp = std::make_shared<T>();
			comp->m_entity = m_self;
			std::shared_ptr<Component> compCast = comp;
			compCast->onInit();
			m_components.push_back(comp);
			return comp;
		}

		/**
		* \brief Adds Component of type to Entity using parameters
		*/
		template <class T, class A>
		std::shared_ptr<T> addComponent(A _a)
		{
			std::shared_ptr<T> comp = std::make_shared<T>(_a);
			comp->m_entity = m_self;
			std::shared_ptr<Component> compCast = comp;
			compCast->onInit();
			m_components.push_back(comp);
			return comp;
		}

		/**
		* \brief Adds Component of type to Entity using parameters
		*/
		template <class T, class A, class B>
		std::shared_ptr<T> addComponent(A _a, B _b)
		{
			std::shared_ptr<T> comp = std::make_shared<T>(_a, _b);
			comp->m_entity = m_self;
			std::shared_ptr<Component> compCast = comp;
			compCast->onInit();
			m_components.push_back(comp);
			return comp;
		}

		/**
		* \brief Adds Component of type to Entity using parameters
		*/
		template <class T, class A, class B, class C>
		std::shared_ptr<T> addComponent(A _a, B _b, C _c)
		{
			std::shared_ptr<T> comp = std::make_shared<T>(_a, _b, _c);
			comp->m_entity = m_self;
			std::shared_ptr<Component> compCast = comp;
			compCast->onInit();
			m_components.push_back(comp);
			return comp;
		}

		/**
		* \brief Adds Component of type to Entity using parameters
		*/
		template <class T>
		std::shared_ptr<T> getComponent()
		{
			std::shared_ptr<T> cmp;

			for (std::list<std::shared_ptr<Component>>::iterator it = m_components.begin(); it != m_components.end(); ++it)
			{
				cmp = std::dynamic_pointer_cast<T>(*it);
				if (cmp)
				{
					return cmp;
				}
			}
			return NULL;
		}

		/**
		* \brief Removes first Component of type from Entity
		*/
		template <class T>
		void removeComponent()
		{
			std::shared_ptr<T> cmp;

			cmp = std::dynamic_pointer_cast<T>(m_transform.lock());
			if (!cmp)
			{
				for (std::list<std::shared_ptr<Component>>::iterator it = m_components.begin(); it != m_components.end(); it++)
				{
					cmp = std::dynamic_pointer_cast<T>(*it);
					if (cmp)
					{
						(*it)->m_kill = true;
						return;
					}
				}

				throw Exception("Component not found");
			}
			else
			{
				throw Exception("Cannot remove Transform component");
			}
		}

		/**
		* \brief Removes Component passed in from Entity
		*/
		template <class T>
		void removeComponent(std::shared_ptr<T> _removeCmp)
		{
			std::shared_ptr<T> cmp;

			cmp = std::dynamic_pointer_cast<T>(m_transform.lock());
			if (!cmp)
			{
				for (std::list<std::shared_ptr<Component>>::iterator it = m_components.begin(); it != m_components.end(); it++)
				{
					cmp = std::dynamic_pointer_cast<T>(*it);
					if (cmp)
					{
						if (_removeCmp == cmp)
						{
							(*it)->m_kill = true;
							return;
						}
					}
				}

				throw Exception("Component not found");
			}
			else
			{
				throw Exception("Cannot remove Transform component");
			}
		}

		/**
		* \brief Returns pointer to Transform component
		*/
		std::shared_ptr<Transform> getTransform();

		/**
		* \brief Kills the entity
		*/
		void kill();

	private:
		friend class Core;
		bool m_kill; ///< Marks Entity for destruction

		std::list<std::shared_ptr<Component>> m_components; ///< List of components attached to entity
		std::weak_ptr<Core> m_core; ///< Pointer to games Core
		std::weak_ptr<Entity> m_self; ///< Pointer to self to be placed in attached components
		std::weak_ptr<Transform> m_transform; ///< Pointer to attached Transform Component

		/**
		* \brief Initialise the Entity when created by the Core
		*/
		virtual void init();

		/**
		* \brief Calls on all components once per frame
		*/
		void tick();
		/**
		* \brief Calls on all components before displaying to screen
		*/
		void preDisplay();
		/**
		* \brief Calls on all components once displaying to screen
		*/
		void display();
		/**
		* \brief Calls on all components after displaying to screen
		*/
		void postDisplay();
		/**
		* \brief Calls on all components when the GUI is drawn to screen
		*/
		void gui();
	};
}