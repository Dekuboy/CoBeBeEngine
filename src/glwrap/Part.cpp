#include <glwrap/Part.h>
#include <glwrap/VertexBuffer.h>
#include <glwrap/VertexArray.h>
#include <glwrap/Frame.h>
#include <glwrap/Animation.h>
#include <glwrap/Material.h>
#include <glwrap/Context.h>
#include <glwrap/ShaderProgram.h>
#include <glm/ext.hpp>

namespace glwrap
{
	float Face::getMaxX()
	{
		float maxX = pa.x;

		if (pb.x > maxX)
		{
			maxX = pb.x;
		}

		if (pc.x > maxX)
		{
			maxX = pc.x;
		}

		return maxX;
	}

	float Face::getMinX()
	{
		float minX = pa.x;

		if (pb.x < minX)
		{
			minX = pb.x;
		}

		if (pc.x < minX)
		{
			minX = pc.x;
		}

		return minX;
	}

	float Face::getMaxY()
	{
		float maxY = pa.y;

		if (pb.y > maxY)
		{
			maxY = pb.y;
		}

		if (pc.y > maxY)
		{
			maxY = pc.y;
		}

		return maxY;
	}

	float Face::getMinY()
	{
		float minY = pa.y;

		if (pb.y < minY)
		{
			minY = pb.y;
		}

		if (pc.y < minY)
		{
			minY = pc.y;
		}

		return minY;
	}

	float Face::getMaxZ()
	{
		float maxZ = pa.z;

		if (pb.z > maxZ)
		{
			maxZ = pb.z;
		}

		if (pc.z > maxZ)
		{
			maxZ = pc.z;
		}

		return maxZ;
	}

	float Face::getMinZ()
	{
		float minZ = pa.z;

		if (pb.z < minZ)
		{
			minZ = pb.z;
		}

		if (pc.z < minZ)
		{
			minZ = pc.z;
		}

		return minZ;
	}

	// ---------------------------------------------------------------------------------

	Part::Part(std::shared_ptr<VertexArray> _mesh, std::string _name)
	{
		m_name = _name;
		m_model = _mesh;
		m_animationUniform = glm::mat4(1);
		m_useMaterial = false;

		generateArrays();
	}

	Part::~Part()
	{

	}

	std::string Part::getName()
	{
		return m_name;
	}

	std::vector<std::shared_ptr<Face> > Part::getFaces()
	{
		return m_faces;
	}

	void Part::addFace(std::shared_ptr<Face> _face)
	{
		m_faces.push_back(_face);

		if (m_faces.size() == 1)
		{
			m_maxX = std::numeric_limits<float>::min();
			m_maxY = std::numeric_limits<float>::min();
			m_maxZ = std::numeric_limits<float>::min();

			m_minX = std::numeric_limits<float>::max();
			m_minY = std::numeric_limits<float>::max();
			m_minZ = std::numeric_limits<float>::max();
		}

		if (m_faces.at(m_faces.size() - 1)->getMaxX() > m_maxX)
		{
			m_maxX = _face->getMaxX();
		}

		if (m_faces.at(m_faces.size() - 1)->getMaxY() > m_maxY)
		{
			m_maxY = _face->getMaxY();
		}

		if (m_faces.at(m_faces.size() - 1)->getMaxZ() > m_maxZ)
		{
			m_maxZ = _face->getMaxZ();
		}

		if (m_faces.at(m_faces.size() - 1)->getMinX() < m_minX)
		{
			m_minX = _face->getMinX();
		}

		if (m_faces.at(m_faces.size() - 1)->getMinY() < m_minY)
		{
			m_minY = _face->getMinY();
		}

		if (m_faces.at(m_faces.size() - 1)->getMinZ() < m_minZ)
		{
			m_minZ = _face->getMinZ();
		}

		m_offsetX = (m_minX + m_maxX) / 2;
		m_offsetY = (m_minY + m_maxY) / 2;
		m_offsetZ = (m_minZ + m_maxZ) / 2;

		m_dirty = true;
	}

	void Part::setBuffer(std::string _attribute, std::shared_ptr<VertexBuffer> _buffer, int _materialId)
	{
		if (_attribute == "in_Position")
		{
			m_buffers.at(_materialId).at(0) = _buffer;
		}
		else if (_attribute == "in_Color")
		{
			m_buffers.at(_materialId).at(1) = _buffer;
		}
		else if (_attribute == "in_TexCoord")
		{
			m_buffers.at(_materialId).at(2) = _buffer;
		}
		else if (_attribute == "in_Normal")
		{
			m_buffers.at(_materialId).at(3) = _buffer;
		}
		else if (_attribute == "in_Tangent")
		{
			m_buffers.at(_materialId).at(4) = _buffer;
		}
		else if (_attribute == "in_Bitangent")
		{
			m_buffers.at(_materialId).at(5) = _buffer;
		}
		else
		{
			throw std::exception();
		}

		m_dirty = true;
	}

	int Part::getVertexCount(int _materialId)
	{
		if (m_buffers.size() < 1)
		{
			throw std::exception();
		}

		return m_buffers.at(_materialId).at(0)->getDataSize() / m_buffers.at(_materialId).at(0)->getComponents();
	}

