#include <cobebe/cobebe.h>

int main()
{
	std::shared_ptr<cobebe::Core> App = cobebe::Core::initialise();

	std::shared_ptr<cobebe::Mesh> mesh = App->loadAsset<cobebe::Mesh>("objs\\curuthers.obj");
	std::shared_ptr<cobebe::Texture> texture = App->loadAsset<cobebe::Texture>("images\\curuthers_diffuse.png");
	std::shared_ptr<cobebe::Shader> shader = App->loadAsset<cobebe::Shader>("shaders\\phong.shad");
	std::shared_ptr<cobebe::Entity> entity = App->addEntity();
	entity->getTransform()->m_position = glm::vec3(0.0f, 0.0f, 20.0f);
	std::shared_ptr<cobebe::Renderer> renderer = entity->addComponent<cobebe::Renderer>();
	renderer->setMesh(mesh);
	renderer->setTexture(texture);
	renderer->setShader(shader);
	entity->addComponent<cobebe::Speaker>("dixie_horn.ogg");
	
	App->run();

	return 0;
}