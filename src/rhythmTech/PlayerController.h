#include <cobebe/Cobebe.h>

class BeatController;
class CameraController;
class Medal;

class PlayerController : public cobebe::Component
{
public:
	PlayerController(std::shared_ptr<BeatController> _bc);

private:
	std::weak_ptr<BeatController> m_bc;

	bool m_queue;
	int m_beatCount;

	std::weak_ptr<cobebe::Transform> m_transform;
	std::shared_ptr<cobebe::Keyboard> m_keyboard;
	std::shared_ptr<cobebe::Mouse> m_mouse;
	std::shared_ptr<cobebe::Gamepad> m_gamepad;
	std::shared_ptr<cobebe::Environment> m_environment;

	std::weak_ptr<CameraController> m_cameraController;
	std::weak_ptr<Medal> m_medalGUI;

	void checkTiming(int _beatPercent);

	void onInit();
	void onTick();

};

class CameraController : public cobebe::Component
{
public:

private:
	friend class PlayerController;
	std::shared_ptr<cobebe::Camera> m_camera;

	glm::mat3 m_originalOrientation;
	glm::vec2 m_camAngle;
	float m_minimumX;
	float m_maximumX;
	float m_minimumY;
	float m_maximumY;

	void rotateCamera(glm::vec2 _camMovement);
	float clampAngle(float _angle, float _min, float _max);

	void onInit();

};

class Medal : public cobebe::Component
{
public:

private:
	friend class PlayerController;

	std::weak_ptr<cobebe::ImageGUI> m_img;
	std::shared_ptr<cobebe::Texture> m_gold;
	std::shared_ptr<cobebe::Texture> m_silver;
	std::shared_ptr<cobebe::Texture> m_bronze;

	std::shared_ptr<cobebe::Environment> m_environment;
	float m_timer;

	void display(float _beatPercent);

	void onInit();
	void onTick();
};