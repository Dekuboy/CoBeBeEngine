#include <iostream>
#include "../cobebe/Cobebe.h"

int main()
{
	std::shared_ptr<Core> App = Core::initialise();
	std::shared_ptr<Entity> entity = App->addEntity();
	entity->addComponent<TriangleRenderer>();
	App->run();

	std::cout << "Could Be Better now with Stuff" << std::endl;
	system("PAUSE");
	return 0;
}