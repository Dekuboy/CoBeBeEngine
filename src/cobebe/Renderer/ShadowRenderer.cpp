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
			if (!m_shader->getUniformCheck())
			{
				m_lighting->setDepthBuffer(m_shader);
				m_shader->setAmbient(m_lighting->getGlobalLightAmbient());
				m_shader->setLightDir(m_lighting->getGlobalLightDir());
				//m_shader->setLightPos(m_lighting->getGlobalLightPos());
				m_shader->setLightSpace(m_lighting->getGlobalLightSpace());

				m_shader->setUniformCheck(true);
			}
		}
		Renderer::onPreDisplay();
	}

	void ShadowRenderer::onDisplay()
	{
		if (m_shader)
		{
			if (!m_shader->getShadowCheck())
			{
				m_shader->setLightCol(m_lighting->getGlobalLightCol());

				m_lighting->setPointLightRCount(m_shader);
				m_lighting->setDepthCubes(m_shader);
				m_lighting->setPointPositions(m_shader);
				m_lighting->setPointColours(m_shader);
				m_lighting->setFarPlanes(m_shader);

				m_shader->setShadowCheck(true);
			}
		}
		Renderer::onDisplay();
	}
}