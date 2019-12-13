#include "VertexBuffer.h"

namespace glwrap
{
	VertexBuffer::VertexBuffer()
	{
		m_components = 0;
		m_dirty = false;

		glGenBuffers(1, &m_id);

		if (!m_id)
		{
			throw std::exception();
		}
	}

	void VertexBuffer::add(glm::vec2 value)
	{
		if (m_components != 2 && m_components != 0)
		{
			throw std::exception();
		}

		m_data.push_back(value.x);
		m_data.push_back(value.y);
		m_components = 2;
		m_dirty = true;
	}

	void VertexBuffer::add(glm::vec3 value)
	{
		if (m_components != 3 && m_components != 0)
		{
			throw std::exception();
		}

		m_data.push_back(value.x);
		m_data.push_back(value.y);
		m_data.push_back(value.z);
		m_components = 3;
		m_dirty = true;
	}

	void VertexBuffer::add(glm::vec4 value)
	{
		if (m_components != 4 && m_components != 0)
		{
			throw std::exception();
		}

		m_data.push_back(value.x);
		m_data.push_back(value.y);
		m_data.push_back(value.z);
		m_data.push_back(value.w);
		m_components = 4;
		m_dirty = true;
	}

	int VertexBuffer::getComponents()
	{
		return m_components;
	}

	int VertexBuffer::getDataSize()
	{
		return m_data.size();
	}

	GLuint VertexBuffer::getId()
	{
		if (m_dirty)
		{
			glBindBuffer(GL_ARRAY_BUFFER, m_id);
			glBufferData(GL_ARRAY_BUFFER, m_data.size() * sizeof(float), &m_data.at(0), GL_STATIC_DRAW);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			m_dirty = false;
		}

		return m_id;
	}
}
