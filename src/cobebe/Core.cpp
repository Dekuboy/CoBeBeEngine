#include "Core.h"

Core::Core()
{

}

const std::shared_ptr<Core> Core::initialise()
{
	std::shared_ptr<Core> temp = std::make_shared<Core>(Core());
	return temp;
}

void Core::run()
{

}

void Core::stop()
{

}

std::shared_ptr<Entity> Core::addEntity()
{

}