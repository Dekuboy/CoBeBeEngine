#include "BeatMonitor.h"
#include "BeatController.h"

BeatMonitor::BeatMonitor(std::shared_ptr<BeatController> _bc)
{
	m_bc = _bc;
}

void BeatMonitor::onInit()
{
	std::shared_ptr<cobebe::Entity> tempEntity = getCore()->addEntity();
	m_monitorBG = tempEntity->addComponent<cobebe::ImageGUI>();
	m_monitorBG.lock()->setTexture("images\\BeatMonitorBG.png");
	std::shared_ptr<cobebe::Transform> tempTransform = tempEntity->getTransform();
	tempTransform->m_position = glm::vec3(0.5f, 0.1f, -0.9f);
	tempTransform->m_scale = glm::vec3(0.15f, 0.045f, 1.0f);

	tempEntity = getCore()->addEntity();
	m_monitorFG = tempEntity->addComponent<cobebe::ImageGUI>();
	m_monitorFG.lock()->setTexture("images\\BeatMonitorFG.png");
	tempTransform = tempEntity->getTransform();
	tempTransform->m_position = glm::vec3(0.5f, 0.1f, 0.0f);
	tempTransform->m_scale = glm::vec3(0.14f, 0.035f, 1.0f);

	std::shared_ptr<cobebe::ImageGUI> tempGUI;

	int blockTotal = 0.14f / (m_bc.lock()->getBeatInterval() / 5.0f);
	blockTotal++;

	for (int i = 0; i < blockTotal * 2; i++)
	{
		tempEntity = getCore()->addEntity();
		tempGUI = tempEntity->addComponent<cobebe::ImageGUI>();
		tempGUI->setTexture("images\\Block.png");
		tempTransform = tempEntity->getTransform();
		tempTransform->m_position = glm::vec3(0.5f, 0.1f, -0.5f);
		tempTransform->m_scale = glm::vec3(0.007f, 0.035f, 1.0f);
		m_blocks.push_back(tempGUI);
	}
}

void BeatMonitor::onTick()
{
	bool sign = true;
	float bpp = m_bc.lock()->getBpp() / 100.0f;

	float increment = 1.0f / ((float)m_blocks.size() / 2.0f);

	glm::vec3 displacement(0.133f, 0.0f, 0.0f);

	for (std::list<std::weak_ptr<cobebe::ImageGUI>>::iterator itr = m_blocks.begin(); 
			itr != m_blocks.end(); itr++)
	{
		if (sign)
		{
			(*itr).lock()->getTransform()->m_position =
				glm::vec3(0.5f, 0.1f, -0.5f) + (displacement * (1 - bpp));
			bpp *= -1;
			sign = false;
		}
		else
		{
			bpp += 2;
			(*itr).lock()->getTransform()->m_position =
				glm::vec3(0.5f, 0.1f, -0.5f) + (displacement * (1 - bpp));
			bpp -= 2;
			bpp *= -1;
			bpp += increment;
			if (bpp > 1.0f)
			{
				bpp -= 1.0f;
			}
			sign = true;
		}
	}
}