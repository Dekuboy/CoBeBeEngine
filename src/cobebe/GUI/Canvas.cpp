#include <cobebe/GUI/Canvas.h>
#include <cobebe/Core/Environment.h>
#include <cobebe/Core/Core.h>
#include <cobebe/Resources/Resources.h>
#include <cobebe/Resources/RendAssets.h>
#include <glm/ext.hpp>

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