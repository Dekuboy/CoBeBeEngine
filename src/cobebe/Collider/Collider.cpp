#include <cobebe/Collider/Collider.h>

namespace cobebe
{
	Collider::Collider(int _mask)
	{
		m_maskList.push_back(_mask);
	}

	void Collider::setMask(int _mask)
	{
		bool found = false;
		for (std::list<int>::iterator itr = m_maskList.begin(); itr != m_maskList.end(); ++itr)
		{
			if (*itr == _mask)
			{
				found = true;
			}
		}
		if (!found)
		{
			m_maskList.push_back(_mask);
		}
	}

	std::list<int>& Collider::getMasks()
	{
		return m_maskList;
	}

	bool Collider::checkColliding()
	{
		return m_hasCollided;
	}

	const std::list<std::weak_ptr<Entity> >& Collider::getColliders()
	{
		return m_colliders;
	}

	bool Collider::checkMask(std::shared_ptr<Collider> _collider)
	{
		std::list<int> maskList = _collider->getMasks();

		for (std::list<int>::iterator thisList = m_maskList.begin();
			thisList != m_maskList.end(); ++thisList)
		{
			for (std::list<int>::iterator colList = maskList.begin();
				colList != maskList.end(); ++colList)
			{
				if ((*thisList) == (*colList))
				{
					return true;
				}
			}
		}

		return false;
	}

	void Collider::onGUI()
	{
		m_hasCollided = false;
		m_colliders.clear();
	}
}