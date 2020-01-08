#include <cobebe/Resources/RendAssets.h>

namespace cobebe
{
	std::vector<std::shared_ptr<glwrap::Face>> Mesh::getFaces()
	{
		return m_internal->getFaces();
	}

	void Mesh::onLoad(const std::string& _path)
	{
		m_path = _path;
		m_internal = m_context.lock()->createMesh(_path);
	}

	void Texture::onLoad(const std::string& _path)
	{
		m_path = _path;
		m_internal = m_context.lock()->createTexture(_path);
	}

	void Shader::setEmissive(glm::vec3 _emissive)
	{
		m_internal->setUniform("in_Emissive", _emissive);
	}

	void Shader::setAmbient(glm::vec3 _ambient)
	{
		m_internal->setUniform("in_Ambient", _ambient);
	}

	void Shader::setLightPos(glm::vec3 _lightPos)
	{
		m_internal->setUniform("in_LightPos", _lightPos);
	}

	void Shader::setLightDir(glm::vec3 _lightDir)
	{
		if (_lightDir != glm::vec3(0, 0, 0))
		{
			m_internal->setUniform("in_LightDir", -_lightDir);
		}
	}

	void Shader::setLightSpace(glm::mat4 _lightSpace)
	{
		m_internal->setUniform("in_LightSpace", _lightSpace);
	}

	bool Shader::getUniformCheck()
	{
		return m_uniformCheck;
	}

	void Shader::setUniformCheck(bool _switch)
	{
		m_uniformCheck = _switch;
	}

	void Shader::onLoad(const std::string& _path)
	{
		m_path = _path;
		m_internal = m_context.lock()->createShader(_path);
	}
}