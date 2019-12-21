#include "ShaderProgram.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "Texture.h"
#include "RenderTexture.h"
#include "DepthBuffer.h"
#include "FileManager.h"

#include <glm/ext.hpp>

namespace glwrap
{
	void printShaderInfoLog(GLuint obj)
	{
		int infologLength = 0;
		int charsWritten = 0;
		char *infoLog;

		glGetShaderiv(obj, GL_INFO_LOG_LENGTH, &infologLength);

		if (infologLength > 0)
		{
			infoLog = (char *)malloc(infologLength);
			glGetShaderInfoLog(obj, infologLength, &charsWritten, infoLog);
			printf("%s\n", infoLog);
			free(infoLog);
		}
	}

	void printProgramInfoLog(GLuint obj)
	{
		int infologLength = 0;
		int charsWritten = 0;
		char *infoLog;

		glGetProgramiv(obj, GL_INFO_LOG_LENGTH, &infologLength);

		if (infologLength > 0)
		{
			infoLog = (char *)malloc(infologLength);
			glGetProgramInfoLog(obj, infologLength, &charsWritten, infoLog);
			printf("%s\n", infoLog);
			free(infoLog);
		}
	}

	ShaderProgram::ShaderProgram()
	{
		std::string vertShader;
		std::string fragShader;

		std::string src = FileManager::loadWin("\\shaders\\phong.shad");

		vertShader = "#version 120\n#define VERTEX\n" + src;

		fragShader = "#version 120\n#define FRAGMENT\n" + src;

		const char *vertex = vertShader.c_str();
		const char *fragment = fragShader.c_str();

		GLuint vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShaderId, 1, &vertex, NULL);
		glCompileShader(vertexShaderId);
		GLint success = 0;
		glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			throw std::exception();
		}

		GLuint fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShaderId, 1, &fragment, NULL);
		glCompileShader(fragmentShaderId);
		success = 0;
		glGetShaderiv(fragmentShaderId, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			throw std::exception();
		}

		m_id = glCreateProgram();
		glAttachShader(m_id, vertexShaderId);
		glAttachShader(m_id, fragmentShaderId);

		// Ensure the VAO "Position" attribute stream gets set as the first position
		// during the link.
		glBindAttribLocation(m_id, 0, "in_Position");
		glBindAttribLocation(m_id, 1, "in_Color");
		glBindAttribLocation(m_id, 2, "in_TexCoord");
		glBindAttribLocation(m_id, 3, "in_Normal");


		// Perform the link and check for failure
		glLinkProgram(m_id);
		glGetProgramiv(m_id, GL_LINK_STATUS, &success);

		if (!success)
		{
			throw std::exception();
		}

		glDetachShader(m_id, vertexShaderId);
		glDeleteShader(vertexShaderId);
		glDetachShader(m_id, fragmentShaderId);
		glDeleteShader(fragmentShaderId);
	}

	ShaderProgram::ShaderProgram(std::string _path)
	{
		std::string vertShader;
		std::string fragShader;

		std::string src = FileManager::loadWin(_path);

		vertShader = "#version 120\n#define VERTEX\n" + src;

		fragShader = "#version 120\n#define FRAGMENT\n" + src;

		const char *vertex = vertShader.c_str();
		const char *fragment = fragShader.c_str();

		GLuint vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShaderId, 1, &vertex, NULL);
		glCompileShader(vertexShaderId);
		GLint success = 0;
		glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			printShaderInfoLog(vertexShaderId);
			printProgramInfoLog(vertexShaderId);
			throw std::exception();
		}

		GLuint fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShaderId, 1, &fragment, NULL);
		glCompileShader(fragmentShaderId);
		success = 0;
		glGetShaderiv(fragmentShaderId, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			printShaderInfoLog(fragmentShaderId);
			printProgramInfoLog(fragmentShaderId);
			throw std::exception();
		}

		m_id = glCreateProgram();
		glAttachShader(m_id, vertexShaderId);
		glAttachShader(m_id, fragmentShaderId);

		// Ensure the VAO "Position" attribute stream gets set as the first position
		// during the link.
		glBindAttribLocation(m_id, 0, "in_Position");
		glBindAttribLocation(m_id, 1, "in_Color");
		glBindAttribLocation(m_id, 2, "in_TexCoord");
		glBindAttribLocation(m_id, 3, "in_Normal");

		// Perform the link and check for failure
		glLinkProgram(m_id);
		glGetProgramiv(m_id, GL_LINK_STATUS, &success);

		if (!success)
		{
			throw std::exception();
		}

		glDetachShader(m_id, vertexShaderId);
		glDeleteShader(vertexShaderId);
		glDetachShader(m_id, fragmentShaderId);
		glDeleteShader(fragmentShaderId);

		std::shared_ptr<VertexBuffer> positions = std::make_shared<VertexBuffer>();
		positions->add(glm::vec2(-1.0f, 1.0f));
		positions->add(glm::vec2(-1.0f, -1.0f));
		positions->add(glm::vec2(1.0f, -1.0f));
		positions->add(glm::vec2(1.0f, -1.0f));
		positions->add(glm::vec2(1.0f, 1.0f));
		positions->add(glm::vec2(-1.0f, 1.0f));

		std::shared_ptr<VertexBuffer> texCoords = std::make_shared<VertexBuffer>();
		texCoords->add(glm::vec2(0.0f, 0.0f));
		texCoords->add(glm::vec2(0.0f, -1.0f));
		texCoords->add(glm::vec2(1.0f, -1.0f));
		texCoords->add(glm::vec2(1.0f, -1.0f));
		texCoords->add(glm::vec2(1.0f, 0.0f));
		texCoords->add(glm::vec2(0.0f, 0.0f));

		m_simpleShape = std::make_shared<VertexArray>();
		m_simpleShape->setBuffer("in_Position", positions);
		m_simpleShape->setBuffer("in_TexCoord", texCoords);
	}

	void ShaderProgram::draw()
	{
		draw(m_simpleShape);
	}

	void ShaderProgram::draw(std::shared_ptr<RenderTexture> renderTexture)
	{
		draw(renderTexture, m_simpleShape);
	}

	void ShaderProgram::draw(std::shared_ptr<VertexArray> vertexArray)
	{
		//  glUseProgram(id);
		//  glBindVertexArray(vertexArray->getId());
		//  
		//  glDrawArrays(GL_TRIANGLES, 0, 3);
		//  
		//  glBindVertexArray(0);
		//  glUseProgram(0);
		glViewport(m_viewport.x, m_viewport.y, m_viewport.z, m_viewport.w);
		glUseProgram(m_id);
		glBindVertexArray(vertexArray->getId());

		for (size_t i = 0; i < m_samplers.size(); i++)
		{
			glActiveTexture(GL_TEXTURE0 + i);

			if (m_samplers.at(i).m_texture)
			{
				glBindTexture(GL_TEXTURE_2D, m_samplers.at(i).m_texture->getId());
			}
			else
			{
				glBindTexture(GL_TEXTURE_2D, 0);
			}
		}

		glDrawArrays(GL_TRIANGLES, 0, vertexArray->getVertexCount());

		for (size_t i = 0; i < m_samplers.size(); i++)
		{
			glActiveTexture(GL_TEXTURE0 + i);
			glBindTexture(GL_TEXTURE_2D, 0);
		}

		glBindVertexArray(0);
		glUseProgram(0);
	}

	void ShaderProgram::draw(std::shared_ptr<RenderTexture> renderTexture, std::shared_ptr<VertexArray> vertexArray)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, renderTexture->getFbId());
		glm::vec4 lastViewport = m_viewport;
		m_viewport = glm::vec4(0, 0, renderTexture->getSize().x, renderTexture->getSize().y);
		draw(vertexArray);
		m_viewport = lastViewport;
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void ShaderProgram::setUniform(std::string uniform, glm::vec4 value)
	{
		GLint uniformId = glGetUniformLocation(m_id, uniform.c_str());

		if (uniformId == -1)
		{
			throw std::exception();
		}

		glUseProgram(m_id);
		glUniform4f(uniformId, value.x, value.y, value.z, value.w);
		glUseProgram(0);
	}

	void ShaderProgram::setUniform(std::string uniform, glm::vec3 value)
	{
		GLint uniformId = glGetUniformLocation(m_id, uniform.c_str());

		if (uniformId == -1)
		{
			throw std::exception();
		}

		glUseProgram(m_id);
		glUniform3f(uniformId, value.x, value.y, value.z);
		glUseProgram(0);
	}

	void ShaderProgram::setUniform(std::string uniform, float value)
	{
		GLint uniformId = glGetUniformLocation(m_id, uniform.c_str());

		if (uniformId == -1)
		{
			throw std::exception();
		}

		glUseProgram(m_id);
		glUniform1f(uniformId, value);
		glUseProgram(0);
	}

	void ShaderProgram::setUniform(std::string uniform, std::shared_ptr<Texture> texture)
	{
		GLint uniformId = glGetUniformLocation(m_id, uniform.c_str());

		if (uniformId == -1)
		{
			throw std::exception();
		}

		for (int i = 0; i < m_samplers.size(); i++)
		{
			if (m_samplers.at(i).m_id == uniformId)
			{
				m_samplers.at(i).m_texture = texture;

				glUseProgram(m_id);
				glUniform1i(uniformId, i);
				glUseProgram(0);
				return;
			}
		}

		Sampler s;
		s.m_id = uniformId;
		s.m_texture = texture;
		m_samplers.push_back(s);

		glUseProgram(m_id);
		glUniform1i(uniformId, m_samplers.size() - 1);
		glUseProgram(0);
	}

	void ShaderProgram::setUniform(std::string uniform, glm::mat4 value)
	{
		GLint uniformId = glGetUniformLocation(m_id, uniform.c_str());

		if (uniformId == -1)
		{
			throw std::exception();
		}

		glUseProgram(m_id);
		glUniformMatrix4fv(uniformId, 1, 0, glm::value_ptr(value));
		glUseProgram(0);
	}

	void ShaderProgram::setUniform(std::string uniform, std::shared_ptr<DepthBuffer> depth)
	{
		GLint uniformId = glGetUniformLocation(m_id, uniform.c_str());

		if (uniformId == -1)
		{
			throw std::exception();
		}

		for (int i = 0; i < m_samplers.size(); i++)
		{
			if (m_samplers.at(i).m_id == uniformId)
			{
				m_samplers.at(i).m_texture = depth;

				glUseProgram(m_id);
				glUniform1i(uniformId, i);
				glUseProgram(0);
				return;
			}
		}

		Sampler s;
		s.m_id = uniformId;
		s.m_texture = depth;
		m_samplers.push_back(s);

		glUseProgram(m_id);
		glUniform1i(uniformId, m_samplers.size() - 1);
		glUseProgram(0);
	}

	GLuint ShaderProgram::getId()
	{
		return m_id;
	}

	void ShaderProgram::setViewport(glm::vec4 viewport)
	{
		this->m_viewport = viewport;
	}
}