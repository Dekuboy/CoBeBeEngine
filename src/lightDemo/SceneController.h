#include <cobebe/Cobebe.h>

class RotateAround : public cobebe::Component
{
public:

private:
	glm::vec3 m_initialPosition;
	glm::vec3 m_rotatePosition;
	float m_timer;

	void onInit();
	void onTick();

};

class SceneController : public cobebe::Component
{
public:

private:
	std::weak_ptr<cobebe::Lighting> m_lighting;
	std::weak_ptr<cobebe::PointLight> m_pointLight;

	std::list<std::weak_ptr<cobebe::Entity>> m_crates;
	std::weak_ptr<cobebe::Keyboard> m_keyboard;

	int m_crateLimit;

	void addCrate();
	void deleteCrate();
	void increaseRange();
	void lowerRange();

	void onInit();
	void onTick();

};