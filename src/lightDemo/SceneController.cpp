#include "SceneController.h"
#include <glm/ext.hpp>

void RotateAround::onInit()
{
	m_initialPosition = getTransform()->m_position;
	m_rotatePosition = (*getLighting()->getPointLights().begin())->getPosition();
	m_timer = 0.0f;
}

void RotateAround::onTick()
{
	m_timer += getEnvironment()->getDeltaTime();
	glm::vec3 move = m_rotatePosition - m_initialPosition;
	glm::mat4 rotate(1);
	rotate = glm::rotate(rotate,glm::radians(20 * m_timer), glm::vec3(0, 1, 0));

	move = rotate * glm::vec4(move, 1);

	getTransform()->m_position = m_rotatePosition + move;
}

void SceneController::addCrate()
{
	if (m_crates.size() < m_crateLimit)
	{
		std::shared_ptr<cobebe::Entity> entity = getCore()->addEntity();

		std::shared_ptr<cobebe::ShadowRenderer> renderer = entity->addComponent<cobebe::ShadowRenderer>();
		renderer->setMesh("objs\\Crate1.obj");
		renderer->setTexture("images\\crate_1.png");
		renderer->setShader("shadows\\cubemap.shad");

		m_crates.push_back(entity);

		switch (m_crates.size())
		{
		case 1:
			entity->getTransform()->m_position = glm::vec3(8, -4, -20);
			break;
		case 2:
			entity->getTransform()->m_position = glm::vec3(-8, -4, -20);
			break;
		case 3:
			entity->getTransform()->m_position = glm::vec3(4, -3, -25);
			break;
		case 4:
			entity->getTransform()->m_position = glm::vec3(-4, -3, -15);
			break;
		case 5:
			entity->getTransform()->m_position = glm::vec3(2, -1, -20);
			break;
		case 6:
			entity->getTransform()->m_position = glm::vec3(-2, -1, -20);
			break;
		}
		entity->addComponent<RotateAround>();
	}
}

void SceneController::deleteCrate()
{
	if (m_crates.size() > 0)
	{
		m_crates.back().lock()->kill();
		m_crates.pop_back();
	}
}

void SceneController::increaseRange()
{
	float range = m_pointLight.lock()->getRadius();
	if (!(range >= 35.0f))
	{
		range += 1.0f;

		if (range < 5.0f)
		{
			range = 5.0f;
		}

		m_pointLight.lock()->setRadius(range);
	}
}

void SceneController::lowerRange()
{
	float range = m_pointLight.lock()->getRadius();
	if (!(range <= 5.0f))
	{
		range -= 1.0f;

		if (range < 5.0f)
		{
			range = 5.0f;
		}

		m_pointLight.lock()->setRadius(range);
	}
}

void SceneController::onInit()
{
	std::shared_ptr<cobebe::Camera> camera = getCore()->getCurrentCamera();

	camera->m_position = glm::vec3(0, 0, -2);

	m_crateLimit = 6;

	m_lighting = getLighting();
	m_lighting.lock()->setGlobalLightPos(glm::vec3(4, -4, -20));
	m_lighting.lock()->setGlobalLightDir(glm::vec3(0, 0, -1));

	m_pointLight = *m_lighting.lock()->getPointLights().begin();

	m_pointLight.lock()->setPosition(glm::vec3(0, -2, -20));

	m_keyboard = getKeyboard();

	addCrate();
}

void SceneController::onTick()
{
	if (m_keyboard.lock()->isKeyPressed(cobebeInput::aKey))
	{
		addCrate();
	}
	if (m_keyboard.lock()->isKeyPressed(cobebeInput::sKey))
	{
		deleteCrate();
	}
	if (m_keyboard.lock()->isKey(cobebeInput::dKey))
	{
		increaseRange();
	}
	if (m_keyboard.lock()->isKey(cobebeInput::fKey))
	{
		lowerRange();
	}
}