	GLuint Part::getId(int _materialId)
	{
		if (m_dirty)
		{
			for (int matId = 0; matId < m_idList.size(); matId++)
			{
				for (int i = 0; i < m_buffers.at(matId).size(); i++)
				{
					glBindVertexArray(m_idList.at(matId));
					if (m_buffers.at(matId).at(i))
					{
						glBindBuffer(GL_ARRAY_BUFFER, m_buffers.at(matId).at(i)->getId());

						glVertexAttribPointer(i, m_buffers.at(matId).at(i)->getComponents(), GL_FLOAT, GL_FALSE,
							m_buffers.at(matId).at(i)->getComponents() * sizeof(GLfloat), (void*)0);

						glEnableVertexAttribArray(i);
					}
					else
					{
						glDisableVertexAttribArray(i);
					}
				}
			}

			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindVertexArray(0);
			m_dirty = false;
		}

		return m_idList.at(_materialId);
	}

	void Part::draw()
	{
		glm::vec3 translateVector(m_offsetX, m_offsetY, m_offsetZ);

		m_animationUniform = glm::translate(m_animationUniform, translateVector);
		translate(1);
		m_animationUniform = glm::translate(m_animationUniform, -translateVector);

		std::shared_ptr<ShaderProgram> shader = m_context.lock()->
			getCurrentShader();

		bool check = false;

		if (m_animationUniform != glm::mat4(1))
		{
			shader->setUniform("in_Animate", m_animationUniform);
			check = true;
		}

		if (m_useMaterial)
		{
			int listItr = 0;
			for (std::list<std::shared_ptr<Material> >::iterator itr = m_materials.begin();
				itr != m_materials.end(); itr++)
			{
				glBindVertexArray(getId(listItr));
				glDrawArrays(GL_TRIANGLES, 0, getVertexCount(listItr));
				listItr++;
			}
		}
		else
		{
			glBindVertexArray(getId(0));
			glDrawArrays(GL_TRIANGLES, 0, getVertexCount(0));
		}

		if (check)
		{
			m_animationUniform = glm::mat4(1);
			shader->setUniform("in_Animate", m_animationUniform);
		}
	}

	void Part::draw(std::string _textureUniform)
	{

		glm::vec3 translateVector(m_offsetX, m_offsetY, m_offsetZ);

		m_animationUniform = glm::translate(m_animationUniform, translateVector);
		translate(1);
		m_animationUniform = glm::translate(m_animationUniform, -translateVector);

		std::shared_ptr<ShaderProgram> shader = m_context.lock()->
			getCurrentShader();

		bool check = false;

		if (m_animationUniform != glm::mat4(1))
		{
			shader->setUniform("in_Animate", m_animationUniform);
			check = true;
		}

		int listItr = 0;
		for (std::list<std::shared_ptr<Material> >::iterator itr = m_materials.begin();
			itr != m_materials.end(); itr++)
		{
			m_context.lock()->getCurrentShader()->setUniform(_textureUniform, (*itr)->m_textureMap.lock());

			glBindVertexArray(getId(listItr));
			glDrawArrays(GL_TRIANGLES, 0, getVertexCount(listItr));
			listItr++;
		}

		if (check)
		{
			m_animationUniform = glm::mat4(1);
			shader->setUniform("in_Animate", m_animationUniform);
		}
	}

	glm::vec3 Part::getSize()
	{
		return glm::vec3(m_maxX - m_minX, m_maxY - m_minY, m_maxZ - m_minZ);
	}

	void Part::translate(int _undo)
	{
		std::vector<std::shared_ptr<Animation> > animations =
			m_model.lock()->getAnimations();
		std::shared_ptr<Frame> frame;
		std::shared_ptr<Translation> translation;

		glm::vec3 translateVector(0);

		for (std::vector<std::shared_ptr<Animation> >::iterator itr = animations.begin();
			itr != animations.end(); itr++)
		{
			if ((*itr)->getEnabled())
			{
				frame = (*itr)->getMergeFrame();
				translation = frame->getTranslation(m_self.lock());

				if (translation != nullptr)
				{
					if (_undo == -1)
					{
						m_animationUniform = glm::rotate(m_animationUniform, _undo *
							translation->getXRotation(), glm::vec3(1, 0, 0));
						m_animationUniform = glm::rotate(m_animationUniform, _undo *
							translation->getYRotation(), glm::vec3(0, 1, 0));
						m_animationUniform = glm::rotate(m_animationUniform, _undo *
							translation->getZRotation(), glm::vec3(0, 0, 1));
					}

					translateVector = ((float)_undo) * glm::vec3(translation->getX(), translation->getY(),
						translation->getZ());
					m_animationUniform = glm::translate(m_animationUniform, translateVector);

					if (_undo == 1)
					{
						m_animationUniform = glm::rotate(m_animationUniform, _undo *
							translation->getZRotation(), glm::vec3(0, 0, 1));
						m_animationUniform = glm::rotate(m_animationUniform, _undo *
							translation->getYRotation(), glm::vec3(0, 1, 0));
						m_animationUniform = glm::rotate(m_animationUniform, _undo *
							translation->getXRotation(), glm::vec3(1, 0, 0));
					}
				}
			}
		}
	}

	void Part::generateArrays()
	{
		m_buffers.resize(m_buffers.size() + 1);
		m_idList.resize(m_idList.size() + 1);

		glGenVertexArrays(1, &m_idList.back());

		if (!m_idList.back())
		{
			throw std::exception();
		}

		m_buffers.back().resize(10);
	}
}