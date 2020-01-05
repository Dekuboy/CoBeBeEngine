#include <cobebe/cobebe.h>
#include "PlayerController.h"

int main()
{
	std::shared_ptr<cobebe::Core> App = cobebe::Core::initialise();

	std::shared_ptr<cobebe::Entity> entity = App->addEntity();
	entity->getTransform()->m_position = glm::vec3(0.0f, 0.0f, 10.0f);

	std::shared_ptr<cobebe::BoxCollider> bc = entity->addComponent<cobebe::BoxCollider>();
	bc->setTrigger(true);

	std::shared_ptr<cobebe::Renderer> renderer = entity->addComponent<cobebe::Renderer>();
	renderer->setMesh("objs\\curuthers.obj");
	renderer->setTexture("images\\curuthers_diffuse.png");
	renderer->setShader("shaders\\phong.shad");
	entity->addComponent<cobebe::Speaker>("dixie_horn.ogg");

	entity = App->addEntity();
	entity->getTransform()->m_position = glm::vec3(0.0f, 0.0f, 5.0f);

	entity->addComponent<cobebe::BoxCollider>();

	renderer = entity->addComponent<cobebe::Renderer>();
	renderer->setMesh("objs\\curuthers.obj");
	renderer->setTexture("images\\curuthers_diffuse.png");
	renderer->setShader("shaders\\phong.shad");
	entity->addComponent<PlayerController>();
	
	App->run();

	return 0;
}