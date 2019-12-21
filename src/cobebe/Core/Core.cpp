#include "Core.h"
#include "Entity.h"
#include "Transform.h"
#include <SDL2/SDL.h>

namespace cobebe
{
	Core::Core()
	{

	}

	Core::~Core()
	{
		SDL_DestroyWindow(m_window);
		SDL_Quit();
	}

	const std::shared_ptr<Core> Core::initialise()
	{
#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

		std::shared_ptr<Core> temp = std::make_shared<Core>();

		if (SDL_Init(SDL_INIT_VIDEO) < 0)
		{
			throw Exception("Vid");
		}

		temp->m_window = SDL_CreateWindow("CoBeBe Window",
			SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);

		if (!SDL_GL_CreateContext(temp->m_window))
		{
			throw Exception("Window");
		}

		temp->m_context = glwrap::Context::initialise();

		temp->m_self = temp;
		return temp;
	}

	void Core::run()
	{
		bool quit = false;

		while (!quit)
		{

			for (std::list<std::shared_ptr<Entity>>::iterator it = m_entities.begin(); it != m_entities.end(); ++it)
			{
				(*it)->tick();
			}

			for (std::list<std::shared_ptr<Entity>>::iterator it = m_entities.begin(); it != m_entities.end(); ++it)
			{
				(*it)->display();
			}

			SDL_GL_SwapWindow(m_window);

			SDL_Event event = { 0 };

			while (SDL_PollEvent(&event))
			{
				if (event.type == SDL_QUIT)
				{
					quit = true;
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
		tempEntity->m_core = m_self;
		m_entities.push_back(tempEntity);
		return tempEntity;
	}
}