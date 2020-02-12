#include <cobebe/cobebe.h>
#include "SceneController.h"
#include <glm/ext.hpp>

int main()
{
	std::shared_ptr<cobebe::Core> App = cobebe::Core::initialise();

	std::shared_ptr<cobebe::Entity> entity = App->addEntity();

	std::shared_ptr<cobebe::Renderer> renderer = entity->addComponent<cobebe::Renderer>();
	renderer->setMesh("objs\\re_hall_baked.obj");
	renderer->setTexture("images\\re_hall_diffuse.png");
	renderer->setShader("deferred_shaders\\renderG.shad");

	entity->getTransform()->m_position = glm::vec3(2.0f, -2.0f, -16.0f);
	entity->getTransform()->m_rotation = glm::rotate(glm::mat4(1), glm::radians(90.0f), glm::vec3(0, 1, 0));

	entity->addComponent<SceneController>();

	App->run();

	return 0;
}