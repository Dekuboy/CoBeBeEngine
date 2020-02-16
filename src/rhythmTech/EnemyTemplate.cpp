#include "EnemyTemplate.h"
#include "BeatController.h"
#include <iostream>

//EnemyTemplate::EnemyTemplate(std::shared_ptr<BeatController> _bc)
//{
//
//}
//
//void EnemyTemplate::init()
//{
//	  addComponent<BaseEntity>(m_bc.lock());
//}

BaseEnemy::BaseEnemy(std::shared_ptr<BeatController> _bc)
{
	m_bc = _bc;
}

SignPost::SignPost(std::shared_ptr<BeatController> _bc) : BaseEnemy(_bc)
{

}

void SignPost::onInit()
{
	m_sprite = getEntity()->addComponent<cobebe::ImageGUI>();
	m_sprite.lock()->setWorldGUI(true);

	std::shared_ptr<cobebe::Core> core = getCore();
	m_sign = core->loadAsset<cobebe::Texture>("images\\Sign.png");
	m_signO1 = core->loadAsset<cobebe::Texture>("images\\SignO1.png");;
	m_signO2 = core->loadAsset<cobebe::Texture>("images\\SignO2.png");;
	m_signO3 = core->loadAsset<cobebe::Texture>("images\\SignO3.png");;
	m_signB1 = core->loadAsset<cobebe::Texture>("images\\SignB1.png");;
	m_signB2 = core->loadAsset<cobebe::Texture>("images\\SignB2.png");;
	m_signB3 = core->loadAsset<cobebe::Texture>("images\\SignB3.png");;

	getEntity()->getTransform()->m_scale = glm::vec3(2.0f, 3.0f, 1.0f);
}

void SignPost::onTick()
{
	bool isBeatFrame = m_bc.lock()->checkBeatFrame();
	if (isBeatFrame)
	{
		m_sprite.lock()->setTexture(m_sign);
		int beatId = m_bc.lock()->getBeatCount();

		int idSplit = beatId % 16;
		int attackId = idSplit / 4;
		int attackSplit = idSplit % 4;

		if (attackId == 1)
		{
			if (attackSplit == 0)
			{
				m_sprite.lock()->setTexture(m_signO1);
			}
			else if (attackSplit == 1)
			{
				m_sprite.lock()->setTexture(m_signO2);
			}
			else if (attackSplit == 2)
			{
				m_sprite.lock()->setTexture(m_signO3);
			}
		}
		else if (attackId == 2)
		{
			if (attackSplit == 0)
			{
				m_sprite.lock()->setTexture(m_signB1);
			}
			else if (attackSplit == 1)
			{
				m_sprite.lock()->setTexture(m_signB2);
			}
			else if (attackSplit == 2)
			{
				m_sprite.lock()->setTexture(m_signB3);
			}
		}
		else if (attackId == 3)
		{
			if (attackSplit == 0 || attackSplit == 2)
			{
				m_sprite.lock()->setTexture(m_signO2);
			}
			else
			{
				m_sprite.lock()->setTexture(m_signO3);
			}
		}
	}
}