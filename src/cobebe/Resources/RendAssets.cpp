#include <cobebe/Resources/RendAssets.h>
#include <cobebe/Core/Camera.h>

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

	void Shader::setLightCol(glm::vec3 _lightCol)
	{
		m_internal->setUniform("in_GlobalLightCol", _lightCol);
	}

	void Shader::setLightSpace(glm::mat4 _lightSpace)
	{
		m_internal->setUniform("in_GlobalLightSpace", _lightSpace);
	}

	void Shader::setLightSpace(std::vector<glm::mat4> _lightSpace)
	{
		m_internal->setUniform("in_LightSpace", _lightSpace);
	}

	void Shader::setPointLightCount(int _count)
	{
		m_internal->setUniform("in_PointTotal", _count);
	}

	void Shader::setDepthCubes(std::vector<std::shared_ptr<glwrap::DepthCube>> _depthCubes)
	{
		m_internal->setUniform("in_DepthMap", _depthCubes);
	}

	void Shader::setPointLightPositions(std::vector<glm::vec3> _pointLightPositions)
	{
		m_internal->setUniform("in_LightPos", _pointLightPositions);
	}

	void Shader::setPointLightColours(std::vector<glm::vec3> _pointColours)
	{
		m_internal->setUniform("in_LightCol", _pointColours);
	}

	void Shader::setFarPlanes(std::vector<float> _farPlanes)
	{
		m_internal->setUniform("in_FarPlane", _farPlanes);
	}

	bool Shader::getUniformCheck()
	{
		return m_uniformCheck;
	}

	void Shader::setUniformCheck(bool _switch)
	{
		m_uniformCheck = _switch;
	}

	bool Shader::getShadowCheck()
	{
		return m_shadowCheck;
	}

	void Shader::setShadowCheck(bool _switch)
	{
		m_shadowCheck = _switch;
	}

	void Shader::setCam(std::shared_ptr<Camera> _camera)
	{
		if (_camera != m_camSet)
		{
			m_internal->setUniform("in_View", glm::inverse(_camera->getView()));
			m_internal->setUniform("in_Projection", _camera->getProjection());
			m_camSet = _camera;
		}
	}

	void Shader::resetChecks()
	{
		if (m_uniformCheck)
		{
			setUniformCheck(false);
			setShadowCheck(false);

			m_camSet = NULL;
		}
	}

	void Shader::onLoad(const std::string& _path)
	{
		m_path = _path;
		m_internal = m_context.lock()->createShader(_path);
		m_uniformCheck = false;
		m_shadowCheck = false;
	}
}