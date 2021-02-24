#include <cobebe/Renderer/Renderer.h>
#include <cobebe/Renderer/Lighting.h>
#include <cobebe/Core/Transform.h>
#include <cobebe/Core/Entity.h>
#include <cobebe/Core/Core.h>
#include <cobebe/Resources/RendAssets.h>
#include <cobebe/Core/Camera.h>
#include <cobebe/Renderer/ObjAnimationController.h>

namespace cobebe
{
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

	void Renderer::setWavefrontModel(std::shared_ptr<WavefrontModel> _wavefrontModel)
	{
		m_objMtlModel = _wavefrontModel;
	}

	void Renderer::setWavefrontModel(std::string _path)
	{
		m_objMtlModel = getCore()->loadAsset<WavefrontModel>(_path);
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

	void Renderer::setCullByPart(bool _switch)
	{
		m_cullByPart = _switch;
	}

	std::shared_ptr<Mesh> Renderer::getMesh()
	{
		return m_mesh;
	}

	std::shared_ptr<WavefrontModel> Renderer::getWavefrontModel()
	{
		return m_objMtlModel;
	}

	std::shared_ptr<ObjAnimationController> Renderer::addAnimationController()
	{
		if (m_mesh)
		{
			m_animationController = getEntity()->addComponent<ObjAnimationController>(m_mesh->m_internal);
			return m_animationController;
		}
		return nullptr;
	}

	void Renderer::loadAnimation(std::string _path)
	{
		if (m_animationController)
		{
			m_animationController->loadAnimation(_path);
		}
	}

	std::shared_ptr<glwrap::Texture> Renderer::getTextureInternal(std::shared_ptr<Texture> _texture)
	{
		return _texture->m_internal;
	}

	void Renderer::onInit()
	{
		m_transform = getTransform();
		m_lighting = getLighting();
		m_cullByPart = false;
	}

	void Renderer::onTick()
	{
		if (m_shader)
		{
			m_shader->resetChecks();
		}
	}

	void Renderer::onPreDisplay()
	{
		if (m_shader)
		{
			if (!m_shader->getUniformCheck())
			{
				m_shader->setUniformCheck(true);
			}
			if (m_mesh && m_texture)
			{
				glm::mat4 model = m_transform.lock()->getModel();
				if (m_cullByPart)
				{
					m_lighting->draw(m_mesh->m_internal, m_animationController, model);
				}
				else
				{
					m_lighting->draw(m_mesh->m_internal, m_animationController, model);
				}
			}
			else if (m_objMtlModel)
			{
				glm::mat4 model = m_transform.lock()->getModel();
				if (m_cullByPart)
				{
					m_lighting->draw(m_objMtlModel->m_internal, m_animationController, model);
				}
				else
				{
					m_lighting->draw(m_objMtlModel->m_internal, m_animationController, model);
				}
			}
		}
	}

	void Renderer::onDisplay()
	{
		if (m_shader)
		{
			if ((m_mesh && m_texture) || m_objMtlModel)
			{
				std::shared_ptr<Camera> currentCam;
				glm::mat4 model = m_transform.lock()->getModel();
				m_shader->m_internal->setUniform("in_Model", model);
				m_shader->m_internal->setUniform("in_Texture", m_texture->m_internal);
				//m_shader->m_internal->setUniform("in_Animate", glm::mat4(1));
				
				if (m_animationController)
				{
					m_animationController->setToDraw();
				}

				if (m_camera)
				{
					currentCam = m_camera;
					m_shader->setCam(currentCam);
				}
				else
				{
					currentCam = getCore()->getCurrentCamera();
					m_shader->setCam(currentCam);
				}

				if (m_objMtlModel)
				{
					if (m_cullByPart)
					{
						m_camera->cullAndDraw(m_shader->m_internal, m_transform.lock(),
							m_objMtlModel->m_internalModel, "in_Texture");
					}
					else
					{
						m_camera->draw(m_shader->m_internal, m_transform.lock(),
							m_objMtlModel->m_internalModel, "in_Texture");
					}
				}
				else
				{
					if (m_cullByPart)
					{
						currentCam->cullAndDraw(m_shader->m_internal,
							m_transform.lock(), m_mesh->m_internal);
					}
					else
					{
						currentCam->draw(m_shader->m_internal,
							m_transform.lock(), m_mesh->m_internal);
					}
				}
			}
		}
	}
}