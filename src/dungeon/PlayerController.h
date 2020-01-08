#include <cobebe/Cobebe.h>

class PlayerController : public cobebe::Component
{
public:

private:
	std::weak_ptr<cobebe::Transform> m_transform;
	std::weak_ptr<cobebe::Keyboard> m_keyboard;
	std::weak_ptr<cobebe::Mouse> m_mouse;
	std::weak_ptr<cobebe::Gamepad> m_gamepad;
	std::weak_ptr<cobebe::Camera> m_camera;
	std::weak_ptr<cobebe::Environment> m_environment;

	glm::mat3 m_originalOrientation;
	glm::vec2 m_camAngle;
	float m_minimumX;
	float m_maximumX;
	float m_minimumY;
	float m_maximumY;

	void onInit();
	void onTick();
	float ClampAngle(float _angle, float _min, float _max);
};