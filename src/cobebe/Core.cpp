#include "Core.h"
#include "Entity.h"
#include <SDL2/SDL.h>

Core::Core()
{

}

Core::~Core()
{

}

const std::shared_ptr<Core> Core::initialise()
{
	std::shared_ptr<Core> temp = std::make_shared<Core>();
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
	m_entities.push_back(tempEntity);
	return tempEntity;
}