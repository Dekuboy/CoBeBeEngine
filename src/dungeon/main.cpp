#include <cobebe/Cobebe.h>
#include "PlayerController.h"
#include "Bloom.h"

int main()
{
	std::shared_ptr<cobebe::Core> App = cobebe::Core::initialise();
	printf("Initialise\n");

	App->getLighting()->addPointLight(glm::vec3(-12, 2, -5), glm::vec3(0.5f), 25.0f);

	std::shared_ptr<cobebe::Entity> entity = App->addEntity();

	std::shared_ptr<cobebe::Renderer> renderer = entity->addComponent<cobebe::Renderer>();
	renderer->setMesh("objs\\graveyard.obj");
	renderer->setTexture("images\\graveyard.png");
	renderer->setShader("emscripten_shaders\\renderG.shad");

	entity->addComponent<Bloom>();

	//entity->addComponent<cobebe::Speaker>("oggs\\dixie_horn.ogg");

	entity->addComponent<cobebe::StaticModelCollider>(0);

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
	entity->getTransform()->m_scale = glm::vec3(0.7f, 0.7f, 0.7f);
	entity->addComponent<PlayerController>();

	renderer = entity->addComponent<cobebe::Renderer>();
	renderer->setMesh("objs\\curuthers.obj");
	renderer->setTexture("images\\curuthers_diffuse.png");
	renderer->setShader("emscripten_shaders\\renderGAni.shad");
	std::shared_ptr<cobebe::ObjAnimationController> anm = renderer->addObjAnimationController();
	renderer->loadObjAnimation("animations\\run.anm");

	anm->playAnimation(0, 1);

	std::shared_ptr<cobebe::BoxCollider> tmp = entity->addComponent<cobebe::BoxCollider>(0);
	tmp->setSize(glm::vec3(0.7f));


	entity = App->addEntity();
	entity->getTransform()->m_position = glm::vec3(-4.0f, 1.7f, 5.0f);

	renderer = entity->addComponent<cobebe::Renderer>();
	renderer->setMesh("objs\\curuthers.obj");
	renderer->setTexture("images\\curuthers_diffuse.png");
	renderer->setShader("emscripten_shaders\\renderGAni.shad");
	anm = renderer->addObjAnimationController();
	tmp = entity->addComponent<cobebe::BoxCollider>(1);
	tmp->setSize(glm::vec3(0.7f));

	entity = App->addEntity();
	entity->getTransform()->m_position = glm::vec3(0.12f, 0.92f, 0.1f);
	entity->getTransform()->m_scale = glm::vec3(0.1f, 0.05f, 1.0f);

	std::shared_ptr<cobebe::ImageGUI> gui = entity->addComponent<cobebe::ImageGUI>();
	gui->setTexture("images\\health_bar.png");

	App->run();
	
	return 0;
}

/* Emscripten Testing

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER) < 0)
	{
		throw std::exception();
	}

	SDL_Window* window = SDL_CreateWindow("CoBeBe Window",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		1080, 720,
		SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);

	if (!SDL_GL_CreateContext(window))
	{
		throw std::exception();
	}


	// Initialize OpenAL audio system


	// Open up the OpenAL device
	ALCdevice* device = alcOpenDevice(NULL);

	if (device == NULL)
	{
		throw std::exception();
	}

	// Create audio context
	ALCcontext* alContext = alcCreateContext(device, NULL);

	if (alContext == NULL)
	{
		alcCloseDevice(device);
		throw std::exception();
	}

	// Set as current context
	if (!alcMakeContextCurrent(alContext))
	{
		alcDestroyContext(alContext);
		alcCloseDevice(device);
		throw std::exception();
	}

	std::shared_ptr<glwrap::Context> context = glwrap::Context::initialise();

	std::shared_ptr<glwrap::GBuffer> gbuff = context->createGBuffer(1080, 720);

	std::shared_ptr<glwrap::ShaderProgram> nullShader = context->createShader("emscripten_shaders\\lightingG.shad");

*/