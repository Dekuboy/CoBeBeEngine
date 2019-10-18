#include <memory>
#include <list>

class Environment;
class Entity;
class Keyboard;
class Mouse;

class Core
{
public:
	static const std::shared_ptr<Core> initialise();

	void run();

	void stop();
	
	std::shared_ptr<Entity> addEntity();

private:
	std::list<std::shared_ptr<Entity>> m_entities;
	std::shared_ptr<Environment> m_environment;
	std::shared_ptr<Keyboard> m_keyboard;
	std::shared_ptr<Mouse> m_mouse;

	bool running;

	Core();
};