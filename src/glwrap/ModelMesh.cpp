#include <glwrap/ModelMesh.h>
#include <glwrap/TriFace.h>
#include <glwrap/VertexBuffer.h>
#include <glwrap/GltfModel.h>
//#include <glwrap/ModelFrame.h>
//#include <glwrap/ModelAnimation.h>
#include <glwrap/Material.h>
#include <glwrap/Context.h>
#include <glwrap/ShaderProgram.h>
#include <glwrap/TextureUniforms.h>
#include <glwrap/ViewingFrustum.h>
#include <glm/ext.hpp>

namespace glwrap
{
	ModelMesh::ModelMesh(std::shared_ptr<GltfModel> _mesh, std::string _name)
	{
		m_name = _name;
		m_model = _mesh;
		m_minPoint = glm::vec3(std::numeric_limits<float>::max());
		m_maxPoint = glm::vec3(std::numeric_limits<float>::min());
		m_animationUniform = nullptr;
	}

	ModelMesh::~ModelMesh()
	{
		glDeleteVertexArrays(m_idList.size(), &m_idList.at(0));
	}

	std::string ModelMesh::getName()
	{
		return m_name;
	}

	std::vector<std::shared_ptr<TriFace> >& ModelMesh::getFaces()
	{
		return m_faces;
	}

	void ModelMesh::addFace(std::shared_ptr<TriFace> _face)
	{
		m_faces.push_back(_face);

		m_dirty = true;
	}

	void ModelMesh::setBuffer(std::string _attribute, std::shared_ptr<VertexBuffer> _buffer, int _materialId)
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
		else if (_attribute == "in_JointIDs")
		{
			m_buffers.at(_materialId).at(4) = _buffer;
		}
		else if (_attribute == "in_Weights")
		{
			m_buffers.at(_materialId).at(5) = _buffer;
		}
		else if (_attribute == "in_Tangent")
		{
			m_buffers.at(_materialId).at(6) = _buffer;
		}
		else if (_attribute == "in_Bitangent")
		{
			m_buffers.at(_materialId).at(7) = _buffer;
		}
		else
		{
			throw std::exception();
		}

		m_dirty = true;
	}

	int ModelMesh::getVertexCount(int _materialId)
	{
		if (m_buffers.size() < 1)
		{
			throw std::exception();
		}

		return m_buffers.at(_materialId).at(0)->getDataSize() / m_buffers.at(_materialId).at(0)->getComponents();
	}

	GLuint ModelMesh::getId(int _materialId)
	{
		if (m_dirty)
		{
			for (int matId = 0; matId < m_idList.size(); matId++)
			{
				glBindVertexArray(m_idList.at(matId));
				for (int i = 0; i < m_buffers.at(matId).size(); i++)
				{
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

	void ModelMesh::draw()
	{
		drawArrays();
	}

	void ModelMesh::cullAndDraw()
	{
		bool check = false;
		glm::vec3 partCentre = m_minPoint + 0.5f * m_size;
		glm::vec3 partSize = getSize();
		std::shared_ptr<ShaderProgram> shader = m_context.lock()->getCurrentShader();
		if (m_animationUniform)
		{
			glm::mat4 partMatrix = *m_animationUniform;
			partCentre = partMatrix * glm::vec4(partCentre, 1);
			glm::mat3 partRotation = glm::mat3(*m_animationUniform);

			check = shader->
				checkViewingFrustum(partCentre, partSize, partRotation);
		}
		else
		{
			check = shader->
				getViewingFrustum()->checkCube(partCentre, partSize);
		}

		if (check)
		{
			drawArrays();
		}
	}

	glm::vec3 ModelMesh::getSize()
	{
		return m_size;
	}

	glm::vec3 ModelMesh::getCentre()
	{
		return m_minPoint + 0.5f * m_size;
	}

	void ModelMesh::checkMinMax(glm::vec3& _vertexPosition)
	{
		if (m_minPoint.x > m_maxPoint.x)
		{
			m_minPoint = _vertexPosition;
			m_maxPoint = _vertexPosition;
			return;
		}
		if (_vertexPosition.x < m_minPoint.x)
		{
			m_minPoint.x = _vertexPosition.x;
		}
		else if (_vertexPosition.x > m_maxPoint.x)
		{
			m_maxPoint.x = _vertexPosition.x;
		}
		if (_vertexPosition.y < m_minPoint.y)
		{
			m_minPoint.y = _vertexPosition.y;
		}
		else if (_vertexPosition.y > m_maxPoint.y)
		{
			m_maxPoint.y = _vertexPosition.y;
		}
		if (_vertexPosition.z < m_minPoint.z)
		{
			m_minPoint.z = _vertexPosition.z;
		}
		else if (_vertexPosition.z > m_maxPoint.z)
		{
			m_maxPoint.z = _vertexPosition.z;
		}
	}

	void ModelMesh::checkMin(glm::vec3& _vertexPosition)
	{
		if (_vertexPosition.x < m_minPoint.x)
		{
			m_minPoint.x = _vertexPosition.x;
		}
		if (_vertexPosition.y < m_minPoint.y)
		{
			m_minPoint.y = _vertexPosition.y;
		}
		if (_vertexPosition.z < m_minPoint.z)
		{
			m_minPoint.z = _vertexPosition.z;
		}
	}

	void ModelMesh::checkMax(glm::vec3& _vertexPosition)
	{
		if (_vertexPosition.x > m_maxPoint.x)
		{
			m_maxPoint.x = _vertexPosition.x;
		}
		if (_vertexPosition.y > m_maxPoint.y)
		{
			m_maxPoint.y = _vertexPosition.y;
		}
		if (_vertexPosition.z > m_maxPoint.z)
		{
			m_maxPoint.z = _vertexPosition.z;
		}
	}

	void ModelMesh::drawArrays()
	{
		std::shared_ptr<ShaderProgram> shader = m_context.lock()->
			getCurrentShader();

		std::string textureCheck[10];

		for (int i = 0; i < 10; i++)
		{
			shader->getUniforms()->getUniformName(i, textureCheck[i]);
		}

		int listItr = 0;
		for (std::list<std::shared_ptr<Material> >::iterator itr = m_materials.begin();
			itr != m_materials.end(); itr++)
		{
			if (*itr)
			{
				if ((*itr)->m_colourMap.lock())
				{
					if (textureCheck[0] != "")
					{
						shader->setUniform(textureCheck[0], (*itr)->m_colourMap.lock());
					}
					if (textureCheck[5] != "")
					{
						shader->setUniform(textureCheck[5], (*itr)->m_colourFactor);
					}
				}
			}

			glBindVertexArray(getId(listItr));
			glDrawArrays(GL_TRIANGLES, 0, getVertexCount(listItr));
			listItr++;
		}
	}

	void ModelMesh::generateArrays()
	{
		m_buffers.resize(m_buffers.size() + 1);
		m_idList.resize(m_idList.size() + 1);

		glGenVertexArrays(1, &m_idList.back());

		if (!m_idList.back())
		{
			throw std::exception();
		}

		m_buffers.back().resize(8);
	}
}