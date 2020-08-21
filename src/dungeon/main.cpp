#include <cobebe/Cobebe.h>
#include "PlayerController.h"
#include "Bloom.h"

int main()
{
	std::shared_ptr<cobebe::Core> App = cobebe::Core::initialise();

	App->getLighting()->addPointLight(glm::vec3(-12, 2, -5), glm::vec3(0.5f), 25.0f);

	std::shared_ptr<cobebe::Entity> entity = App->addEntity();

	std::shared_ptr<cobebe::Renderer> renderer = entity->addComponent<cobebe::Renderer>();
	renderer->setMesh("objs\\graveyard.obj");
	renderer->setTexture("images\\graveyard.png");
	renderer->setShader("deferred_shaders\\renderGAni.shad");

	entity->addComponent<Bloom>();

	//entity->addComponent<cobebe::Speaker>("oggs\\dixie_horn.ogg");

	entity->addComponent<cobebe::StaticModelCollider>();

	//entity = App->addEntity();
	//entity->getTransform()->m_position = glm::vec3(-12.0f, 1.7f, -12.0f);
	//std::shared_ptr<cobebe::PBRenderer> pbRenderer = entity->addComponent<cobebe::PBRenderer>();
	//pbRenderer->setMesh("spaceship\\Intergalactic_Spaceship-(Wavefront).obj");
	//pbRenderer->setTexture("spaceship\\textures\\Intergalactic Spaceship_color_4.png");
	//pbRenderer->setNormalMap("spaceship\\textures\\Intergalactic Spaceship_nmap_2_Tris.png");
	//pbRenderer->setMetalMap("spaceship\\textures\\Intergalactic Spaceship_metalness.png");
	//pbRenderer->setShader("pbr_shaders\\renderG_PBR.shad");

	entity = App->addEntity();
	entity->getTransform()->m_position = glm::vec3(0.0f, 1.7f, 5.0f);

	renderer = entity->addComponent<cobebe::Renderer>();
	renderer->setMesh("objs\\curuthers.obj");
	renderer->setTexture("images\\curuthers_diffuse.png");
	renderer->setShader("deferred_shaders\\renderGAni.shad");
	std::shared_ptr<cobebe::AnimationController> anm = renderer->addAnimationController();
	renderer->loadAnimation("animations\\run.anm");

	anm->playAnimation(0, 1);

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