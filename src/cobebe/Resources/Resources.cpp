#include "Resources.h"

namespace cobebe
{
	bool Resources::remove(std::string _path)
	{
		if (!m_resources.empty())
		{
			std::weak_ptr<Asset> dependency;
			for (std::list<std::shared_ptr<Asset> >::iterator it = m_resources.begin(); it != m_resources.end(); ++it)
			{
				if ((*it)->m_path == _path)
				{
					dependency = *it;
					*it = std::shared_ptr<Asset>();
					if (dependency.lock())
					{
						*it = dependency.lock();
						return false;
					}
					else
					{
						m_resources.erase(it);
						return true;
					}
				}
			}
		}
		return false;
	}

	void Resources::empty()
	{
		if (!m_resources.empty())
		{
			std::weak_ptr<Asset> dependency;
			for (std::list<std::shared_ptr<Asset> >::iterator it = m_resources.begin(); it != m_resources.end(); )
			{
				dependency = *it;
				*it = std::shared_ptr<Asset>();
				if (dependency.lock())
				{
					*it = dependency.lock();
					it++;
				}
				else
				{
					it = m_resources.erase(it);
				}
			}
		}
	}

	void Resources::hardEmpty()
	{
		m_resources.empty();
	}
}