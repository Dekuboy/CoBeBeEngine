#include <memory>

class Core;
class Entity;
class Keyboard;
class Mouse;
class Environment;

class Component
{
public:
	std::shared_ptr<Entity> getEntity();
	std::shared_ptr<Core> getCore();
	std::shared_ptr<Keyboard> getKeyboard();
	std::shared_ptr<Mouse> getMouse();
	std::shared_ptr<Environment> getEnvironment();

private:
	std::weak_ptr<Entity> m_entity;

	void onInit();
	void onBegin();
	void onTick();
	void onDisplay();

};