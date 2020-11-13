#include <cobebe/Core/Camera.h>
#include <cobebe/Resources/RendAssets.h>
#include <cobebe/Renderer/Lighting.h>
#include <glm/ext.hpp>

namespace cobebe
{
	Camera::Camera()
	{
		m_position = glm::vec3(0.0f);
		m_rotation = glm::mat3(1.0f);
		m_isOn = false;
	}

	glm::mat4 Camera::getView()
	{
		glm::mat4 camModel(1.0f);
		camModel = glm::translate(camModel, m_position);
		camModel = camModel * glm::mat4(m_rotation);
		return camModel;
	}

	glm::mat4 Camera::getProjection()
	{
		return m_projection;
	}


	void Camera::setPerspective(float _angle, float _width, float _height, float _near, float _far)
	{
		m_projection = glm::perspective(glm::radians(_angle), _width / _height, _near, _far);
		m_near = _near;
		m_far = _far;
	}

	float Camera::getNearPlane()
	{
		return m_near;
	}

	float Camera::getFarPlane()
	{
		return m_far;
	}

	void Camera::draw(std::shared_ptr<glwrap::ShaderProgram> _shaderInternal, std::shared_ptr<glwrap::VertexArray> _meshInternal)
	{
		if (m_isOn)
		{
			//_shaderInternal->draw(m_texture, _meshInternal);
			_shaderInternal->draw(m_gBuffer, _meshInternal);
		}
	}

	void Camera::draw(std::shared_ptr<glwrap::ShaderProgram> _shaderInternal)
	{
		if (m_isOn)
		{
			//_shaderInternal->draw(m_texture);
			_shaderInternal->draw(m_gBuffer);
		}
	}

	void Camera::draw(std::shared_ptr<glwrap::ShaderProgram> _shaderInternal, std::shared_ptr<glwrap::Model> _meshInternal, std::string _textureUniform)
	{
		if (m_isOn)
		{
			//_shaderInternal->draw(m_texture);
			_shaderInternal->draw(m_gBuffer, _meshInternal, _textureUniform);
		}
	}

	void Camera::drawLighting(std::shared_ptr<Shader> _shader)
	{
		if (m_isOn)
		{
			std::shared_ptr<glwrap::ShaderProgram> temp = _shader->getInternal();

			_shader->setLightCol(m_lighting->getGlobalLightCol());
			m_lighting->setDepthBuffer(_shader);
			_shader->setAmbient(m_lighting->getGlobalLightAmbient());
			_shader->setLightDir(m_lighting->getGlobalLightDir());
			_shader->setLightSpace(m_lighting->getGlobalLightSpace());

			m_lighting->setPointLightRCount(_shader);
			if (m_lighting->getPointLights().size() > 0)
			{
				m_lighting->setDepthCubes(_shader);
				m_lighting->setPointPositions(_shader);
				m_lighting->setPointColours(_shader);
				m_lighting->setFarPlanes(_shader);
			}

			temp->setUniform(m_gBuffer);

			temp->setUniform("in_ViewPos", m_position);
			temp->draw(m_texture);
		}
	}

	void Camera::setRtUniform(std::string _uniform, std::shared_ptr<glwrap::ShaderProgram> _shaderInternal)
	{
		std::shared_ptr<glwrap::Texture> texture = m_texture;
		_shaderInternal->setUniform(_uniform, texture);
	}

	void Camera::setGbUniform(std::shared_ptr<glwrap::ShaderProgram> _shaderInternal)
	{
		_shaderInternal->setUniform(m_gBuffer);
	}
}