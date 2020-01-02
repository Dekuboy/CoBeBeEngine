#include <cobebe/cobebe.h>

int main()
{
	std::shared_ptr<cobebe::Core> App = cobebe::Core::initialise();

	std::shared_ptr<cobebe::Entity> entity = App->addEntity();
	entity->getTransform()->m_position = glm::vec3(0.0f, 0.0f, 10.0f);
	std::shared_ptr<cobebe::Renderer> renderer = entity->addComponent<cobebe::Renderer>();
	renderer->setMesh("objs\\curuthers.obj");
	renderer->setTexture("images\\curuthers_diffuse.png");
	renderer->setShader("shaders\\phong.shad");
	entity->addComponent<cobebe::Speaker>("dixie_horn.ogg");
	
	App->run();

	return 0;
}