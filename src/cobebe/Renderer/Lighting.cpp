#include <cobebe/Renderer/Lighting.h>
#include <cobebe/Renderer/PointLight.h>
#include <cobebe/Resources/Resources.h>
#include <cobebe/Resources/RendAssets.h>
#include <cobebe/Core/Core.h>
#include <cobebe/Core/Camera.h>
#include <glm/ext.hpp>

namespace cobebe
{
	glm::vec3 Lighting::getGlobalLightPos()
	{
		return m_globalLightPos;
	}

	glm::vec3 Lighting::getGlobalLightDir()
	{
		return m_globalLightDir;
	}

	void Lighting::setGlobalLightDir(glm::vec3 _lightDir)
	{
		if (_lightDir != glm::vec3(0, 0, 0))
		{
			m_globalLightDir = glm::normalize(_lightDir);
		}
	}

	glm::vec3 Lighting::getGlobalLightCol()
	{
		return m_globalLightCol;
	}

	void Lighting::setGlobalLightCol(glm::vec3 _lightCol)
	{
		if (_lightCol != glm::vec3(0, 0, 0))
		{
			m_globalLightCol = _lightCol;
		}
	}

	glm::vec3 Lighting::getGlobalLightEmissive()
	{
		return m_globalLightEmissive;
	}

	void Lighting::setGlobalLightEmissive(glm::vec3 _lightEmissive)
	{
		m_globalLightEmissive = _lightEmissive;
	}

	glm::vec3 Lighting::getGlobalLightAmbient()
	{
		return m_globalLightAmbient;
	}

	void Lighting::setGlobalLightAmbient(glm::vec3 _lightAmbient)
	{
		m_globalLightAmbient = _lightAmbient;
	}

	glm::mat4 Lighting::getGlobalLightSpace()
	{
		return m_globalLightSpace;
	}

	std::shared_ptr<PointLight> Lighting::addPointLight(glm::vec3 _position,
		glm::vec3 _colour, float _radius)
	{
		std::shared_ptr<PointLight> light;
		return light;
	}

	std::list<std::shared_ptr<PointLight>> Lighting::getPointLights()
	{
		return m_pointLights;
	}

	void Lighting::setDepthBuffer(std::shared_ptr<Shader> _shadowShader)
	{
		_shadowShader->m_internal->setUniform("in_DepthMap", m_depthMap);
	}

	void Lighting::draw(std::shared_ptr<glwrap::VertexArray> _meshInternal,
		glm::mat4 _modelMat)
	{
		m_depthShader->m_internal->setUniform("in_Model", _modelMat);
		m_depthShader->m_internal->draw(m_depthMap, _meshInternal);
	}

	void Lighting::setGlobalLightPos(std::shared_ptr<Camera> _camera)
	{
		_camera->

		glm::mat4 lightProjection = glm::ortho(-10.0f, 10.0f,
			-10.0f, 10.0f, 1.0f, m_globalLightRenderDistance);

		glm::mat4 lightView = glm::lookAt(m_globalLightPos,
			m_globalLightPos + m_globalLightDir,
			glm::vec3(0.0f, 1.0f, 0.0f));

		m_globalLightSpace = lightProjection * lightView;

		m_depthShader->setLightSpace(m_globalLightSpace);
	}

	void Lighting::clear()
	{
		m_depthMap->clear();
	}

	void Lighting::onInit()
	{
		m_globalLightDir = glm::normalize(glm::vec3(0.0f, -0.3f, 1.0f));;
		m_globalLightCol = glm::vec3(0.5f);
		m_globalLightEmissive = glm::vec3(0.0f);
		m_globalLightAmbient = glm::vec3(0.1f);

		m_globalLightRenderDistance = 10.0f;

		m_depthMap = std::make_shared<glwrap::DepthBuffer>(2048, 2048);
		m_depthShader = m_core.lock()->loadAsset<Shader>("shadows\\shadow.shad");

		glm::mat4 lightProjection = glm::ortho(-10.0f, 10.0f,
			-10.0f, 10.0f, 1.0f, m_globalLightRenderDistance);

		m_globalLightPos = glm::vec3(-12, 2, -5);

		glm::mat4 lightView = glm::lookAt(m_globalLightPos,
			m_globalLightPos + m_globalLightDir,
			glm::vec3(0.0f, 1.0f, 0.0f));

		m_globalLightSpace = lightProjection * lightView;

		m_depthShader->setLightSpace(m_globalLightSpace);
	}
}