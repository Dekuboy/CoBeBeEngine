#include <cobebe/Cobebe.h>

int main()
{
	std::shared_ptr<cobebe::Core> App = cobebe::Core::initialise();
	printf("Initialise\n");

	std::shared_ptr<cobebe::Entity> entity = App->addEntity();

	std::shared_ptr<cobebe::Renderer> renderer = entity->addComponent<cobebe::Renderer>();
	renderer->setWavefrontModel("speedhighway\\speed.obj");
	renderer->setShader("deferred_shaders\\renderGAni.shad");

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

	App->run();

	return 0;
}