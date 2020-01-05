#include <cobebe/Cobebe.h>

class PlayerController : public cobebe::Component
{
public:

private:
	std::weak_ptr<cobebe::Transform> m_transform;
	std::weak_ptr<cobebe::Keyboard> m_keyboard;
	std::weak_ptr<cobebe::Gamepad> m_gamepad;

	std::weak_ptr<cobebe::Environment> m_environment;

	void onInit();
	void onTick();

};