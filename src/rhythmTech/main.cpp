#include "BeatController.h"
#include "BeatMonitor.h"
#include "BGMusic.h"
#include "PlayerController.h"
#include "EnemyTemplate.h"
#include <glm/ext.hpp>

int main()
{
	std::shared_ptr<cobebe::Core> App = cobebe::Core::initialise();

	App->getLighting()->setGlobalLightCol(glm::vec3(0.2f));
	App->getLighting()->setGlobalLightDir(glm::vec3(1, -1, 0));
	App->getLighting()->addPointLight(glm::vec3(0, 0, 0), glm::vec3(0.3f), 50.0f);

	std::shared_ptr<cobebe::Camera> camera = App->getCurrentCamera();
	camera->m_position = glm::vec3(-16, 2, 0);
	camera->m_rotation = glm::rotate(glm::mat4(1), glm::radians(-90.0f), glm::vec3(0, 1, 0));

	std::shared_ptr<cobebe::Entity> entity = App->addEntity();

	std::shared_ptr<BeatController> bc = entity->addComponent<BeatController>();
	entity->addComponent<BGMusic>(bc, "oggs\\The_First_Step.ogg");
	entity->addComponent<BeatMonitor>(bc);
	entity->addComponent<PlayerController>(bc);

	entity = App->addEntity();

	std::shared_ptr<cobebe::Renderer> renderer = entity->addComponent<cobebe::Renderer>();
	renderer->setMesh("objs\\re_hall_baked.obj");
	renderer->setTexture("images\\re_hall_diffuse.png");
	renderer->setShader("deferred_shaders\\renderG.shad");

	entity = App->addEntity();

	entity->addComponent<SignPost>(bc);

	App->run();

	return 0;
}