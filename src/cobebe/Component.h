#ifndef _ENTITY_COMPONENT
#define _ENTITY_COMPONENT
#include <memory>
#include "NonCopyable.h"

class Core;
class Entity;
class Keyboard;
class Mouse;
class Environment;

class Component : private NonCopyable
{
public:
	virtual ~Component() {}

	std::shared_ptr<Entity> getEntity();
	std::shared_ptr<Core> getCore();
	std::shared_ptr<Keyboard> getKeyboard();
	std::shared_ptr<Mouse> getMouse();
	std::shared_ptr<Environment> getEnvironment();

private:
	friend class Entity;

	std::weak_ptr<Entity> m_entity;

	virtual void onInit();
	virtual void onBegin();
	virtual void onTick();
	virtual void onDisplay();

};
#endif