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

	void Lighting::setGlobalLightPos(glm::vec3 _position)
	{
		m_globalLightPos = _position;
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

	void Lighting::setPointLightRCount(std::shared_ptr<Shader> _shadowShader)
	{
		_shadowShader->setPointLightCount(m_depthCubes.size());
	}

	void Lighting::setDepthCubes(std::shared_ptr<Shader> _shadowShader)
	{
		_shadowShader->setDepthCubes(m_depthCubes);
	}

	void Lighting::setPointPositions(std::shared_ptr<Shader> _shadowShader)
	{
		_shadowShader->setPointLightPositions(m_pointLightPositions);
	}

	void Lighting::setPointColours(std::shared_ptr<Shader> _shadowShader)
	{
		_shadowShader->setPointLightColours(m_pointColours);
	}

	void Lighting::setFarPlanes(std::shared_ptr<Shader> _shadowShader)
	{
		_shadowShader->setFarPlanes(m_farPlanes);
	}

	std::shared_ptr<PointLight> Lighting::addPointLight()
	{
		if (m_pointLights.size() < m_maxPointLights)
		{
			std::shared_ptr<PointLight> light = std::make_shared<PointLight>();
			light->m_core = m_core;

			m_pointLights.push_back(light);
			m_depthCubes.push_back(light->m_depthCube);

			return light;
		}
		return NULL;
	}

	std::shared_ptr<PointLight> Lighting::addPointLight(glm::vec3 _position,
		glm::vec3 _colour, float _radius)
	{
		if (m_pointLights.size() < m_maxPointLights)
		{
			std::shared_ptr<PointLight> light = std::make_shared<PointLight>();
			light->m_core = m_core;

			light->m_position = _position;
			light->setColour(_colour);
			light->setRadius(_radius);

			m_pointLights.push_back(light);
			m_depthCubes.push_back(light->m_depthCube);

			return light;
		}
		return NULL;
	}

	std::list<std::shared_ptr<PointLight>> Lighting::getPointLights()
	{
		return m_pointLights;
	}

	void Lighting::removePointLight(std::shared_ptr<PointLight> _light)
	{
		if (_light)
		{
			int count = 0;
			for (std::list<std::shared_ptr<PointLight>>::iterator it = m_pointLights.begin();
				it != m_pointLights.end();)
			{
				if (_light == (*it))
				{
					it = m_pointLights.erase(it);
					std::vector<std::shared_ptr<glwrap::DepthCube>>::iterator
						dc = m_depthCubes.begin() + count;
					m_depthCubes.erase(dc);
					return;
				}
				count++;
			}
		}
	}

	void Lighting::emptyPointLights()
	{
		m_pointLights.clear();
		m_depthCubes.clear();
		addPointLight(glm::vec3(0), glm::vec3(0), 1);
	}

	void Lighting::setDepthBuffer(std::shared_ptr<Shader> _shadowShader)
	{
		_shadowShader->m_internal->setUniform("in_DepthBuff", m_depthMap);
	}

	void Lighting::draw(std::shared_ptr<glwrap::VertexArray> _meshInternal,
		glm::mat4 _modelMat)
	{
		ShadowModel tempModel;
		tempModel.m_mesh = _meshInternal;
		tempModel.m_model = _modelMat;
		m_shadowModels.push_back(tempModel);
	}

	void Lighting::setGlobalLightPos(std::shared_ptr<Camera> _camera)
	{
		//_camera->

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

		for (std::list<std::shared_ptr<PointLight>>::iterator it = m_pointLights.begin();
			it != m_pointLights.end(); it++)
		{
			(*it)->m_depthCube->clear();
		}

		// Vectors must clear as PointLights may change values after tick
		m_pointLightPositions.clear();
		m_pointColours.clear();
		m_farPlanes.clear();
	}

	void Lighting::onInit()
	{
		// Temporary max PointLights set to current value in shader
		m_maxPointLights = 10;

		// Set global directional light values
		m_globalLightDir = glm::normalize(glm::vec3(0.0f, -0.3f, 1.0f));;
		m_globalLightCol = glm::vec3(0.3f);
		m_globalLightEmissive = glm::vec3(0.0f);
		m_globalLightAmbient = glm::vec3(0.1f);

		m_globalLightRenderDistance = 25.0f;

		// Set depth map ready for rendering
		m_depthMap = std::make_shared<glwrap::DepthBuffer>(512, 512);
		m_depthShader = m_core.lock()->loadAsset<Shader>("shadows\\shadow.shad");
		m_cubeShader = m_core.lock()->loadAsset<Shader>("shadows\\shadowCube.shad");

		// Set light space matrix
		glm::mat4 lightProjection = glm::ortho(-10.0f, 10.0f,
			-10.0f, 10.0f, 1.0f, m_globalLightRenderDistance);

		m_globalLightPos = glm::vec3(-12, 2, -5);

		glm::mat4 lightView = glm::lookAt(m_globalLightPos,
			m_globalLightPos + m_globalLightDir,
			glm::vec3(0.0f, 1.0f, 0.0f));

		m_globalLightSpace = lightProjection * lightView;

		m_depthShader->setLightSpace(m_globalLightSpace);

		// Lighting must have 1 PointLight, even if it has no colour
		std::shared_ptr<PointLight> light = addPointLight(
			glm::vec3(-12, 2, -5), glm::vec3(0.2f), 25.0f);
	}

	void Lighting::drawLighting()
	{
		// Draws to global directional light depth map
		for (std::list<ShadowModel>::iterator it = m_shadowModels.begin();
			it != m_shadowModels.end(); it++)
		{
			m_depthShader->m_internal->setUniform("in_Model", (*it).m_model);
			m_depthShader->m_internal->draw(m_depthMap, (*it).m_mesh.lock());
		}

		// Iterates through each PointLight
		// Sets cube light space matrices once per shader
		// -avoids setting once per shader per model
		for (std::list<std::shared_ptr<PointLight>>::iterator pointIt = m_pointLights.begin();
			pointIt != m_pointLights.end(); pointIt++)
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			m_pointLightPositions.push_back((*pointIt)->m_position);
			m_pointColours.push_back((*pointIt)->m_colour);
			m_farPlanes.push_back((*pointIt)->m_radius);

			m_cubeShader->setLightSpace((*pointIt)->m_lightSpaces);
			m_cubeShader->m_internal->setUniform("in_FarPlane", (*pointIt)->m_radius);
			m_cubeShader->setLightPos((*pointIt)->m_position);

			// Draws to PointLight depth map
			for (std::list<ShadowModel>::iterator it = m_shadowModels.begin();
				it != m_shadowModels.end(); it++)
			{
				m_cubeShader->m_internal->setUniform("in_Model", (*it).m_model);
				m_cubeShader->m_internal->draw((*pointIt)->m_depthCube, (*it).m_mesh.lock());
			}
		}

		// Deletes models to prepare for next display
		m_shadowModels.clear();
	}
}