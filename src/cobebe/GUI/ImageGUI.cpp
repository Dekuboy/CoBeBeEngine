#include <cobebe/GUI/ImageGUI.h>
#include <cobebe/Resources/RendAssets.h>
#include <cobebe/Core/Core.h>
#include <cobebe/Core/Transform.h>
#include <cobebe/GUI/Canvas.h>

namespace cobebe
{
	void ImageGUI::setTexture(std::string _path)
	{
		m_texture = getCore()->loadAsset<Texture>(_path);
	}

	void ImageGUI::setTexture(std::shared_ptr<Texture> _texture)
	{
		m_texture = _texture;
	}

	void ImageGUI::onInit()
	{
		m_transform = getTransform();
		m_canvas = getCore()->getCanvas();
	}

	void ImageGUI::onGUI()
	{
		if (m_texture)
		{
			m_canvas->drawTexture(m_texture, 
				m_transform.lock()->m_position, m_transform.lock()->m_scale);
		}
	}
}