#include <cobebe/Renderer/PBRenderer.h>
#include <cobebe/Core/Core.h>
#include <cobebe/Resources/RendAssets.h>

namespace cobebe
{
	void PBRenderer::setNormalMap(std::shared_ptr<Texture> _texture)
	{
		m_normalMap = _texture;
	}

	void PBRenderer::setNormalMap(std::string _path)
	{
		m_normalMap = getCore()->loadAsset<Texture>(_path);
	}

	void PBRenderer::setMetalMap(std::shared_ptr<Texture> _texture)
	{
		m_metalMap = _texture;
	}

	void PBRenderer::setMetalMap(std::string _path)
	{
		m_metalMap = getCore()->loadAsset<Texture>(_path);
	}

	void PBRenderer::setRoughMap(std::shared_ptr<Texture> _texture)
	{
		m_roughMap = _texture;
	}

	void PBRenderer::setRoughMap(std::string _path)
	{
		m_roughMap = getCore()->loadAsset<Texture>(_path);
	}

	void PBRenderer::setAoMap(std::shared_ptr<Texture> _texture)
	{
		m_aoMap = _texture;
	}

	void PBRenderer::setAoMap(std::string _path)
	{
		m_aoMap = getCore()->loadAsset<Texture>(_path);
	}

	void PBRenderer::onPreDisplay()
	{
		if (m_shader)
		{
			if (!m_shader->getUniformCheck())
			{
				m_shader->setUniformCheck(true);
			}
		}
		Renderer::onPreDisplay();
	}

	void PBRenderer::onDisplay()
	{
		if (m_mesh && m_texture && m_shader)
		{
			std::shared_ptr<glwrap::ShaderProgram> internalShader = m_shader->getInternal();
			if (m_normalMap)
			{
				internalShader->setUniform("in_NormMap", getTextureInternal(m_normalMap));
			}
			if (m_metalMap)
			{
				internalShader->setUniform("in_MetalMap", getTextureInternal(m_metalMap));
			}
			if (m_roughMap)
			{
				internalShader->setUniform("in_RoughMap", getTextureInternal(m_roughMap));
			}
			if (m_aoMap)
			{
				internalShader->setUniform("in_AoMap", getTextureInternal(m_aoMap));
			}
		}
		Renderer::onDisplay();
	}
}