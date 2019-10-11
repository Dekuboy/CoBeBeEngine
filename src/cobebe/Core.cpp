#include "Core.h"

Core::Core()
{

}

std::shared_ptr<Core> Core::initialise()
{
	std::shared_ptr<Core> temp = std::make_shared<Core>(Core());
	return temp;
}