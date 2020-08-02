#include <cobebe/GUI/Canvas.h>
#include <cobebe/Core/Environment.h>
#include <cobebe/Core/Core.h>
#include <cobebe/Core/Camera.h>
#include <cobebe/Resources/Resources.h>
#include <cobebe/Resources/RendAssets.h>
#include <cobebe/Core/Entity.h>
#include <cobebe/Core/Transform.h>
#include <cobebe/GUI/ButtonGUI.h>
#include <cobebe/Core/Mouse.h>
#include <glm/ext.hpp>

float rayTriIntersect(float _origin[3], float _direction[3], float _triCoords[3][3]);
bool aabb(float _positionA[3], float _sizeA[3], float _positionB[3], float _sizeB[3]);

namespace cobebe
{
	void Canvas::drawTexture(std::shared_ptr<Texture> _image,
		glm::vec3 _position, glm::vec3 _size)
	{
		int newWidth = m_environment.lock()->getWidth();
		int newHeight = m_environment.lock()->getHeight();

		if (!(m_currentWidth == newWidth && m_currentHeight == newHeight))
		{
			m_currentWidth = newWidth;
			m_currentHeight = newHeight;

			setProjection();
		}

		glm::mat4 model(1.0f);

		model = glm::translate(model, 
			glm::vec3(_position.x * m_currentWidth, _position.y * m_currentHeight, _position.z));
		model = glm::scale(model, 
			glm::vec3(_size.x * m_currentWidth, _size.y * m_currentHeight, 1));

		m_staticShader->m_internal->setUniform("in_Model", model);
		m_staticShader->m_internal->setUniform("in_Texture", _image->m_internal);

		m_staticShader->m_internal->draw();
	}

	void Canvas::drawTextureInWorld(std::shared_ptr<Texture> _image, glm::vec3 _position, glm::vec3 _size)
	{
		int newWidth = m_environment.lock()->getWidth();
		int newHeight = m_environment.lock()->getHeight();

		if (!(m_currentWidth == newWidth && m_currentHeight == newHeight))
		{
			m_currentWidth = newWidth;
			m_currentHeight = newHeight;

			setProjection();
		}

		glm::mat4 model(1.0f);

		std::shared_ptr<Camera> currentCam = m_core.lock()->getCurrentCamera();

		model = glm::translate(model,
			glm::vec3(_position.x, _position.y, _position.z));
		model = model * glm::mat4(currentCam->m_rotation);
		model = glm::scale(model,
			glm::vec3(_size.x, _size.y, 1));

		model = glm::inverse(m_projection) * currentCam->getProjection() * glm::inverse(currentCam->getView()) * model;

		m_staticShader->m_internal->setUniform("in_Model", model);
		m_staticShader->m_internal->setUniform("in_Texture", _image->m_internal);

		m_staticShader->m_internal->draw();
	}

	void Canvas::addButton(std::shared_ptr<Entity> _button)
	{
		std::shared_ptr<ButtonGUI> btn = _button->getComponent<ButtonGUI>();
		if (btn)
		{
			for (std::list<std::weak_ptr<Entity> >::iterator itr = m_buttonList.begin();
				itr != m_buttonList.end(); itr++)
			{
				if ((*itr).lock() == _button)
				{
				return;
				}
			}

			m_buttonList.push_back(_button);
		}
	}

	void Canvas::removeButton(std::shared_ptr<Entity> _button)
	{
		std::shared_ptr<ButtonGUI> btn = _button->getComponent<ButtonGUI>();
		if (btn)
		{
			for (std::list<std::weak_ptr<Entity> >::iterator itr = m_buttonList.begin();
				itr != m_buttonList.end(); itr++)
			{
				if ((*itr).lock() == _button)
				{
					itr = m_buttonList.erase(itr);
					return;
				}
			}
		}
	}

