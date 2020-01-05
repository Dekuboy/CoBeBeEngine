#include "PlayerController.h"

void PlayerController::onInit()
{
	m_transform = getTransform();
	m_keyboard = getKeyboard();
	m_gamepad = getGamepad();
	m_environment = getEnvironment();
}

void PlayerController::onTick()
{
	if (m_keyboard.lock()->isKey(cobebeInput::wKey) 
		|| m_gamepad.lock()->isButton(0, cobebeInput::upButton))
	{
		m_transform.lock()->m_position +=
			glm::vec3(0, 0, 3.0) * m_environment.lock()->getDeltaTime();
	}
}