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
		
	}

	ShaderProgram::ShaderProgram(std::string _path)
	{
		std::string vertShader;
		std::string fragShader;
		std::string geomShader;

		std::string src = FileManager::loadWin(_path);

		bool geometry = (src.compare(0, 8, "#version") == 0);
		if (geometry)
		{
#if defined(__EMSCRIPTEN__)
			vertShader = "#define VERTEX\n" + src.substr(12, std::string::npos);

			fragShader = "#define FRAGMENT\n" + src.substr(12, std::string::npos);

			geomShader = "#define GEOMETRY\n" + src.substr(12, std::string::npos);
#else
			vertShader = /*src.substr(0, 12) + */"\n#define VERTEX\n" + src.substr(12, std::string::npos);

			fragShader = src.substr(0, 12) + "\n#define FRAGMENT\n" + src.substr(12, std::string::npos);

			geomShader = src.substr(0, 12) + "\n#define GEOMETRY\n" + src.substr(12, std::string::npos);
#endif
		}
		else
		{
#if defined (__EMSCRIPTEN__)
			vertShader = "#define VERTEX\n" + src;

			fragShader = "#define FRAGMENT\n" + src;
#else
			vertShader = "#version 140\n#define VERTEX\n" + src;

			fragShader = "#version 140\n#define FRAGMENT\n" + src;
#endif
		}

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

		GLuint geometryShaderId;
		if (geometry)
		{
			const char *geom = geomShader.c_str();
			geometryShaderId = glCreateShader(GL_GEOMETRY_SHADER);
			glShaderSource(geometryShaderId, 1, &geom, NULL);
			glCompileShader(geometryShaderId);
			success = 0;
			glGetShaderiv(geometryShaderId, GL_COMPILE_STATUS, &success);
			if (!success)
			{
				throw std::exception();
			}
		}

		m_id = glCreateProgram();
		glAttachShader(m_id, vertexShaderId);
		glAttachShader(m_id, fragmentShaderId);
		if (geometry)
		{
			glAttachShader(m_id, geometryShaderId);
		}

		// Ensure the VAO "Position" attribute stream gets set as the first position
		// during the link.
		glBindAttribLocation(m_id, 0, "in_Position");
		glBindAttribLocation(m_id, 1, "in_Color");
		glBindAttribLocation(m_id, 2, "in_TexCoord");
		glBindAttribLocation(m_id, 3, "in_Normal");
		glBindAttribLocation(m_id, 4, "in_Tangent");
		glBindAttribLocation(m_id, 5, "in_Bitangent");

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
		if (geometry)
		{
			glDetachShader(m_id, geometryShaderId);
			glDeleteShader(geometryShaderId);
		}

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

		m_simpleShape = m_context.lock()->createMesh();
		m_simpleShape->setBuffer("in_Position", positions);
		m_simpleShape->setBuffer("in_TexCoord", texCoords);
	}

	void ShaderProgram::parse(std::string _path)
	{
		std::string vertShader;
		std::string fragShader;
		std::string geomShader;

		std::string src = FileManager::loadWin(_path);

		bool geometry = (src.compare(0, 8, "#version") == 0);
		if (geometry)
		{
			vertShader = /*src.substr(0, 12) + */"\n#define VERTEX\n" + src.substr(12, std::string::npos);

			fragShader = src.substr(0, 12) + "\n#define FRAGMENT\n" + src.substr(12, std::string::npos);

			geomShader = src.substr(0, 12) + "\n#define GEOMETRY\n" + src.substr(12, std::string::npos);
		}
		else
		{
			vertShader = "#define VERTEX\n" + src;

			fragShader = "#define FRAGMENT\n" + src;
		}

		const char* vertex = vertShader.c_str();
		const char* fragment = fragShader.c_str();

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

		GLuint geometryShaderId;
		if (geometry)
		{
			const char* geom = geomShader.c_str();
			geometryShaderId = glCreateShader(GL_GEOMETRY_SHADER);
			glShaderSource(geometryShaderId, 1, &geom, NULL);
			glCompileShader(geometryShaderId);
			success = 0;
			glGetShaderiv(geometryShaderId, GL_COMPILE_STATUS, &success);
			if (!success)
			{
				throw std::exception();
			}
		}

		m_id = glCreateProgram();
		glAttachShader(m_id, vertexShaderId);
		glAttachShader(m_id, fragmentShaderId);
		if (geometry)
		{
			glAttachShader(m_id, geometryShaderId);
		}

		// Ensure the VAO "Position" attribute stream gets set as the first position
		// during the link.
		glBindAttribLocation(m_id, 0, "in_Position");
		glBindAttribLocation(m_id, 1, "in_Color");
		glBindAttribLocation(m_id, 2, "in_TexCoord");
		glBindAttribLocation(m_id, 3, "in_Normal");
		glBindAttribLocation(m_id, 4, "in_Tangent");
		glBindAttribLocation(m_id, 5, "in_Bitangent");

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
		if (geometry)
		{
			glDetachShader(m_id, geometryShaderId);
			glDeleteShader(geometryShaderId);
		}

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

		m_simpleShape = m_context.lock()->createMesh();
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
		m_context.lock()->setCurrentShader(m_self.lock());

		gType check;

		for (size_t i = 0; i < m_samplers.size(); i++)
		{
			glActiveTexture(GL_TEXTURE0 + i);

			if (m_samplers.at(i).m_texture)
			{
				glBindTexture(GL_TEXTURE_2D, m_samplers.at(i).m_texture->getId());
			}
			else if (m_samplers.at(i).m_depthCube)
			{
				glBindTexture(GL_TEXTURE_CUBE_MAP, m_samplers.at(i).m_depthCube->getId());
			}
			else if (m_samplers.at(i).m_gBuffer)
			{
				check = m_samplers.at(i).m_gType;

				if (check == 0)
				{
					glBindTexture(GL_TEXTURE_2D, m_samplers.at(i).m_gBuffer->getId());
				}
				else if (check == 1)
				{
					glBindTexture(GL_TEXTURE_2D, m_samplers.at(i).m_gBuffer->getNId());
				}
				else if (check == 2)
				{
					glBindTexture(GL_TEXTURE_2D, m_samplers.at(i).m_gBuffer->getAsId());
				}
				else
				{
					glBindTexture(GL_TEXTURE_2D, 0);
				}
			}
			else
			{
				glBindTexture(GL_TEXTURE_2D, 0);
			}
		}

		_vertexArray->draw();
		//glBindVertexArray(_vertexArray->getId());
		//glDrawArrays(GL_TRIANGLES, 0, _vertexArray->getVertexCount());

		for (size_t i = 0; i < m_samplers.size(); i++)
		{
			glActiveTexture(GL_TEXTURE0 + i);

			if (m_samplers.at(i).m_texture || m_samplers.at(i).m_gBuffer)
			{
				glBindTexture(GL_TEXTURE_2D, 0);
			}
			else if (m_samplers.at(i).m_depthCube)
			{
				glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
			}
		}

		glBindVertexArray(0);
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

	void ShaderProgram::setUniform(std::string _uniform, int _value)
	{
		GLint uniformId = glGetUniformLocation(m_id, _uniform.c_str());

		if (uniformId == -1)
		{
			throw std::exception();
		}

		m_context.lock()->setCurrentShader(m_self.lock());
		glUniform1i(uniformId, _value);
	}

	void ShaderProgram::setUniform(std::string _uniform, glm::vec4 _value)
	{
		GLint uniformId = glGetUniformLocation(m_id, _uniform.c_str());

		if (uniformId == -1)
		{
			throw std::exception();
		}

		m_context.lock()->setCurrentShader(m_self.lock());
		glUniform4f(uniformId, _value.x, _value.y, _value.z, _value.w);
	}

	void ShaderProgram::setUniform(std::string _uniform, glm::vec3 _value)
	{
		GLint uniformId = glGetUniformLocation(m_id, _uniform.c_str());

		if (uniformId == -1)
		{
			throw std::exception();
		}

		m_context.lock()->setCurrentShader(m_self.lock());
		glUniform3f(uniformId, _value.x, _value.y, _value.z);
	}

	void ShaderProgram::setUniform(std::string _uniform, std::vector<glm::vec3> _vectors)
	{
		GLint uniformId = glGetUniformLocation(m_id, _uniform.c_str());

		if (uniformId == -1)
		{
			throw std::exception();
		}

		m_context.lock()->setCurrentShader(m_self.lock());
		glUniform3fv(uniformId, _vectors.size(), glm::value_ptr(_vectors.at(0)));
	}

	void ShaderProgram::setUniform(std::string _uniform, float _value)
	{
		GLint uniformId = glGetUniformLocation(m_id, _uniform.c_str());

		if (uniformId == -1)
		{
			throw std::exception();
		}

		m_context.lock()->setCurrentShader(m_self.lock());
		glUniform1f(uniformId, _value);
	}

	void ShaderProgram::setUniform(std::string _uniform, std::vector<float> _floats)
	{
		GLint uniformId = glGetUniformLocation(m_id, _uniform.c_str());

		if (uniformId == -1)
		{
			throw std::exception();
		}

		m_context.lock()->setCurrentShader(m_self.lock());
		glUniform1fv(uniformId, _floats.size(), reinterpret_cast<GLfloat *>(_floats.data()));
	}

	void ShaderProgram::setUniform(std::string _uniform, std::shared_ptr<Texture> _texture)
	{
		GLint uniformId = glGetUniformLocation(m_id, _uniform.c_str());

		if (uniformId == -1)
		{
			throw std::exception();
		}

		m_context.lock()->setCurrentShader(m_self.lock());

		for (int i = 0; i < m_samplers.size(); i++)
		{
			if (m_samplers.at(i).m_id == uniformId)
			{
				m_samplers.at(i).m_texture = _texture;
				m_samplers.at(i).m_depthCube = NULL;
				m_samplers.at(i).m_gBuffer = NULL;

				glUniform1i(uniformId, i);
				return;
			}
		}

		Sampler s;
		s.m_id = uniformId;
		s.m_texture = _texture;
		m_samplers.push_back(s);

		glUniform1i(uniformId, m_samplers.size() - 1);
	}

	void ShaderProgram::setUniform(std::string _uniform, glm::mat4 _value)
	{
		GLint uniformId = glGetUniformLocation(m_id, _uniform.c_str());

		if (uniformId == -1)
		{
			throw std::exception();
		}

		m_context.lock()->setCurrentShader(m_self.lock());
		glUniformMatrix4fv(uniformId, 1, 0, glm::value_ptr(_value));
	}

	void ShaderProgram::setUniform(std::string _uniform, std::vector<glm::mat4> _matrices)
	{
		GLint uniformId = glGetUniformLocation(m_id, _uniform.c_str());

		if (uniformId == -1)
		{
			throw std::exception();
		}

		m_context.lock()->setCurrentShader(m_self.lock());
		glUniformMatrix4fv(uniformId, _matrices.size(), 0, glm::value_ptr(_matrices.at(0)));
	}

	void ShaderProgram::setUniform(std::string _uniform, std::shared_ptr<DepthBuffer> _depth)
	{
		GLint uniformId = glGetUniformLocation(m_id, _uniform.c_str());

		if (uniformId == -1)
		{
			throw std::exception();
		}

		m_context.lock()->setCurrentShader(m_self.lock());

		for (int i = 0; i < m_samplers.size(); i++)
		{
			if (m_samplers.at(i).m_id == uniformId)
			{
				m_samplers.at(i).m_texture = _depth;
				m_samplers.at(i).m_depthCube = NULL;
				m_samplers.at(i).m_gBuffer = NULL;

				glUniform1i(uniformId, i);
				return;
			}
		}

		Sampler s;
		s.m_id = uniformId;
		s.m_texture = _depth;
		m_samplers.push_back(s);

		glUniform1i(uniformId, m_samplers.size() - 1);
	}

	void ShaderProgram::setUniform(std::string _uniform, std::shared_ptr<DepthCube> _depthCube)
	{
		GLint uniformId = glGetUniformLocation(m_id, _uniform.c_str());

		if (uniformId == -1)
		{
			throw std::exception();
		}

		m_context.lock()->setCurrentShader(m_self.lock());

		for (int i = 0; i < m_samplers.size(); i++)
		{
			if (m_samplers.at(i).m_id == uniformId)
			{
				m_samplers.at(i).m_depthCube = _depthCube;
				m_samplers.at(i).m_texture = NULL;
				m_samplers.at(i).m_gBuffer = NULL;

				glUniform1i(uniformId, i);
				return;
			}
		}

		Sampler s;
		s.m_id = uniformId;
		s.m_depthCube = _depthCube;
		m_samplers.push_back(s);

		glUniform1i(uniformId, m_samplers.size() - 1);
	}

	void ShaderProgram::setUniform(std::string _uniform, std::vector<std::shared_ptr<DepthCube> > _cubes)
	{
		GLint uniformId = glGetUniformLocation(m_id, _uniform.c_str());

		if (uniformId == -1)
		{
			throw std::exception();
		}

		bool skip = false;
		int count = 0;
		std::string temp;
		m_context.lock()->setCurrentShader(m_self.lock());

		for (std::vector<std::shared_ptr<DepthCube> >::iterator itr = _cubes.begin();
			itr != _cubes.end(); itr++)
		{
			temp = _uniform + "[" + std::to_string(count) + "]";
			GLint uniformId = glGetUniformLocation(m_id, temp.c_str());

			for (int i = 0; i < m_samplers.size(); i++)
			{
				if (m_samplers.at(i).m_id == uniformId)
				{
					m_samplers.at(i).m_depthCube = (*itr);
					m_samplers.at(i).m_texture = NULL;
					m_samplers.at(i).m_gBuffer = NULL;

					glUniform1i(uniformId, i);
					skip = true;
					break;
				}
			}
			if (!skip)
			{
				Sampler s;
				s.m_id = uniformId;
				s.m_depthCube = (*itr);
				m_samplers.push_back(s);

				glUniform1i(uniformId, m_samplers.size() - 1);
			}
			count++;
		}
	}

	void ShaderProgram::setUniform(std::shared_ptr<GBuffer> _gBuffer)
	{
		int buffer = 0;
		bool skip = false;
		GLint uniformId;
		m_context.lock()->setCurrentShader(m_self.lock());
		while (buffer < 3)
		{
			if (buffer == 0) uniformId = glGetUniformLocation(m_id, "in_GPosition");
			else if (buffer == 1) uniformId = glGetUniformLocation(m_id, "in_GNormal");
			else if (buffer == 2) uniformId = glGetUniformLocation(m_id, "in_GAlbedoSpec");

			if (uniformId == -1)
			{
				throw std::exception();
			}

			for (int i = 0; i < m_samplers.size(); i++)
			{
				if (m_samplers.at(i).m_id == uniformId)
				{
					m_samplers.at(i).m_gBuffer = _gBuffer;
					m_samplers.at(i).m_gType = (gType)buffer;
					m_samplers.at(i).m_texture = NULL;
					m_samplers.at(i).m_depthCube = NULL;

					glUniform1i(uniformId, i);
					skip = true;
					break;
				}
			}
			if (!skip)
			{
				Sampler s;
				s.m_id = uniformId;
				s.m_gBuffer = _gBuffer;
				s.m_gType = (gType)buffer;
				m_samplers.push_back(s);

				glUniform1i(uniformId, m_samplers.size() - 1);
			}
			buffer++;
		}
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