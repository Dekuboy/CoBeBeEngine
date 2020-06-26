#include <cobebe/Collider/BoxCollider.h>
#include <cobebe/Collider/StaticModelCollider.h>
#include <cobebe/Core/Core.h>
#include <cobebe/Core/Transform.h>
#include <cobebe/Core/Entity.h>

namespace cobebe
{
	glm::vec3 BoxCollider::getSize()
	{
		return m_size;
	}

	void BoxCollider::setSize(glm::vec3 _size)
	{
		m_size = _size;
	}

	void BoxCollider::setOffset(glm::vec3 _offset)
	{
		m_offset = _offset;
	}

	void BoxCollider::setTrigger(bool _switch)
	{
		m_isTrigger = _switch;
	}

	void BoxCollider::setStatic(bool _switch)
	{
		m_isStatic = _switch;
	}

	void BoxCollider::collideBox()
	{
		std::list<std::shared_ptr<Entity>> boxEntities;
		boxEntities = getCore()->getAllEntitiesByComponent<BoxCollider>();
		std::shared_ptr<BoxCollider> bc;

		glm::vec3 np = getTransform()->m_position + m_offset;
		glm::vec3 sp;

		for (std::list<std::shared_ptr<Entity>>::iterator it = boxEntities.begin();
			it != boxEntities.end(); it++)
		{
			if (*it == getEntity())
			{
				continue;
			}

			bc = (*it)->getComponent<BoxCollider>();

			if (!m_isTrigger && !m_isStatic)
			{
				sp = bc->getCollisionResponse(np, m_size);
				if (np != sp)
				{
					m_hasCollided = true;
					m_colliders.push_back(*it);
					np = sp;
					np = np - m_offset;
					getTransform()->m_position = (np);
					m_lastPosition = np;
				}
			}
			else
			{
				if (bc->isColliding(np, m_size))
				{
					m_hasCollided = true;
					m_colliders.push_back(*it);
				}
			}
		}
	}

	void BoxCollider::collideStaticModel()
	{
		std::list<std::shared_ptr<Entity>> smces;

		smces = getCore()->getAllEntitiesByComponent<StaticModelCollider>();

		glm::vec3 np = getTransform()->m_position + m_offset;

		for (std::list<std::shared_ptr<Entity>>::iterator it = smces.begin();
			it != smces.end(); it++)
		{
			std::shared_ptr<StaticModelCollider> smc =
				(*it)->getComponent<StaticModelCollider>();

			bool solved = false;
			glm::vec3 sp = smc->getCollisionResponse(np, m_size, solved);

			if (solved)
			{
				np = sp;
			}
			else
			{
				np = m_lastPosition + m_offset;
			}
			if (np != np)
			{
				np = m_lastPosition + m_offset;
			}
			np = np - m_offset;
			getTransform()->m_position = np;
			m_lastPosition = np;
		}
	}

	bool BoxCollider::isColliding(glm::vec3 _position, glm::vec3 _size)
	{
		glm::vec3 a = getTransform()->m_position + m_offset;
		glm::vec3& as = m_size;
		glm::vec3& b = _position;
		glm::vec3& bs = _size;

		if (a.x > b.x) // a right of b
		{
			if (a.x - as.x > b.x + bs.x) // left edge of a greater than right edge of b (not colliding)
			{
				return false;
			}
		}
		else
		{
			if (b.x - bs.x > a.x + as.x)
			{
				return false;
			}
		}

		if (a.z > b.z) // a front of b
		{
			if (a.z - as.z > b.z + bs.z) // back edge of a greater than front edge of b (not colliding)
			{
				return false;
			}
		}
		else
		{
			if (b.z - bs.z > a.z + as.z)
			{
				return false;
			}
		}

		if (a.y > b.y) // a above b
		{
			if (a.y - as.y > b.y + bs.y) // bottom edge of a greater than top edge of b (not colliding)
			{
				return false;
			}
		}
		else
		{
			if (b.y - bs.y > a.y + as.y)
			{
				return false;
			}
		}

		return true;
	}

	glm::vec3 BoxCollider::getCollisionResponse(glm::vec3 _position, glm::vec3 _size)
	{
		if (!m_isTrigger)
		{
			float amount = 0.1f;
			float step = 0.1f;

			while (true)
			{
				if (!isColliding(_position, _size)) break;
				_position.x += amount;
				if (!isColliding(_position, _size)) break;
				_position.x -= amount;
				_position.x -= amount;
				if (!isColliding(_position, _size)) break;
				_position.x += amount;
				_position.z += amount;
				if (!isColliding(_position, _size)) break;
				_position.z -= amount;
				_position.z -= amount;
				if (!isColliding(_position, _size)) break;
				_position.z += amount;
				_position.y += amount;
				if (!isColliding(_position, _size)) break;
				_position.y -= amount;
				_position.y -= amount;
				if (!isColliding(_position, _size)) break;
				_position.y += amount;
				amount += step;
			}
		}

		return _position;
	}

	void BoxCollider::onInit()
	{
		m_size = glm::vec3(1, 1, 1);
		m_offset = glm::vec3(0);
		m_lastPosition = getTransform()->m_position;
	}

	void BoxCollider::onTick()
	{
		m_colliders.clear();
		if (!m_isTrigger && !m_isStatic)
		{
			collideStaticModel();
		}
		collideBox();
	}
}