#include <cobebe/Resources/RendAssets.h>

namespace cobebe
{
	std::vector<std::shared_ptr<glwrap::Face>> Mesh::getFaces()
	{
		return m_internal->getFaces();
	}

	void Mesh::onLoad(const std::string& _path)
	{
		m_internal = m_context.lock()->createMesh(_path);
	}

	void Texture::onLoad(const std::string& _path)
	{
		m_internal = m_context.lock()->createTexture(_path);
	}

	void Shader::onLoad(const std::string& _path)
	{
		m_internal = m_context.lock()->createShader(_path);
		m_internal->setUniform("in_Emissive", glm::vec3(0, 0, 0));
		m_internal->setUniform("in_Ambient", glm::vec3(0.1, 0.1, 0.1));
		//m_environmentShader->setUniform("in_LightPos", lightPosition);
		m_internal->setUniform("in_LightDir", glm::normalize(glm::vec3(0, 1, 1)));
	}
}