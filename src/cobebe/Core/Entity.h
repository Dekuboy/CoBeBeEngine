#include <memory>
#include <list>
#include <cobebe/Exception.h>

namespace cobebe
{
	class Core;
	class Component;
	class Transform;

	class Entity
	{
	public:
		virtual ~Entity() {}

		const std::shared_ptr<Core> getCore();

		template <class T>
		std::shared_ptr<T> addComponent()
		{
			std::shared_ptr<T> comp = std::make_shared<T>();
			comp->onInit();
			m_components.push_back(comp);
			return comp;
		}

		template <class T, class A>
		std::shared_ptr<T> addComponent(A _a)
		{
			std::shared_ptr<T> comp = std::make_shared<T>(_a);
			comp->onInit();
			m_components.push_back(comp);
			return comp;
		}

		template <class T, class A, class B>
		std::shared_ptr<T> addComponent(A _a, B _b)
		{
			std::shared_ptr<T> comp = std::make_shared<T>(_a, _b);
			comp->onInit();
			m_components.push_back(comp);
			return comp;
		}

		template <class T, class A, class B, class C>
		std::shared_ptr<T> addComponent(A _a, B _b, C _c)
		{
			std::shared_ptr<T> comp = std::make_shared<T>(_a, _b, _c);
			comp->onInit();
			m_components.push_back(comp);
			return comp;
		}

		template <class T>
		std::shared_ptr<T> getComponent()
		{
			std::shared_ptr<T> cmp;

			for (std::list<std::shared_ptr<Component>>::iterator it = m_entities.begin(); it != m_entities.end(); ++it)
			{
				cmp = std::dynamic_pointer_cast<std::shared_ptr<T>>(*it);
				if (cmp)
				{
					return cmp;
				}
			}

			throw Exception("Component not found");
		}

	private:
		friend class Core;
		std::list<std::shared_ptr<Component>> m_components;
		std::weak_ptr<Core> m_core;
		std::weak_ptr<Entity> m_self;
		std::weak_ptr<Transform> m_transform;

		void tick();
		void display();

	};
}