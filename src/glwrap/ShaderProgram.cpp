#include <glwrap/glwrap.h>

#include <glm/ext.hpp>

namespace glwrap
{
	void printShaderInfoLog(GLuint _obj)
	{
		int infologLength = 0;
		int charsWritten = 0;
		char *infoLog;

		glGetShaderiv(_obj, GL_INFO_LOG_LENGTH, &infologLength);

		if (infologLength > 0)
		{
			infoLog = (char *)malloc(infologLength);
			glGetShaderInfoLog(_obj, infologLength, &charsWritten, infoLog);
			printf("%s\n", infoLog);
			free(infoLog);
		}
	}

	void printProgramInfoLog(GLuint _obj)
	{
		int infologLength = 0;
		int charsWritten = 0;
		char *infoLog;

		glGetProgramiv(_obj, GL_INFO_LOG_LENGTH, &infologLength);

		if (infologLength > 0)
		{
			infoLog = (char *)malloc(infologLength);
			glGetProgramInfoLog(_obj, infologLength, &charsWritten, infoLog);
			printf("%s\n", infoLog);
			free(infoLog);
		}
	}

	ShaderProgram::ShaderProgram()
	{
		std::string vertShader;
		std::string fragShader;

		std::string src = FileManager::loadWin("\\shaders\\phong.shad");

		vertShader = "#version 140\n#define VERTEX\n" + src;

		fragShader = "#version 140\n#define FRAGMENT\n" + src;

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

		vertShader = "#version 140\n#define VERTEX\n" + src;

		fragShader = "#version 140\n#define FRAGMENT\n" + src;

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

	void ShaderProgram::draw(std::shared_ptr<RenderTexture> _renderTexture)
	{
		draw(_renderTexture, m_simpleShape);
	}

	void ShaderProgram::draw(std::shared_ptr<VertexArray> _vertexArray)
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
		glBindVertexArray(_vertexArray->getId());

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

		glDrawArrays(GL_TRIANGLES, 0, _vertexArray->getVertexCount());

		for (size_t i = 0; i < m_samplers.size(); i++)
		{
			glActiveTexture(GL_TEXTURE0 + i);
			glBindTexture(GL_TEXTURE_2D, 0);
		}

		glBindVertexArray(0);
		glUseProgram(0);
	}

	void ShaderProgram::draw(std::shared_ptr<RenderTexture> _renderTexture, std::shared_ptr<VertexArray> _vertexArray)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, _renderTexture->getFbId());
		glm::vec4 lastViewport = m_viewport;
		m_viewport = glm::vec4(0, 0, _renderTexture->getSize().x, _renderTexture->getSize().y);
		draw(_vertexArray);
		m_viewport = lastViewport;
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void ShaderProgram::setUniform(std::string _uniform, glm::vec4 _value)
	{
		GLint uniformId = glGetUniformLocation(m_id, _uniform.c_str());

		if (uniformId == -1)
		{
			throw std::exception();
		}

		glUseProgram(m_id);
		glUniform4f(uniformId, _value.x, _value.y, _value.z, _value.w);
		glUseProgram(0);
	}

	void ShaderProgram::setUniform(std::string _uniform, glm::vec3 _value)
	{
		GLint uniformId = glGetUniformLocation(m_id, _uniform.c_str());

		if (uniformId == -1)
		{
			throw std::exception();
		}

		glUseProgram(m_id);
		glUniform3f(uniformId, _value.x, _value.y, _value.z);
		glUseProgram(0);
	}

	void ShaderProgram::setUniform(std::string _uniform, float _value)
	{
		GLint uniformId = glGetUniformLocation(m_id, _uniform.c_str());

		if (uniformId == -1)
		{
			throw std::exception();
		}

		glUseProgram(m_id);
		glUniform1f(uniformId, _value);
		glUseProgram(0);
	}

	void ShaderProgram::setUniform(std::string _uniform, std::shared_ptr<Texture> _texture)
	{
		GLint uniformId = glGetUniformLocation(m_id, _uniform.c_str());

		if (uniformId == -1)
		{
			throw std::exception();
		}

		for (int i = 0; i < m_samplers.size(); i++)
		{
			if (m_samplers.at(i).m_id == uniformId)
			{
				m_samplers.at(i).m_texture = _texture;

				glUseProgram(m_id);
				glUniform1i(uniformId, i);
				glUseProgram(0);
				return;
			}
		}

		Sampler s;
		s.m_id = uniformId;
		s.m_texture = _texture;
		m_samplers.push_back(s);

		glUseProgram(m_id);
		glUniform1i(uniformId, m_samplers.size() - 1);
		glUseProgram(0);
	}

	void ShaderProgram::setUniform(std::string _uniform, glm::mat4 _value)
	{
		GLint uniformId = glGetUniformLocation(m_id, _uniform.c_str());

		if (uniformId == -1)
		{
			throw std::exception();
		}

		glUseProgram(m_id);
		glUniformMatrix4fv(uniformId, 1, 0, glm::value_ptr(_value));
		glUseProgram(0);
	}

	void ShaderProgram::setUniform(std::string _uniform, std::shared_ptr<DepthBuffer> _depth)
	{
		GLint uniformId = glGetUniformLocation(m_id, _uniform.c_str());

		if (uniformId == -1)
		{
			throw std::exception();
		}

		for (int i = 0; i < m_samplers.size(); i++)
		{
			if (m_samplers.at(i).m_id == uniformId)
			{
				m_samplers.at(i).m_texture = _depth;

				glUseProgram(m_id);
				glUniform1i(uniformId, i);
				glUseProgram(0);
				return;
			}
		}

		Sampler s;
		s.m_id = uniformId;
		s.m_texture = _depth;
		m_samplers.push_back(s);

		glUseProgram(m_id);
		glUniform1i(uniformId, m_samplers.size() - 1);
		glUseProgram(0);
	}

	GLuint ShaderProgram::getId()
	{
		return m_id;
	}

	void ShaderProgram::setViewport(glm::vec4 _viewport)
	{
		this->m_viewport = _viewport;
	}
}