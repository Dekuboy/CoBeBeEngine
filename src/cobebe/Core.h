#include <memory>

class Core
{
public:
	static std::shared_ptr<Core> initialise();
private:
	Core();
};