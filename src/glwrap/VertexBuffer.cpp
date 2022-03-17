#include <glwrap/VertexBuffer.h>

namespace glwrap
{
	VertexBuffer::VertexBuffer()
	{
		m_components = 0;
		m_dirty = false;
		m_isFloat = true;

		glGenBuffers(1, &m_id);

		if (!m_id)
		{
			throw std::exception();
		}
	}

	VertexBuffer::~VertexBuffer()
	{
		glDeleteBuffers(1, &m_id);
	}

	void VertexBuffer::add(glm::vec2 _value)
	{
		if (m_components != 2 && m_components != 0)
		{
			throw std::exception();
		}

		m_floatData.push_back(_value.x);
		m_floatData.push_back(_value.y);
		m_components = 2;
		m_dirty = true;
	}

	void VertexBuffer::add(glm::vec3 _value)
	{
		if (m_components != 3 && m_components != 0)
		{
			throw std::exception();
		}

		m_floatData.push_back(_value.x);
		m_floatData.push_back(_value.y);
		m_floatData.push_back(_value.z);
		m_components = 3;
		m_dirty = true;
	}

	void VertexBuffer::add(glm::vec4 _value)
	{
		if (m_components != 4 && m_components != 0)
		{
			throw std::exception();
		}

		m_floatData.push_back(_value.x);
		m_floatData.push_back(_value.y);
		m_floatData.push_back(_value.z);
		m_floatData.push_back(_value.w);
		m_components = 4;
		m_dirty = true;
	}

	void VertexBuffer::add(glm::ivec2 _value)
	{
		if (m_components != 4 && m_components != 0)
		{
			throw std::exception();
		}

		m_intData.push_back(_value.x);
		m_intData.push_back(_value.y);
		m_components = 4;
		m_isFloat = false;
		m_dirty = true;
	}

	void VertexBuffer::add(glm::ivec3 _value)
	{
		if (m_components != 4 && m_components != 0)
		{
			throw std::exception();
		}

		m_intData.push_back(_value.x);
		m_intData.push_back(_value.y);
		m_intData.push_back(_value.z);
		m_components = 4;
		m_isFloat = false;
		m_dirty = true;
	}

	void VertexBuffer::add(glm::ivec4 _value)
	{
		if (m_components != 4 && m_components != 0)
		{
			throw std::exception();
		}

		m_intData.push_back(_value.x);
		m_intData.push_back(_value.y);
		m_intData.push_back(_value.z);
		m_intData.push_back(_value.w);
		m_components = 4;
		m_isFloat = false;
		m_dirty = true;
	}

	int VertexBuffer::getComponents()
	{
		return m_components;
	}

	int VertexBuffer::getDataSize()
	{
		if (m_isFloat) { return m_floatData.size(); }
		return m_intData.size();
	}

	GLuint VertexBuffer::getId()
	{
		if (m_dirty)
		{
			glBindBuffer(GL_ARRAY_BUFFER, m_id);
			if (m_isFloat)
			{
				glBufferData(GL_ARRAY_BUFFER, m_floatData.size() * sizeof(float), &m_floatData.at(0), GL_STATIC_DRAW);
			}
			else
			{
				glBufferData(GL_ARRAY_BUFFER, m_intData.size() * sizeof(int), &m_intData.at(0), GL_STATIC_DRAW);
			}
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			m_dirty = false;
		}

		return m_id;
	}
}
