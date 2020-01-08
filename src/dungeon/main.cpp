#include <cobebe/cobebe.h>
#include "PlayerController.h"

int main()
{
	std::shared_ptr<cobebe::Core> App = cobebe::Core::initialise();

	std::shared_ptr<cobebe::Entity> entity = App->addEntity();

	std::shared_ptr<cobebe::ShadowRenderer> renderer = entity->addComponent<cobebe::ShadowRenderer>();
	renderer->setMesh("objs\\graveyard.obj");
	renderer->setTexture("images\\graveyard.png");
	renderer->setShader("shadows\\spsmap.shad");

	//entity->addComponent<cobebe::Speaker>("dixie_horn.ogg");

	entity->addComponent<cobebe::StaticModelCollider>();

	entity = App->addEntity();
	entity->getTransform()->m_position = glm::vec3(0.0f, 1.7f, 5.0f);

	renderer = entity->addComponent<cobebe::ShadowRenderer>();
	renderer->setMesh("objs\\curuthers.obj");
	renderer->setTexture("images\\curuthers_diffuse.png");
	renderer->setShader("shadows\\spsmap.shad");

	entity->addComponent<cobebe::BoxCollider>();

	entity->addComponent<PlayerController>();
	
	App->run();

	return 0;
}