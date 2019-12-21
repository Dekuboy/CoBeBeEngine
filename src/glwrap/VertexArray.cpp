#include "VertexArray.h"
#include "VertexBuffer.h"
#include "FileManager.h"

#include <fstream>
#include <iostream>

namespace glwrap
{
	void VertexArray::splitStringWhitespace(std::string& input, std::vector<std::string>& output)
	{
		std::string curr;

		output.clear();

		for (size_t i = 0; i < input.length(); i++)
		{
			if (input.at(i) == ' ' ||
				input.at(i) == '\r' ||
				input.at(i) == '\n' ||
				input.at(i) == '\t')
			{
				if (curr.length() > 0)
				{
					output.push_back(curr);
					curr = "";
				}
			}
			else
			{
				curr += input.at(i);
			}
		}

		if (curr.length() > 0)
		{
			output.push_back(curr);
		}
	}

	void VertexArray::splitString(std::string& input, char splitter, std::vector<std::string>& output)
	{
		std::string curr;

		output.clear();

		for (size_t i = 0; i < input.length(); i++)
		{
			if (input.at(i) == splitter)
			{
				output.push_back(curr);
				curr = "";
			}
			else
			{
				curr += input.at(i);
			}
		}

		if (curr.length() > 0)
		{
			output.push_back(curr);
		}
	}

	VertexArray::VertexArray(std::string path) : m_dirty(false)
	{
		glGenVertexArrays(1, &m_id);

		if (!m_id)
		{
			throw std::exception();
		}

		m_buffers.resize(10);
		std::ifstream file(FileManager::returnPath(path).c_str());

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

				if (subsplit.size() >= 1) positionBuffer->add(positions.at(atoi(subsplit.at(0).c_str()) - 1));
				if (subsplit.size() >= 2) texCoordBuffer->add(texCoords.at(atoi(subsplit.at(1).c_str()) - 1));
				if (subsplit.size() >= 3) normalBuffer->add(normals.at(atoi(subsplit.at(2).c_str()) - 1));
				if (subsplit.size() >= 4) lightMapBuffer->add(lightMaps.at(atoi(subsplit.at(3).c_str()) - 1));
				splitString(splitLine.at(2), '/', subsplit);
				if (subsplit.size() >= 1) positionBuffer->add(positions.at(atoi(subsplit.at(0).c_str()) - 1));
				if (subsplit.size() >= 2) texCoordBuffer->add(texCoords.at(atoi(subsplit.at(1).c_str()) - 1));
				if (subsplit.size() >= 3) normalBuffer->add(normals.at(atoi(subsplit.at(2).c_str()) - 1));
				if (subsplit.size() >= 4) lightMapBuffer->add(lightMaps.at(atoi(subsplit.at(3).c_str()) - 1));
				splitString(splitLine.at(3), '/', subsplit);
				if (subsplit.size() >= 1) positionBuffer->add(positions.at(atoi(subsplit.at(0).c_str()) - 1));
				if (subsplit.size() >= 2) texCoordBuffer->add(texCoords.at(atoi(subsplit.at(1).c_str()) - 1));
				if (subsplit.size() >= 3) normalBuffer->add(normals.at(atoi(subsplit.at(2).c_str()) - 1));
				if (subsplit.size() >= 4) lightMapBuffer->add(lightMaps.at(atoi(subsplit.at(3).c_str()) - 1));

				if (splitLine.size() < 5) continue;
				splitString(splitLine.at(3), '/', subsplit);

				if (subsplit.size() >= 1) positionBuffer->add(positions.at(atoi(subsplit.at(0).c_str()) - 1));
				if (subsplit.size() >= 2) texCoordBuffer->add(texCoords.at(atoi(subsplit.at(1).c_str()) - 1));
				if (subsplit.size() >= 3) normalBuffer->add(normals.at(atoi(subsplit.at(2).c_str()) - 1));
				if (subsplit.size() >= 4) lightMapBuffer->add(lightMaps.at(atoi(subsplit.at(3).c_str()) - 1));
				splitString(splitLine.at(4), '/', subsplit);
				if (subsplit.size() >= 1) positionBuffer->add(positions.at(atoi(subsplit.at(0).c_str()) - 1));
				if (subsplit.size() >= 2) texCoordBuffer->add(texCoords.at(atoi(subsplit.at(1).c_str()) - 1));
				if (subsplit.size() >= 3) normalBuffer->add(normals.at(atoi(subsplit.at(2).c_str()) - 1));
				if (subsplit.size() >= 4) lightMapBuffer->add(lightMaps.at(atoi(subsplit.at(3).c_str()) - 1));
				splitString(splitLine.at(1), '/', subsplit);
				if (subsplit.size() >= 1) positionBuffer->add(positions.at(atoi(subsplit.at(0).c_str()) - 1));
				if (subsplit.size() >= 2) texCoordBuffer->add(texCoords.at(atoi(subsplit.at(1).c_str()) - 1));
				if (subsplit.size() >= 3) normalBuffer->add(normals.at(atoi(subsplit.at(2).c_str()) - 1));
				if (subsplit.size() >= 4) lightMapBuffer->add(lightMaps.at(atoi(subsplit.at(3).c_str()) - 1));
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

	void VertexArray::setBuffer(std::string attribute, std::shared_ptr<VertexBuffer> buffer)
	{
		if (attribute == "in_Position")
		{
			m_buffers.at(0) = buffer;
		}
		else if (attribute == "in_Color")
		{
			m_buffers.at(1) = buffer;
		}
		else if (attribute == "in_TexCoord")
		{
			m_buffers.at(2) = buffer;
		}
		else if (attribute == "in_Normal")
		{
			m_buffers.at(3) = buffer;
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
}
