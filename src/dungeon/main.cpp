#include <iostream>
#include "../cobebe/Cobebe.h"

int main()
{
	std::shared_ptr<cobebe::Core> App = cobebe::Core::initialise();
	std::shared_ptr<cobebe::Entity> entity = App->addEntity();
	entity->addComponent<TriangleRenderer>();
	App->run();

	return 0;
}