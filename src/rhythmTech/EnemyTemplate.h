#include <cobebe/Cobebe.h>

class BeatController;

//class EnemyTemplate : public cobebe::Entity
//{
//public:
//	EnemyTemplate(std::shared_ptr<BeatController> _bc);
//
//private:
//	std::weak_ptr<BeatController> m_bc;
//
//	void init();
//
//};

class BaseEnemy : public cobebe::Component
{
public:
	BaseEnemy(std::shared_ptr<BeatController> _bc);

protected:
	std::weak_ptr<BeatController> m_bc;

	float m_health;
	float m_speed;

	int m_beactAction;
	int m_beatStarted;

};

class SignPost :public BaseEnemy
{
public:
	SignPost(std::shared_ptr<BeatController> _bc);

private:
	std::weak_ptr<cobebe::ImageGUI> m_sprite;

	std::shared_ptr<cobebe::Texture> m_sign;
	std::shared_ptr<cobebe::Texture> m_signO1;
	std::shared_ptr<cobebe::Texture> m_signO2;
	std::shared_ptr<cobebe::Texture> m_signO3;
	std::shared_ptr<cobebe::Texture> m_signB1;
	std::shared_ptr<cobebe::Texture> m_signB2;
	std::shared_ptr<cobebe::Texture> m_signB3;

	void onInit();
	void onTick();

};