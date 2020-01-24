#include <cobebe/Renderer/Renderer.h>
#include <cobebe/Renderer/Lighting.h>
#include <cobebe/Core/Transform.h>
#include <cobebe/Core/Entity.h>
#include <cobebe/Core/Core.h>
#include <cobebe/Resources/Resources.h>
#include <cobebe/Resources/RendAssets.h>
#include <cobebe/Core/Camera.h>

namespace cobebe
{
	void Renderer::onInit()
	{
		m_transform = getTransform();
		m_lighting = getLighting();
	}

	void Renderer::setCamera(std::shared_ptr<Camera> _camera)
	{
		m_camera = _camera;
	}

	void Renderer::setMesh(std::shared_ptr<Mesh> _mesh)
	{
		m_mesh = _mesh;
	}

	void Renderer::setMesh(std::string _path)
	{
		m_mesh = getCore()->loadAsset<Mesh>(_path);
	}

	void Renderer::setTexture(std::shared_ptr<Texture> _texture)
	{
		m_texture = _texture;
	}

	void Renderer::setTexture(std::string _path)
	{
		m_texture = getCore()->loadAsset<Texture>(_path);
	}

	void Renderer::setShader(std::shared_ptr<Shader> _shader)
	{
		m_shader = _shader;
	}

	void Renderer::setShader(std::string _path)
	{
		m_shader = getCore()->loadAsset<Shader>(_path);
	}

	std::shared_ptr<Mesh> Renderer::getMesh()
	{
		return m_mesh;
	}

	void Renderer::onTick()
	{
		m_shader->resetChecks();
	}

	void Renderer::onPreDisplay()
	{
		if (m_shader)
		{
			if (!m_shader->getUniformCheck())
			{
				//m_shader->setEmissive(m_lighting->getGlobalLightEmissive());
				//m_shader->setAmbient(m_lighting->getGlobalLightAmbient());
				//m_shader->setLightDir(m_lighting->getGlobalLightDir());
				//m_shader->setLightPos(m_lighting->getGlobalLightPos());

				m_shader->setUniformCheck(true);
			}
		}
		if (m_mesh && m_texture && m_shader)
		{
			glm::mat4 model = m_transform.lock()->getModel();
			m_lighting->draw(m_mesh->m_internal, model);
		}
	}

	void Renderer::onDisplay()
	{
		if (m_mesh && m_texture && m_shader)
		{
			glm::mat4 model = m_transform.lock()->getModel();
			m_shader->m_internal->setUniform("in_Model", model);
			m_shader->m_internal->setUniform("in_Texture", m_texture->m_internal);
			if (m_camera)
			{
				m_shader->setCam(m_camera);
				m_camera->draw(m_shader->m_internal, m_mesh->m_internal);
			}
			else
			{
				std::shared_ptr<Camera> currentCam = getCore()->getCurrentCamera();

				m_shader->setCam(currentCam);
				currentCam->draw(m_shader->m_internal, m_mesh->m_internal);
			}
		}
	}
}