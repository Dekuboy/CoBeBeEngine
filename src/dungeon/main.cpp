#include <cobebe/cobebe.h>
#include "PlayerController.h"
#include "Bloom.h"

int main()
{
	std::shared_ptr<cobebe::Core> App = cobebe::Core::initialise();

	std::shared_ptr<cobebe::Entity> entity = App->addEntity();

	std::shared_ptr<cobebe::ShadowRenderer> renderer = entity->addComponent<cobebe::ShadowRenderer>();
	renderer->setMesh("objs\\graveyard.obj");
	renderer->setTexture("images\\graveyard.png");
	renderer->setShader("shadows\\cubemap.shad");

	entity->addComponent<Bloom>();

	entity->addComponent<cobebe::Speaker>("dixie_horn.ogg");

	entity->addComponent<cobebe::StaticModelCollider>();

	entity = App->addEntity();
	entity->getTransform()->m_position = glm::vec3(0.0f, 1.7f, 5.0f);

	renderer = entity->addComponent<cobebe::ShadowRenderer>();
	renderer->setMesh("objs\\curuthers.obj");
	renderer->setTexture("images\\curuthers_diffuse.png");
	renderer->setShader("shadows\\cubemap.shad");

	std::shared_ptr<cobebe::BoxCollider> tmp = entity->addComponent<cobebe::BoxCollider>();
	tmp->setSize(glm::vec3(0.7f));

	entity->addComponent<PlayerController>();

	entity = App->addEntity();
	entity->getTransform()->m_position = glm::vec3(0.12f, 0.92f, 0.1f);
	entity->getTransform()->m_scale = glm::vec3(0.1f, 0.05f, 1.0f);

	std::shared_ptr<cobebe::ImageGUI> gui = entity->addComponent<cobebe::ImageGUI>();
	gui->setTexture("images\\health_bar.png");
	
	App->run();

	return 0;
}