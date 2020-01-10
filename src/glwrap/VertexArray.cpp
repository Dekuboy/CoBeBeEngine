#include <glwrap/VertexArray.h>
#include <glwrap/VertexBuffer.h>
#include <glwrap/FileManager.h>

#include <fstream>
#include <iostream>

namespace glwrap
{
	void VertexArray::splitStringWhitespace(std::string& _input, std::vector<std::string>& _output)
	{
		std::string curr;

		_output.clear();

		for (size_t i = 0; i < _input.length(); i++)
		{
			if (_input.at(i) == ' ' ||
				_input.at(i) == '\r' ||
				_input.at(i) == '\n' ||
				_input.at(i) == '\t')
			{
				if (curr.length() > 0)
				{
					_output.push_back(curr);
					curr = "";
				}
			}
			else
			{
				curr += _input.at(i);
			}
		}

		if (curr.length() > 0)
		{
			_output.push_back(curr);
		}
	}

	void VertexArray::splitString(std::string& _input, char _splitter, std::vector<std::string>& _output)
	{
		std::string curr;

		_output.clear();

		for (size_t i = 0; i < _input.length(); i++)
		{
			if (_input.at(i) == _splitter)
			{
				_output.push_back(curr);
				curr = "";
			}
			else
			{
				curr += _input.at(i);
			}
		}

		if (curr.length() > 0)
		{
			_output.push_back(curr);
		}
	}

	VertexArray::VertexArray(std::string _path) : m_dirty(false)
	{
		glGenVertexArrays(1, &m_id);

		if (!m_id)
		{
			throw std::exception();
		}

		m_buffers.resize(10);
		std::ifstream file(FileManager::returnPath(_path).c_str());

		if (!file.is_open())
		{
			throw std::exception();
		}

		std::string line;
		std::vector<std::string> splitLine;
		std::vector<glm::vec3> positions;
		std::vector<glm::vec2> texCoords;
		std::vector<glm::vec3> normals;
		std::vector<glm::vec2> lightMaps;

		std::shared_ptr<VertexBuffer> positionBuffer;
		std::shared_ptr<VertexBuffer> texCoordBuffer;
		std::shared_ptr<VertexBuffer> normalBuffer;
		std::shared_ptr<VertexBuffer> lightMapBuffer;

		Face f;
		Face fq;

		while (!file.eof())
		{
			std::getline(file, line);
			if (line.length() < 1) continue;
			splitStringWhitespace(line, splitLine);
			if (splitLine.size() < 1) continue;

			if (splitLine.at(0) == "v")
			{
				if (!positionBuffer) positionBuffer = std::make_shared<VertexBuffer>();

				positions.push_back(glm::vec3(
					atof(splitLine.at(1).c_str()),
					atof(splitLine.at(2).c_str()),
					atof(splitLine.at(3).c_str())));
			}
			else if (splitLine.at(0) == "vt")
			{
				if (!texCoordBuffer) texCoordBuffer = std::make_shared<VertexBuffer>();

				texCoords.push_back(glm::vec2(
					atof(splitLine.at(1).c_str()),
					1.0f - atof(splitLine.at(2).c_str())));
			}
			else if (splitLine.at(0) == "vn")
			{
				if (!normalBuffer) normalBuffer = std::make_shared<VertexBuffer>();

				normals.push_back(glm::vec3(
					atof(splitLine.at(1).c_str()),
					atof(splitLine.at(2).c_str()),
					atof(splitLine.at(3).c_str())));
			}
			else if (splitLine.at(0) == "f")
			{
				std::vector<std::string> subsplit;
				splitString(splitLine.at(1), '/', subsplit);

				if (subsplit.size() >= 1)
				{
					f.pa = positions.at(atoi(subsplit.at(0).c_str()) - 1);
					positionBuffer->add(f.pa);
				}
				if (subsplit.size() >= 2)
				{
					f.tca = texCoords.at(atoi(subsplit.at(1).c_str()) - 1);
					texCoordBuffer->add(f.tca);
				}
				if (subsplit.size() >= 3)
				{
					f.na = normals.at(atoi(subsplit.at(2).c_str()) - 1);
					normalBuffer->add(f.na);
				}
				if (subsplit.size() >= 4)
				{
					f.lmca = lightMaps.at(atoi(subsplit.at(3).c_str()) - 1);
					lightMapBuffer->add(f.lmca);
				}
				splitString(splitLine.at(2), '/', subsplit);
				if (subsplit.size() >= 1) 
				{
					f.pb = positions.at(atoi(subsplit.at(0).c_str()) - 1);
					positionBuffer->add(f.pb);
				}
				if (subsplit.size() >= 2)
				{
					f.tcb = texCoords.at(atoi(subsplit.at(1).c_str()) - 1);
					texCoordBuffer->add(f.tcb);
				}
				if (subsplit.size() >= 3)
				{
					f.nb = normals.at(atoi(subsplit.at(2).c_str()) - 1);
					normalBuffer->add(f.nb);
				}
				if (subsplit.size() >= 4) 
				{
					f.lmcb = lightMaps.at(atoi(subsplit.at(3).c_str()) - 1);
					lightMapBuffer->add(f.lmcb);
				}
				splitString(splitLine.at(3), '/', subsplit);
				if (subsplit.size() >= 1)
				{
					f.pc = positions.at(atoi(subsplit.at(0).c_str()) - 1);
					positionBuffer->add(f.pc);
				}
				if (subsplit.size() >= 2)
				{
					f.tcc = texCoords.at(atoi(subsplit.at(1).c_str()) - 1);
					texCoordBuffer->add(f.tcc);
				}
				if (subsplit.size() >= 3)
				{
					f.nc = normals.at(atoi(subsplit.at(2).c_str()) - 1);
					normalBuffer->add(f.nc);
				}
				if (subsplit.size() >= 4)
				{
					f.lmcc = lightMaps.at(atoi(subsplit.at(3).c_str()) - 1);
					lightMapBuffer->add(f.lmcc);
				}

				m_faces.push_back(std::make_shared<Face>(f));
				if (splitLine.size() < 5) continue;

				fq.pa = f.pc;
				positionBuffer->add(fq.pa);
				fq.tca = f.tcc;
				texCoordBuffer->add(fq.tca);
				fq.na = f.nc;
				if (normalBuffer) normalBuffer->add(fq.na);
				fq.lmca = f.lmcc;
				if (lightMapBuffer) lightMapBuffer->add(fq.lmca);

				splitString(splitLine.at(4), '/', subsplit);
				if (subsplit.size() >= 1)
				{
					fq.pb = positions.at(atoi(subsplit.at(0).c_str()) - 1);
					positionBuffer->add(fq.pb);
				}
				if (subsplit.size() >= 2)
				{
					fq.tcb = texCoords.at(atoi(subsplit.at(1).c_str()) - 1);
					texCoordBuffer->add(fq.tcb);
				}
				if (subsplit.size() >= 3)
				{
					fq.nb = normals.at(atoi(subsplit.at(2).c_str()) - 1);
					normalBuffer->add(fq.nb);
				}
				if (subsplit.size() >= 4)
				{
					fq.lmcb = lightMaps.at(atoi(subsplit.at(3).c_str()) - 1);
					lightMapBuffer->add(fq.lmcb);
				}

				splitString(splitLine.at(1), '/', subsplit);
				fq.pc = f.pa;
				positionBuffer->add(fq.pc);
				fq.tcc = f.tca;
				texCoordBuffer->add(fq.tcc);
				fq.nc = f.na;
				if (normalBuffer) normalBuffer->add(fq.nc);
				fq.lmcc = f.lmca;
				if (lightMapBuffer) lightMapBuffer->add(fq.lmcc);

				m_faces.push_back(std::make_shared<Face>(fq));
			}
		}

		setBuffer("in_Position", positionBuffer);
		if (texCoordBuffer) setBuffer("in_TexCoord", texCoordBuffer);
		if (normalBuffer) setBuffer("in_Normal", normalBuffer);
		if (lightMapBuffer) setBuffer("in_LightMapCoord", lightMapBuffer);
	}

