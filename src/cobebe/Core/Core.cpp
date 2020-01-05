#include <cobebe/Core/Core.h>
#include <cobebe/Core/Entity.h>
#include <cobebe/Core/Transform.h>
#include <cobebe/Core/Camera.h>
#include <cobebe/Core/Environment.h>
#include <cobebe/Core/Keyboard.h>
#include <cobebe/Core/Mouse.h>
#include <cobebe/Core/Gamepad.h>
#include <cobebe/Resources/Resources.h>
#include <glm/ext.hpp>
#include <iostream>

namespace cobebe
{
	Core::Core()
	{
		m_running = false;
	}

	Core::~Core()
	{
		/*
		* Clean up OpenAL data.
		*
		* Note: Make sure current context has been set to NULL before deleting context.
		*       Make sure context destroyed before closing device.
		*/
		alcMakeContextCurrent(NULL);
		alcDestroyContext(m_alContext);
		alcCloseDevice(m_device);

		/*
		* Clean up input Devices
		*/
		m_gamepad = NULL;

		/*
		* Clean up SDL Window
		*/
		SDL_DestroyWindow(m_window);
		SDL_Quit();
	}

	const std::shared_ptr<Core> Core::initialise()
	{
		std::shared_ptr<Core> temp = std::make_shared<Core>();
		temp->m_environment = std::make_shared<Environment>();

		if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER) < 0)
		{
			throw Exception("SDL");
		}

		temp->m_window = SDL_CreateWindow("CoBeBe Window",
			SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			temp->m_environment->m_width, temp->m_environment->m_height,
			SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);

		if (!SDL_GL_CreateContext(temp->m_window))
		{
			throw Exception("Window");
		}

		/*
		* Initialize OpenAL audio system
		*/

		// Open up the OpenAL device
		temp->m_device = alcOpenDevice(NULL);

		if (temp->m_device == NULL)
		{
			throw Exception("Cannot open al device");
		}

		// Create audio context
		temp->m_alContext = alcCreateContext(temp->m_device, NULL);

		if (temp->m_alContext == NULL)
		{
			alcCloseDevice(temp->m_device);
			throw Exception("Cannot create al context");
		}

		// Set as current context
		if (!alcMakeContextCurrent(temp->m_alContext))
		{
			alcDestroyContext(temp->m_alContext);
			alcCloseDevice(temp->m_device);
			throw Exception("Cannot set as current context");
		}

		temp->m_context = glwrap::Context::initialise();
		temp->m_currentCamera = temp->addCamera();
		temp->m_currentCamera.lock()->m_isOn = true;

		temp->m_keyboard = std::make_shared<Keyboard>();
		temp->m_keyboard->onInit();

		temp->m_mouse = std::make_shared<Mouse>();

		temp->m_gamepad = std::make_shared<Gamepad>();

		temp->m_resources = std::make_shared<Resources>();
		temp->m_resources->m_context = temp->m_context;

		temp->m_nullShader = temp->m_context->
			createShader("shaders\\nullpass.shad");

		temp->m_self = temp;
		return temp;
	}

	void Core::run()
	{
		m_running = true;

		float currentTime, lastTime = SDL_GetTicks();
		while (m_running)
		{
			// Tick each Entity, if an error occurs destroy the Entity
			for (std::list<std::shared_ptr<Entity>>::iterator it = m_entities.begin(); it != m_entities.end(); ++it)
			{
				try
				{
					(*it)->tick();
				}
				catch (const Exception& e)
				{
					e.what();
					(*it)->m_kill = true;
				}
			}

			// Iterate through entities and delete any marked as killed
			for (std::list<std::shared_ptr<Entity>>::iterator it = m_entities.begin(); it != m_entities.end();)
			{
				if ((*it)->m_kill)
				{
					it = m_entities.erase(it);
				}
				else
				{
					it++;
				}
			}

			// Reset inputs for next tick
			m_keyboard->resetKeys();
			m_gamepad->resetButtons();

			// Update variables ready for drawing to screen
			SDL_GetWindowSize(m_window, &(m_environment->m_width), &(m_environment->m_height));
			glEnable(GL_CULL_FACE);
			glEnable(GL_DEPTH_TEST);
			glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			m_currentCamera.lock()->m_texture->clear();

			// PreDisplay each Entity
			for (std::list<std::shared_ptr<Entity>>::iterator it = m_entities.begin(); it != m_entities.end(); ++it)
			{
				(*it)->preDisplay();
			}

			// Display each Entity
			for (std::list<std::shared_ptr<Entity>>::iterator it = m_entities.begin(); it != m_entities.end(); ++it)
			{
				(*it)->display();
			}

			// Draw current Camera to screen
			m_nullShader->setViewport(glm::vec4(0, 0,
				m_environment->m_width, m_environment->m_height));
			m_nullShader->setUniform("in_Texture",
				m_currentCamera.lock()->m_texture);
			m_nullShader->draw();

			SDL_GL_SwapWindow(m_window);

			// PostDisplay each Entity
			for (std::list<std::shared_ptr<Entity>>::iterator it = m_entities.begin(); it != m_entities.end(); ++it)
			{
				(*it)->postDisplay();
			}

			// GUI each Entity
			for (std::list<std::shared_ptr<Entity>>::iterator it = m_entities.begin(); it != m_entities.end(); ++it)
			{
				(*it)->gui();
			}

			// Update deltaTime
			currentTime = SDL_GetTicks();
			m_environment->m_deltaTime = (currentTime - lastTime) / 1000.0f;
			lastTime = currentTime;
			if (m_environment->m_deltaTime < (1.0f / 60.0f))
			{
				SDL_Delay((unsigned int)(((1.0f / 60.0f) - m_environment->m_deltaTime)*1000.0f));
			}

			// Poll SDL Events
			pollSDLEvent();
			if (m_keyboard->isKeyPressed(SDL_SCANCODE_Q) || m_gamepad->isButtonPressed(0, cobebeInput::GamepadButton::aButton))
			{
				m_mouse->m_warpMouse = !m_mouse->m_warpMouse;
			}
		}
	}

	void Core::stop()
	{
		m_running = false;
	}

	std::shared_ptr<Entity> Core::addEntity()
	{
		// Initialise Entity before pushing to list
		std::shared_ptr<Entity> tempEntity = std::make_shared<Entity>();
		std::shared_ptr<Transform> tempTransform = tempEntity->addComponent<Transform>();
		tempEntity->m_transform = tempTransform;
		tempEntity->m_self = tempEntity;
		tempEntity->m_core = m_self;
		m_entities.push_back(tempEntity);
		return tempEntity;
	}

	std::shared_ptr<Camera> Core::addCamera()
	{
		// Initialise Camera before pushing to list
		std::shared_ptr<Camera> tempCamera = std::make_shared<Camera>();
		int width = m_environment->m_width;
		int height = m_environment->m_height;
		tempCamera->m_texture = m_context->createRenderTexture(width, height);
		tempCamera->m_projection = glm::perspective(glm::radians(45.0f),
			(float)width / (float)height, 0.1f, 100.f);

		m_cameras.push_back(tempCamera);
		return tempCamera;
	}

	std::shared_ptr<Camera> Core::addCamera(int _renderWidth, int _renderHeight)
	{
		// Initialise Camera before pushing to list
		std::shared_ptr<Camera> tempCamera = std::make_shared<Camera>();
		tempCamera->m_texture = m_context->createRenderTexture(_renderWidth, _renderHeight);
		tempCamera->m_projection = glm::perspective(glm::radians(45.0f),
			(float)_renderWidth / (float)_renderHeight, 0.1f, 100.f);

		m_cameras.push_back(tempCamera);
		return tempCamera;
	}

	std::shared_ptr<Camera> Core::getCurrentCamera()
	{
		return m_currentCamera.lock();
	}

	void Core::pollSDLEvent()
	{
		SDL_Event event = { 0 };

		int controllerId;

		while (SDL_PollEvent(&event))
		{
			int code;
			if (event.type == SDL_QUIT)
			{
				m_running = false;
			}
			else if (event.type == SDL_KEYDOWN)
			{
				code = event.key.keysym.scancode;
				m_keyboard->m_keysPressed.push_back
				(code);
			}
			else if (event.type == SDL_KEYUP)
			{
				code = event.key.keysym.scancode;
				m_keyboard->m_keysReleased.push_back
				(code);
			}
			else if (event.type == SDL_CONTROLLERBUTTONDOWN)
			{
				controllerId = m_gamepad->getControllerId(event.cdevice.which);
				m_gamepad->pressButton(controllerId, cobebeInput::GamepadButton(event.cbutton.button));
			}
			else if (event.type == SDL_CONTROLLERBUTTONUP)
			{
				controllerId = m_gamepad->getControllerId(event.cdevice.which);
				m_gamepad->releaseButton(controllerId, cobebeInput::GamepadButton(event.cbutton.button));
			}
			else if (event.type == SDL_CONTROLLERAXISMOTION)
			{
				controllerId = m_gamepad->getControllerId(event.cdevice.which);
				if (abs(event.caxis.value) > 3000)
				{
					m_gamepad->setAxis(controllerId, cobebeInput::GamepadAxis(event.caxis.axis), event.caxis.value);
				}
				else
				{
					m_gamepad->setAxis(controllerId, cobebeInput::GamepadAxis(event.caxis.axis), 0);
				}
			}
			else if (event.type == SDL_CONTROLLERDEVICEADDED)
			{
				m_gamepad->addController(event.cdevice.which);
			}
			else if (event.type == SDL_CONTROLLERDEVICEREMOVED)
			{
				m_gamepad->removeController(event.cdevice.which);
			}
		}

		int posX, posY;
		SDL_GetMouseState(&posX, &posY);

		// If applicable, return mouse to centre
		if (m_mouse->m_warpMouse)
		{
			int Mid_X = m_environment->m_width / 2;
			int Mid_Y = m_environment->m_height / 2;

			SDL_WarpMouseInWindow(NULL, Mid_X, Mid_Y);

			// Set the movement of the mouse
			m_mouse->m_movement.x = posX - Mid_X;
			m_mouse->m_movement.y = posY - Mid_Y;

			m_mouse->m_position = glm::vec2(posX, posY);
		}
		else
		{
			// Set the movement of the mouse
			m_mouse->m_movement.x = posX - m_mouse->m_position.x;
			m_mouse->m_movement.y = posY - m_mouse->m_position.y;

			m_mouse->m_position = glm::vec2(posX, posY);
		}
	}

	std::shared_ptr<Keyboard> Core::getKeyboard()
	{
		return m_keyboard;
	}

	std::shared_ptr<Mouse> Core::getMouse()
	{
		return m_mouse;
	}

	std::shared_ptr<Gamepad> Core::getGamepad()
	{
		return m_gamepad;
	}

	std::shared_ptr<Environment> Core::getEnvironment()
	{
		return m_environment;
	}
}