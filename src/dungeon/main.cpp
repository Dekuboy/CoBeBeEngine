#include <iostream>
#include "cobebe/Cobebe.h"

int main()
{
	std::shared_ptr<Core> Application = Core::initialise();

	std::cout << "Could Be Better now with App" << std::endl;
	system("PAUSE");
	return 0;
}