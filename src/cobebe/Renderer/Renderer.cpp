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

	void Renderer::setWavefrontModel(std::shared_ptr<WavefrontModel> _mesh)
	{
		m_mesh = _mesh;
		m_modelType = cobebeModel::objMtl;
	}

	void Renderer::setWavefrontModel(std::string _path)
	{
		m_mesh = getCore()->loadAsset<WavefrontModel>(_path);
		m_modelType = cobebeModel::objMtl;
	}

	void Renderer::setGltfMesh(std::shared_ptr<SkinModel> _mesh)
	{
		m_mesh = _mesh;
		m_modelType = cobebeModel::skin;
	}

	void Renderer::setGltfMesh(std::string _path)
	{
		m_mesh = getCore()->loadAsset<SkinModel>(_path);
		m_modelType = cobebeModel::skin;
	}

	void Renderer::setMesh(std::shared_ptr<Mesh> _mesh)
	{
		m_mesh = _mesh;
		m_modelType = cobebeModel::singleTexObj;
	}

	void Renderer::setMesh(std::string _path)
	{
		m_mesh = getCore()->loadAsset<SimpleModel>(_path);
		m_modelType = cobebeModel::singleTexObj;
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
		m_shader->m_internal->setTextureUniformsType<glwrap::SingleUniform>();
	}

	void Renderer::setCullByPart(bool _switch)
	{
		m_cullByPart = _switch;
	}

	std::shared_ptr<Mesh> Renderer::getMesh()
	{
		return m_mesh;
	}

	std::shared_ptr<ObjAnimationController> Renderer::addAnimationController()
	{
		if (m_mesh)
		{
			if (m_mesh->m_internal && m_modelType < 2 && m_modelType > -1)
			{
				std::shared_ptr<glwrap::VertexArray> va = std::dynamic_pointer_cast<glwrap::VertexArray>(m_mesh->m_internal);
				if (va)
				{
					m_animationController = getEntity()->addComponent<ObjAnimationController>(va);
					return m_animationController;
				}
			}
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
			if (!m_mesh)
			{
				return;
			}
			else
			{
				if (!m_mesh->m_internal)
				{
					return;
				}
			}
			if (m_modelType == 0)
			{
				if (!m_texture)
				{
					return;
				}
			}
			if (!m_shader->getUniformCheck())
			{
				m_shader->setUniformCheck(true);
			}
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
	}

	void Renderer::onDisplay()
	{
		if (m_shader)
		{
			if (!m_mesh)
			{
				return;
			}
			else
			{
				if (!m_mesh->m_internal)
				{
					return;
				}
			}
			if (m_modelType == 0)
			{
				if (!m_texture)
				{
					return;
				}
				m_shader->m_internal->setUniform("in_Texture", m_texture->m_internal);
			}
			else if (m_modelType == 2)
			{
				std::shared_ptr<glwrap::GltfModel> skinModel =
					std::dynamic_pointer_cast<glwrap::GltfModel>(m_mesh->m_internal);
				if (skinModel)
				{
					skinModel->updateAnimationValues(m_shader->m_internal);
				}
			}
			std::shared_ptr<Camera> currentCam;
			glm::mat4 model = m_transform.lock()->getModel();
			m_shader->m_internal->setUniform("in_Model", model);
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