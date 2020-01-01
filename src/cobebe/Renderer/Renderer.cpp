#include <cobebe/Renderer/Renderer.h>
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
		m_transform = getEntity()->getComponent<Transform>();
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

	void Renderer::onDisplay()
	{
		if (m_mesh && m_texture && m_shader)
		{
			glm::mat4 model = glm::inverse(m_transform.lock()->getModel());
			m_shader->m_internal->setUniform("in_Model", model);
			m_shader->m_internal->setUniform("in_Texture", m_texture->m_internal);
			if (m_camera)
			{
				m_shader->m_internal->setUniform("in_View", glm::inverse(m_camera->getView()));
				m_shader->m_internal->setUniform("in_Projection", m_camera->getProjection());
				m_camera->draw(m_shader->m_internal, m_mesh->m_internal);
			}
			else
			{
				std::shared_ptr<Camera> currentCam = getCore()->getCurrentCamera();

				m_shader->m_internal->setUniform("in_View", glm::inverse(currentCam->getView()));
				m_shader->m_internal->setUniform("in_Projection", currentCam->getProjection());
				currentCam->draw(m_shader->m_internal, m_mesh->m_internal);
			}
		}
	}
}