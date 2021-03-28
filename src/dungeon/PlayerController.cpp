#include "PlayerController.h"
#include <glm/gtx/quaternion.hpp>
#include <glm/ext.hpp>

void PlayerController::onInit()
{
	m_transform = getTransform();
	m_keyboard = getKeyboard();
	m_mouse = getMouse();
	m_gamepad = getGamepad();
	m_environment = getEnvironment();
	m_camera = getCore()->getCurrentCamera();
	m_camAngle = glm::vec2(0);
	m_minimumX = glm::radians(-360.0f);
	m_maximumX = glm::radians(360.0f);
	m_minimumY = glm::radians(-60.0f);
	m_maximumY = glm::radians(60.0f);

	m_camera.lock()->m_position = m_transform.lock()->m_position + glm::vec3(0, 0, -5);
	m_originalOrientation = glm::lookAt(m_camera.lock()->m_position,
		m_transform.lock()->m_position, glm::vec3(0, 1, 0));
}

void PlayerController::onTick()
{
	// Update camAngle using input
	m_camAngle += glm::radians(0.08f * -m_mouse.lock()->getMovement());
	glm::quat rotateY;
	glm::quat rotateX;

	m_camAngle.x = ClampAngle(m_camAngle.x, m_minimumX, m_maximumX);
	m_camAngle.y = ClampAngle(m_camAngle.y, m_minimumY, m_maximumY);

	rotateY = glm::rotate(rotateY, m_camAngle.y,
		glm::vec3(1, 0, 0));
	rotateX = glm::rotate(rotateX, m_camAngle.x,
		glm::vec3(0, 1, 0));

	m_camera.lock()->m_rotation = glm::toMat3(glm::quat(m_originalOrientation) * rotateX * rotateY);
	m_transform.lock()->m_rotation = glm::toMat3(rotateX);

	// Update camPosition using Input
	glm::mat4 tempMat(1.0f);

	tempMat = glm::rotate(glm::mat4(m_originalOrientation), m_camAngle.x, glm::vec3(0, 1, 0));
	glm::mat4 fwdMat = tempMat;

	if (m_keyboard.lock()->isKey(cobebeInput::wKey) 
		|| m_gamepad.lock()->isButton(0, cobebeInput::upButton))
	{
		fwdMat = glm::translate(fwdMat, glm::vec3(0, 0, -1));
	}
	if (m_keyboard.lock()->isKey(cobebeInput::sKey)
		|| m_gamepad.lock()->isButton(0, cobebeInput::downButton))
	{
		fwdMat = glm::translate(fwdMat, glm::vec3(0, 0, 1));
	}
	if (m_keyboard.lock()->isKey(cobebeInput::aKey)
		|| m_gamepad.lock()->isButton(0, cobebeInput::leftButton))
	{
		fwdMat = glm::translate(fwdMat, glm::vec3(-1, 0, 0));
	}
	if (m_keyboard.lock()->isKey(cobebeInput::dKey)
		|| m_gamepad.lock()->isButton(0, cobebeInput::rightButton))
	{
		fwdMat = glm::translate(fwdMat, glm::vec3(1, 0, 0));
	}

	glm::vec3 fwd = fwdMat * glm::vec4(0, 0, 0, 1);

	if (fwd != glm::vec3(0.0f, 0.0f, 0.0f))
	{
		fwd = 0.5f * glm::normalize(fwd);
		m_transform.lock()->m_position += fwd;
	}

	tempMat = glm::translate(tempMat, glm::vec3(0, 0.2, 1));
	glm::vec3 bwd = tempMat * glm::vec4(0, 0, 0, 1);
	bwd = 7.0f * glm::normalize(bwd);

	m_camera.lock()->m_position = m_transform.lock()->m_position + bwd;
	getEntity()->getComponent<cobebe::ObjAnimationController>()->incrementAnimations(0.1);
}

float PlayerController::ClampAngle(float _angle, float _min, float _max)
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