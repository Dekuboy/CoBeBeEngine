#include "PlayerController.h"
#include <glm/ext.hpp>

void PlayerController::onInit()
{
	m_transform = getTransform();
	m_keyboard = getKeyboard();
	m_gamepad = getGamepad();
	m_environment = getEnvironment();
}

void PlayerController::onTick()
{
	glm::mat3 rotate = m_transform.lock()->m_rotation;
	m_transform.lock()->m_rotation = glm::mat3(glm::rotate(glm::quat(rotate),
		glm::radians(30.0f * m_environment.lock()->getDeltaTime()),
		glm::vec3(0, 1, 0)));
	if (m_keyboard.lock()->isKey(cobebeInput::wKey) 
		|| m_gamepad.lock()->isButton(0, cobebeInput::upButton))
	{
		m_transform.lock()->m_position +=
			glm::vec3(0, 0, -3.0) * m_environment.lock()->getDeltaTime();
	}
}