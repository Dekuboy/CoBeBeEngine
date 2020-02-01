#include <cobebe/Core/Core.h>
#include <cobebe/Core/Entity.h>
#include <cobebe/Core/Transform.h>
#include <cobebe/Core/Camera.h>
#include <cobebe/Renderer/Lighting.h>
#include <cobebe/Core/Environment.h>
#include <cobebe/Core/Keyboard.h>
#include <cobebe/Core/Mouse.h>
#include <cobebe/Core/Gamepad.h>
#include <cobebe/GUI/Canvas.h>
#include <cobebe/Resources/RendAssets.h>
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

		temp->m_keyboard = std::make_shared<Keyboard>();
		temp->m_keyboard->onInit();

		temp->m_mouse = std::make_shared<Mouse>();

		temp->m_gamepad = std::make_shared<Gamepad>();

		temp->m_resources = std::make_shared<Resources>();
		temp->m_resources->m_context = temp->m_context;

		temp->m_nullShader = temp->loadAsset<Shader>("shaders\\nullpass.shad");
		temp->m_lightPassShader = temp->loadAsset<Shader>("deferred_shaders\\lightingG.shad");

		temp->m_lighting = std::make_shared<Lighting>();
		temp->m_lighting->m_core = temp;
		temp->m_lighting->onInit();

		temp->m_canvas = std::make_shared<Canvas>();
		temp->m_canvas->m_core = temp;
		temp->m_canvas->onInit();

		temp->m_currentCamera = temp->addCamera();
		temp->m_currentCamera.lock()->m_isOn = true;
		temp->m_currentCamera.lock()->m_position = glm::vec3(0, 0, 10);

		temp->m_self = temp;
		return temp;
	}

	void Core::run()
	{
		m_running = true;
		SDL_ShowCursor(false);

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
					std::cout << e.what();
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

			// Update variables ready for drawing to screen
			SDL_GetWindowSize(m_window, &(m_environment->m_width), &(m_environment->m_height));
			glEnable(GL_CULL_FACE);
			glEnable(GL_DEPTH_TEST);
			glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			m_currentCamera.lock()->m_texture->clear();
			m_currentCamera.lock()->m_gBuffer->clear();

			// Clear Shadows
			m_lighting->clear();

			// PreDisplay each Entity
			// Renders to DepthMaps in Lighting
			//glCullFace(GL_FRONT);
			for (std::list<std::shared_ptr<Entity>>::iterator it = m_entities.begin(); it != m_entities.end(); ++it)
			{
				(*it)->preDisplay();
			}
			//glCullFace(GL_BACK);
			m_lighting->drawLighting();
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			// Display each Entity
			for (std::list<std::shared_ptr<Entity>>::iterator it = m_entities.begin(); it != m_entities.end(); ++it)
			{
				(*it)->display();
			}

			glDisable(GL_DEPTH_TEST);
			glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			// Draw current Camera to screen
			drawToScreen();

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

			// Draw to window
			SDL_GL_SwapWindow(m_window);

			// Update deltaTime
			currentTime = SDL_GetTicks();
			m_environment->m_deltaTime = (currentTime - lastTime) / 1000.0f;
			lastTime = currentTime;
			if (m_environment->m_deltaTime < (1.0f / 60.0f))
			{
				SDL_Delay((unsigned int)(((1.0f / 60.0f) - m_environment->m_deltaTime)*1000.0f));
				m_environment->m_deltaTime = 1.0f / 60.0f;
			}

			// Reset inputs for next tick
			m_keyboard->resetKeys();
			m_gamepad->resetButtons();

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

	std::shared_ptr<glwrap::Context> Core::getGLContext()
	{
		return m_context;
	}

	std::shared_ptr<Camera> Core::addCamera()
	{
		// Initialise Camera before pushing to list
		std::shared_ptr<Camera> tempCamera = std::make_shared<Camera>();
		int width = m_environment->m_width;
		int height = m_environment->m_height;
		tempCamera->m_texture = m_context->createRenderTexture(width, height);
		tempCamera->m_gBuffer = m_context->createGBuffer(width, height);
		tempCamera->m_lighting = m_lighting;
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
		tempCamera->m_gBuffer = m_context->createGBuffer(_renderWidth, _renderHeight);
		tempCamera->m_lighting = m_lighting;
		tempCamera->m_projection = glm::perspective(glm::radians(45.0f),
			(float)_renderWidth / (float)_renderHeight, 0.1f, 100.f);

		m_cameras.push_back(tempCamera);
		return tempCamera;
	}

	std::shared_ptr<Camera> Core::getCurrentCamera()
	{
		return m_currentCamera.lock();
	}

	std::shared_ptr<Camera> Core::getCamera()
	{
		return m_currentCamera.lock();
	}

	std::shared_ptr<glwrap::ShaderProgram> Core::getNullPassShader()
	{
		return m_nullShader->getInternal();
	}

	std::shared_ptr<glwrap::ShaderProgram> Core::getLightPassShader()
	{
		return m_lightPassShader->getInternal();
	}

	std::shared_ptr<Lighting> Core::getLighting()
	{
		return m_lighting;
	}

	std::shared_ptr<Canvas> Core::getCanvas()
	{
		return m_canvas;
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

	void Core::drawToScreen()
	{
		m_currentCamera.lock()->drawLighting(m_lightPassShader);

		//std::shared_ptr<Shader> temp = loadAsset<Shader>("deferred_shaders\\test.shad");

		//temp->getInternal()->setUniform(m_currentCamera.lock()->m_gBuffer);

		//temp->getInternal()->draw(m_currentCamera.lock()->m_texture);

		std::shared_ptr<glwrap::ShaderProgram> nullInternal = m_nullShader->getInternal();

		nullInternal->setViewport(glm::vec4(0, 0,
			m_environment->m_width, m_environment->m_height));
		nullInternal->setUniform("in_Texture",
			m_currentCamera.lock()->m_texture);
		nullInternal->draw();
	}
}