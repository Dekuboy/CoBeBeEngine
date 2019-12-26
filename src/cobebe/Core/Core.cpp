#include <cobebe/Core/Core.h>
#include <cobebe/Core/Entity.h>
#include <cobebe/Core/Transform.h>
#include <cobebe/Core/Camera.h>
#include <cobebe/Core/Environment.h>
#include <cobebe/Resources/Resources.h>
#include <SDL2/SDL.h>
#include <glm/ext.hpp>

namespace cobebe
{
	Core::Core()
	{
		m_running = false;
	}

	Core::~Core()
	{
		SDL_DestroyWindow(m_window);
		SDL_Quit();
	}

	const std::shared_ptr<Core> Core::initialise()
	{
		std::shared_ptr<Core> temp = std::make_shared<Core>();
		temp->m_environment = std::make_shared<Environment>();

		if (SDL_Init(SDL_INIT_VIDEO) < 0)
		{
			throw Exception("Vid");
		}

		temp->m_window = SDL_CreateWindow("CoBeBe Window",
			SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			temp->m_environment->m_width, temp->m_environment->m_height, 
			SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);

		if (!SDL_GL_CreateContext(temp->m_window))
		{
			throw Exception("Window");
		}

		temp->m_context = glwrap::Context::initialise();
		temp->m_currentCamera = temp->addCamera();
		temp->m_currentCamera.lock()->m_isOn = true;

		temp->m_resources = std::make_shared<Resources>();
		temp->m_resources->m_context = temp->m_context;

		temp->m_nullShader = temp->m_context->
			createShader("shaders\\nullpass.shad");

		temp->m_self = temp;
		return temp;
	}

	void Core::run()
	{
		m_running = true;

		float currentTime, lastTime = SDL_GetTicks();
		while (m_running)
		{
			for (std::list<std::shared_ptr<Entity>>::iterator it = m_entities.begin(); it != m_entities.end(); ++it)
			{
				try
				{
					(*it)->tick();
				}
				catch (const Exception& e)
				{
					e.what();
					(*it)->m_kill = true;
				}
			}

			for (std::list<std::shared_ptr<Entity>>::iterator it = m_entities.begin(); it != m_entities.end();)
			{
				if ((*it)->m_kill)
				{
					it = m_entities.erase(it);
				}
				else
				{
					it++;
				}
			}

			SDL_GetWindowSize(m_window, &(m_environment->m_width), &(m_environment->m_height));
			glEnable(GL_CULL_FACE);
			glEnable(GL_DEPTH_TEST);
			glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			m_currentCamera.lock()->m_texture->clear();

			for (std::list<std::shared_ptr<Entity>>::iterator it = m_entities.begin(); it != m_entities.end(); ++it)
			{
				(*it)->display();
			}

			m_nullShader->setViewport(glm::vec4(0, 0, 
				m_environment->m_width, m_environment->m_height));
			m_nullShader->setUniform("in_Texture", 
				m_currentCamera.lock()->m_texture);
			m_nullShader->draw();

			SDL_GL_SwapWindow(m_window);

			currentTime = SDL_GetTicks();
			m_environment->m_deltaTime = (float)(currentTime - lastTime) / 1000.0f;
			lastTime = currentTime;
			if (m_environment->m_deltaTime < (1.0f / 60.0f))
			{
				SDL_Delay((unsigned int)(((1.0f / 60.0f) - m_environment->m_deltaTime)*1000.0f));
			}

			SDL_Event event = { 0 };

			while (SDL_PollEvent(&event))
			{
				if (event.type == SDL_QUIT)
				{
					m_running = false;
				}
			}
		}
	}

	void Core::stop()
	{

	}

	std::shared_ptr<Entity> Core::addEntity()
	{
		std::shared_ptr<Entity> tempEntity = std::make_shared<Entity>();
		std::shared_ptr<Transform> tempTransform = tempEntity->addComponent<Transform>();
		tempEntity->m_transform = tempTransform;
		tempEntity->m_self = tempEntity;
		tempEntity->m_core = m_self;
		m_entities.push_back(tempEntity);
		return tempEntity;
	}

	std::shared_ptr<Camera> Core::addCamera()
	{
		std::shared_ptr<Camera> tempCamera = std::make_shared<Camera>();
		int width = m_environment->m_width;
		int height = m_environment->m_height;
		tempCamera->m_texture = m_context->createRenderTexture(width, height);
		tempCamera->m_projection = glm::perspective(glm::radians(45.0f),
			(float)width / (float)height, 0.1f, 100.f);

		m_cameras.push_back(tempCamera);
		return tempCamera;
	}

	std::shared_ptr<Camera> Core::addCamera(int _renderWidth, int _renderHeight)
	{
		std::shared_ptr<Camera> tempCamera = std::make_shared<Camera>();
		tempCamera->m_texture = m_context->createRenderTexture(_renderWidth, _renderHeight);
		tempCamera->m_projection = glm::perspective(glm::radians(45.0f),
			(float)_renderWidth / (float)_renderHeight, 0.1f, 100.f);

		m_cameras.push_back(tempCamera);
		return tempCamera;
	}

	std::shared_ptr<Camera> Core::getCurrentCamera()
	{
		return m_currentCamera.lock();
	}
}