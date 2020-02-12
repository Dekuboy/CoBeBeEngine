#include <cobebe/cobebe.h>
#include <glm/ext.hpp>

int main()
{
	std::shared_ptr<cobebe::Core> App = cobebe::Core::initialise();

	App->getLighting()->setGlobalLightCol(glm::vec3(0.2f));
	App->getLighting()->setGlobalLightDir(glm::vec3(1, -1, 0));
	App->getLighting()->addPointLight(glm::vec3(0, 0, -2), glm::vec3(0.3f), 50.0f);

	std::shared_ptr<cobebe::Entity> entity = App->addEntity();

	std::shared_ptr<cobebe::Renderer> renderer = entity->addComponent<cobebe::Renderer>();
	renderer->setMesh("objs\\re_hall_baked.obj");
	renderer->setTexture("images\\re_hall_diffuse.png");
	renderer->setShader("deferred_shaders\\renderG.shad");

	std::shared_ptr<cobebe::Camera> camera = App->getCurrentCamera();

	camera->m_position = glm::vec3(-16, 2, -2);
	camera->m_rotation = glm::rotate(glm::mat4(1), glm::radians(-90.0f), glm::vec3(0, 1, 0));

	App->run();

	return 0;
}