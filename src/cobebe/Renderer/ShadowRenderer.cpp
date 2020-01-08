#include <cobebe/Renderer/ShadowRenderer.h>
#include <cobebe/Renderer/Lighting.h>
#include <cobebe/Core/Transform.h>
#include <cobebe/Resources/Resources.h>
#include <cobebe/Resources/RendAssets.h>

namespace cobebe
{
	void ShadowRenderer::onPreDisplay()
	{
		if (m_shader)
		{
			m_lighting->setDepthBuffer(m_shader);
			if (!m_shader->getUniformCheck())
			{
				//m_shader->setEmissive(m_lighting->getGlobalLightEmissive());
				m_shader->setAmbient(m_lighting->getGlobalLightAmbient());
				m_shader->setLightDir(m_lighting->getGlobalLightDir());
				//m_shader->setLightPos(m_lighting->getGlobalLightPos());
				m_shader->setLightSpace(m_lighting->getGlobalLightSpace());

				m_shader->setUniformCheck(true);
			}
		}
		Renderer::onPreDisplay();
	}
}