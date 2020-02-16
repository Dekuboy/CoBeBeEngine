#include "PlayerController.h"
#include "BeatController.h"
#include <glm/ext.hpp>

PlayerController::PlayerController(std::shared_ptr<BeatController> _bc)
{
	m_bc = _bc;
}

void PlayerController::checkTiming(int _beatPercent)
{
	if (m_queue)
	{
		_beatPercent = 50;
	}

	m_medalGUI.lock()->display(_beatPercent);
	m_queue = true;
}

void PlayerController::onInit()
{
	m_queue = false;

	m_transform = getTransform();
	m_transform.lock()->m_scale = glm::vec3(0.8f);
	m_keyboard = getKeyboard();
	m_mouse = getMouse();
	m_gamepad = getGamepad();
	m_environment = getEnvironment();

	m_cameraController = getEntity()->addComponent<CameraController>();
	m_medalGUI = getEntity()->addComponent<Medal>();
}

void PlayerController::onTick()
{
	float beatPercent = m_bc.lock()->getBpp();
	int beatCount = m_bc.lock()->getBeatCount();

	if (beatPercent > 50 && beatCount > m_beatCount)
	{
		m_queue = false;
		m_beatCount = beatCount;
	}

	if (m_keyboard->isKeyPressed(cobebeInput::zKey))
	{
		checkTiming(beatPercent);
	}
	if (m_keyboard->isKeyPressed(cobebeInput::xKey))
	{
		checkTiming(beatPercent);
	}

	glm::vec2 mouseMovement = m_mouse->getMovement();

	if (mouseMovement.length() != 0.0f)
	{
		m_cameraController.lock()->rotateCamera(m_environment->getDeltaTime() * 2.0f * -mouseMovement);
	}

	// Update camPosition using Input
	glm::mat4 tempMat(1.0f);

	tempMat = getCore()->getCurrentCamera()->m_rotation;
	glm::mat4 fwdMat = tempMat;

	if (m_keyboard->isKey(cobebeInput::wKey)
		|| m_gamepad->isButton(0, cobebeInput::upButton))
	{
		fwdMat = glm::translate(fwdMat, glm::vec3(0, 0, -1));
	}
	if (m_keyboard->isKey(cobebeInput::sKey)
		|| m_gamepad->isButton(0, cobebeInput::downButton))
	{
		fwdMat = glm::translate(fwdMat, glm::vec3(0, 0, 1));
	}
	if (m_keyboard->isKey(cobebeInput::aKey)
		|| m_gamepad->isButton(0, cobebeInput::leftButton))
	{
		fwdMat = glm::translate(fwdMat, glm::vec3(-1, 0, 0));
	}
	if (m_keyboard->isKey(cobebeInput::dKey)
		|| m_gamepad->isButton(0, cobebeInput::rightButton))
	{
		fwdMat = glm::translate(fwdMat, glm::vec3(1, 0, 0));
	}

	glm::vec3 fwd = fwdMat * glm::vec4(0, 0, 0, 1);

	if (fwd != glm::vec3(0.0f, 0.0f, 0.0f))
	{
		fwd = 0.5f * glm::normalize(fwd);
		getCore()->getCurrentCamera()->m_position += fwd;
	}

	tempMat = glm::translate(tempMat, glm::vec3(0, 0.2, 1));
	glm::vec3 bwd = tempMat * glm::vec4(0, 0, 0, 1);
	bwd = 7.0f * glm::normalize(bwd);
}

void CameraController::rotateCamera(glm::vec2 _camMovement)
{
	// Update camAngle using input
	m_camAngle += glm::radians(_camMovement);
	glm::quat rotateY;
	glm::quat rotateX;

	m_camAngle.x = clampAngle(m_camAngle.x, m_minimumX, m_maximumX);
	m_camAngle.y = clampAngle(m_camAngle.y, m_minimumY, m_maximumY);

	rotateY = glm::rotate(rotateY, m_camAngle.y,
		glm::vec3(1, 0, 0));
	rotateX = glm::rotate(rotateX, m_camAngle.x,
		glm::vec3(0, 1, 0));

	m_camera->m_rotation = glm::mat3(glm::quat(m_originalOrientation) * rotateX * rotateY);
}

float CameraController::clampAngle(float _angle, float _min, float _max)
{
	if (_angle > glm::radians(360.0f))
	{
		_angle -= glm::radians(360.0f);
	}
	if (_angle < glm::radians(-360.0f))
	{
		_angle += glm::radians(360.0f);
	}
	return glm::clamp(_angle, _min, _max);
}

void CameraController::onInit()
{
	m_camAngle = glm::vec2(0);
	m_camera = getCore()->getCurrentCamera();
	m_minimumX = glm::radians(-360.0f);
	m_maximumX = glm::radians(360.0f);
	m_minimumY = glm::radians(-60.0f);
	m_maximumY = glm::radians(60.0f);

	m_originalOrientation = m_camera->m_rotation;
}

void Medal::display(float _beatPercent)
{
	m_timer = 0.4f;
	if (_beatPercent < 20 || _beatPercent > 80)
	{
		m_img.lock()->setTexture(m_gold);
	}
	else if (_beatPercent < 25 || _beatPercent > 60)
	{
		m_img.lock()->setTexture(m_silver);
	}
	else
	{
		m_img.lock()->setTexture(m_bronze);
	}
}

void Medal::onInit()
{
	std::shared_ptr<cobebe::Entity> tempEntity = getCore()->addEntity();

	m_img = tempEntity->addComponent<cobebe::ImageGUI>();

	m_gold = getCore()->loadAsset<cobebe::Texture>("images\\Gold.png");
	m_silver = getCore()->loadAsset<cobebe::Texture>("images\\Silver.png");
	m_bronze = getCore()->loadAsset<cobebe::Texture>("images\\Bronze.png");

	std::shared_ptr<cobebe::Transform> transform = tempEntity->getTransform();
	transform->m_position = glm::vec3(0.74f, 0.13f, 0.5f);
	transform->m_scale = glm::vec3(0.06f);

	m_environment = getEnvironment();
	m_timer = -1.0f;
}

void Medal::onTick()
{
	m_timer -= m_environment->getDeltaTime();
	if (m_timer < 0.0f)
	{
		m_img.lock()->setTexture((std::shared_ptr<cobebe::Texture>)NULL);
	}
}