	void Canvas::queryButton()
	{
		std::shared_ptr<Mouse> mouse = m_core.lock()->getMouse();
		std::shared_ptr<Camera> currentCam = m_core.lock()->getCurrentCamera();
		glm::vec2 mousePos = mouse->getPosition();
		glm::vec4 camPos = glm::vec4(currentCam->m_position, 1);

		//glm::vec3 dirProj = mouse->getRayDirection();

		std::shared_ptr<ButtonGUI> button;

		// float origin[3], direction[3], coords[3][3];
		float boxA[3], boxASize[3], boxB[3], boxBSize[3];

		std::list<glm::vec3> positions;

		{
			//origin[0] = camPos.x;
			//origin[1] = camPos.y;
			//origin[2] = camPos.z;

			//direction[0] = dirProj.x;
			//direction[1] = dirProj.y;
			//direction[2] = dirProj.z;

			//positions.push_back(glm::vec3(-1.0f, 1.0f, 0));
			//positions.push_back(glm::vec3(-1.0f, -1.0f, 0));
			//positions.push_back(glm::vec3(1.0f, -1.0f, 0));
			//positions.push_back(glm::vec3(1.0f, -1.0f, 0));
			//positions.push_back(glm::vec3(1.0f, 1.0f, 0));
			//positions.push_back(glm::vec3(-1.0f, 1.0f, 0));

			boxA[0] = mousePos.x / m_environment.lock()->getWidth();
			boxA[1] = mousePos.y / m_environment.lock()->getHeight();
			boxA[2] = 0;

			boxASize[0] = 1;
			boxASize[1] = 1;
			boxASize[2] = 1;
		}

		glm::vec3 coordCalc, boxPos, boxScale;
		glm::mat4 buttonModel;

		float distance;
		float shortestDistance = -1;
		std::shared_ptr<Entity> currentButton;

		for (std::list<std::weak_ptr<Entity> >::iterator itr = m_buttonList.begin();
			itr != m_buttonList.end(); itr++)
		{
			button = (*itr).lock()->getComponent<ButtonGUI>();

			if (button->m_isWorldGUI)
			{
				/**
				* INSERT
				* Call to ButtonGUI function which tests for ray intersection
				* Virtual function allows for different shaped buttons e.g. circles, modelled buttons
				*/
			}
			else
			{
				boxPos = button->m_transform.lock()->m_position;
				boxScale = button->m_transform.lock()->m_scale;

				boxB[0] = boxPos.x;
				boxB[1] = boxPos.y;
				boxB[2] = boxPos.z;

				boxBSize[0] = boxScale.x;
				boxBSize[1] = boxScale.y;
				boxBSize[2] = 1;

				distance = aabb(boxA, boxASize, boxB, boxBSize);
			}

			if ((distance < shortestDistance || shortestDistance < 0.0f) && distance > 0.0f)
			{
				shortestDistance = distance;
				currentButton = (*itr).lock();
			}
		}

		// Check if button is highlighted
		if (shortestDistance > 0)
		{
			if (m_currentButton.lock() != currentButton)
			{
				if (m_currentButton.lock())
				{
					m_currentButton.lock()->getComponent<ButtonGUI>()->m_isHighlighted = false;
				}
				m_currentButton = currentButton;
				if (m_currentButton.lock())
				{
					m_currentButton.lock()->getComponent<ButtonGUI>()->m_isHighlighted = true;
				}
			}
		}
		else
		{
			m_currentButton.lock()->getComponent<ButtonGUI>()->m_isHighlighted = false;
			m_currentButton.lock() = NULL;
		}

		// Press and release button if necessary
		// If released while highlighted, button is activated
		if (mouse->isButtonPressed(cobebeInput::leftClick) && m_currentButton.lock())
		{
			if (m_clickedButton.lock())
			{
				m_currentButton.lock()->getComponent<ButtonGUI>()->m_isClicked = false;
			}
			m_currentButton.lock()->getComponent<ButtonGUI>()->m_isClicked = true;
		}

		if (mouse->isButtonReleased(cobebeInput::leftClick) && m_clickedButton.lock())
		{
			button = m_clickedButton.lock()->getComponent<ButtonGUI>();
			button->m_isClicked = false;
			if (button->m_isHighlighted)
			{
				button->activate();
			}
			m_clickedButton.lock() = NULL;
		}
	}

	void Canvas::switchButton(std::shared_ptr<Entity> _button)
	{
		for (std::list<std::weak_ptr<Entity> >::iterator itr = m_buttonList.begin();
			itr != m_buttonList.end(); itr++)
		{
			if ((*itr).lock() == _button)
			{
				if (m_currentButton.lock())
				{
					m_currentButton.lock()->getComponent<ButtonGUI>()->m_isHighlighted = false;
				}
				m_currentButton = _button;
				if (m_currentButton.lock())
				{
					m_currentButton.lock()->getComponent<ButtonGUI>()->m_isHighlighted = true;
				}
				return;
			}
		}
	}

	void Canvas::scrollButton(bool _toNext)
	{
		bool found = false;

		for (std::list<std::weak_ptr<Entity> >::iterator itr = m_buttonList.begin();
			itr != m_buttonList.end(); itr++)
		{
			if (_toNext && found)
			{
				if (m_currentButton.lock())
				{
					m_currentButton.lock()->getComponent<ButtonGUI>()->m_isHighlighted = false;
				}
				m_currentButton = (*itr);
				if (m_currentButton.lock())
				{
					m_currentButton.lock()->getComponent<ButtonGUI>()->m_isHighlighted = true;
				}
				return;
			}
			if ((*itr).lock() == m_currentButton.lock())
			{
				found = true;
			}
			if (!_toNext && found)
			{
				itr--;
				if (m_currentButton.lock())
				{
					m_currentButton.lock()->getComponent<ButtonGUI>()->m_isHighlighted = false;
				}
				m_currentButton = (*itr);
				if (m_currentButton.lock())
				{
					m_currentButton.lock()->getComponent<ButtonGUI>()->m_isHighlighted = true;
				}
				return;
			}
		}
	}

	std::shared_ptr<Entity> Canvas::getHighlighted()
	{
		return m_currentButton.lock();
	}

	void Canvas::setProjection()
	{
		m_projection = glm::ortho(0.0f,
			(float)m_currentWidth, 0.0f, (float)m_currentHeight, -1.0f, 1.0f);

		m_staticShader->m_internal->setUniform("in_Projection", m_projection);
		m_staticShader->m_internal->setViewport(glm::vec4(0, 0, m_currentWidth, m_currentHeight));
	}

	void Canvas::onInit()
	{
		m_environment = m_core.lock()->getEnvironment();

		m_currentWidth = m_environment.lock()->getWidth();
		m_currentHeight = m_environment.lock()->getHeight();

		m_staticShader = m_core.lock()->loadAsset<Shader>("shaders\\static.shad");

		setProjection();
	}
}