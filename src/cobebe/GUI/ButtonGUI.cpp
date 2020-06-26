#include <cobebe/GUI/ButtonGUI.h>
#include <cobebe/Resources/RendAssets.h>
#include <cobebe/Core/Core.h>
#include <cobebe/GUI/Canvas.h>
#include <cobebe/Core/Transform.h>

namespace cobebe
{
	void ButtonGUI::setTextureStatic(std::string _path)
	{
		m_textureStatic = getCore()->loadAsset<Texture>(_path);
	}

	void ButtonGUI::setTextureStatic(std::shared_ptr<Texture> _texture)
	{
		m_textureStatic = _texture;
	}

	void ButtonGUI::setTextureHighlighted(std::string _path)
	{
		m_textureHighlighted = getCore()->loadAsset<Texture>(_path);
	}

	void ButtonGUI::setTextureHighlighted(std::shared_ptr<Texture> _texture)
	{
		m_textureHighlighted = _texture;
	}

	void ButtonGUI::SetTexturePressed(std::string _path)
	{
		m_texturePressed = getCore()->loadAsset<Texture>(_path);
	}

	void ButtonGUI::setTexturePressed(std::shared_ptr<Texture> _texture)
	{
		m_texturePressed = _texture;
	}

	void ButtonGUI::setWorldGUI(bool _switch)
	{
		m_isWorldGUI = _switch;
	}

	void ButtonGUI::setInCanvas(bool _switch)
	{
		if (_switch)
		{
			m_canvas->addButton(getEntity());
		}
		else
		{
			m_canvas->removeButton(getEntity());
		}
	}

	float ButtonGUI::checkHighlight()
	{
		return 0.0f;
	}

	void ButtonGUI::activate()
	{

	}

	void ButtonGUI::onInit()
	{
		m_transform = getTransform();
		m_canvas = getCore()->getCanvas();
		m_isHighlighted = false;
		m_isClicked = false;

		m_isWorldGUI = false;
	}

	void ButtonGUI::onTick()
	{

	}

	void ButtonGUI::onGUI()
	{
		std::shared_ptr<Texture> texture;
		if (m_isHighlighted)
		{
			if (m_isClicked)
			{
				texture = m_texturePressed;
			}
			else
			{
				texture = m_textureHighlighted;
			}
		}
		else
		{
			texture = m_textureStatic;
		}

		if (texture)
		{
			if (m_isWorldGUI)
			{
				m_canvas->drawTextureInWorld(texture,
					m_transform.lock()->m_position, m_transform.lock()->m_scale);
			}
			else
			{
				m_canvas->drawTexture(texture,
					m_transform.lock()->m_position, m_transform.lock()->m_scale);
			}
		}
	}
}