	VertexArray::VertexArray() : m_dirty(false)
	{
		glGenVertexArrays(1, &m_id);

		if (!m_id)
		{
			throw std::exception();
		}

		m_buffers.resize(10);
	}

	void VertexArray::setBuffer(std::string _attribute, std::shared_ptr<VertexBuffer> _buffer)
	{
		if (_attribute == "in_Position")
		{
			m_buffers.at(0) = _buffer;
		}
		else if (_attribute == "in_Color")
		{
			m_buffers.at(1) = _buffer;
		}
		else if (_attribute == "in_TexCoord")
		{
			m_buffers.at(2) = _buffer;
		}
		else if (_attribute == "in_Normal")
		{
			m_buffers.at(3) = _buffer;
		}
		else
		{
			throw std::exception();
		}

		m_dirty = true;
	}

	int VertexArray::getVertexCount()
	{
		if (!m_buffers.at(0))
		{
			throw std::exception();
		}

		return m_buffers.at(0)->getDataSize() / m_buffers.at(0)->getComponents();
	}

	GLuint VertexArray::getId()
	{
		if (m_dirty)
		{
			glBindVertexArray(m_id);

			for (size_t i = 0; i < m_buffers.size(); i++)
			{
				if (m_buffers.at(i))
				{
					glBindBuffer(GL_ARRAY_BUFFER, m_buffers.at(i)->getId());

					glVertexAttribPointer(i, m_buffers.at(i)->getComponents(), GL_FLOAT, GL_FALSE,
						m_buffers.at(i)->getComponents() * sizeof(GLfloat), (void *)0);

					glEnableVertexAttribArray(i);
				}
				else
				{
					glDisableVertexAttribArray(i);
				}
			}

			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindVertexArray(0);
			m_dirty = false;
		}

		return m_id;
	}

	std::vector<std::shared_ptr<Face>> VertexArray::getFaces()
	{
		return m_faces;
	}
}
