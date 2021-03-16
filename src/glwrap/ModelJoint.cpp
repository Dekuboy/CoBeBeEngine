#include <glwrap/ModelJoint.h>
#include <glwrap/TriFace.h>
#include <glwrap/VertexBuffer.h>
#include <glwrap/GltfModel.h>
//#include <glwrap/ModelFrame.h>
//#include <glwrap/ModelAnimation.h>
#include <glwrap/Material.h>
#include <glwrap/Context.h>
#include <glwrap/ShaderProgram.h>
#include <glwrap/ViewingFrustum.h>
#include <glm/ext.hpp>

namespace glwrap
{
	ModelJoint::ModelJoint(std::shared_ptr<GltfModel> _mesh, std::string _name)
	{
		m_name = _name;
		m_model = _mesh;
		m_animationUniform = glm::mat4(1);
		m_useMaterial = false;

		generateArrays();
	}

	ModelJoint::~ModelJoint()
	{

	}

	std::string ModelJoint::getName()
	{
		return m_name;
	}

	std::vector<std::shared_ptr<TriFace> >& ModelJoint::getFaces()
	{
		return m_faces;
	}

	void ModelJoint::addFace(std::shared_ptr<TriFace> _face)
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

	void ModelJoint::setBuffer(std::string _attribute, std::shared_ptr<VertexBuffer> _buffer, int _materialId)
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

	int ModelJoint::getVertexCount(int _materialId)
	{
		if (m_buffers.size() < 1)
		{
			throw std::exception();
		}

		return m_buffers.at(_materialId).at(0)->getDataSize() / m_buffers.at(_materialId).at(0)->getComponents();
	}

	GLuint ModelJoint::getId(int _materialId)
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

	void ModelJoint::draw()
	{
		glm::vec3 translateVector(m_offsetX, m_offsetY, m_offsetZ);

		m_animationUniform = glm::translate(m_animationUniform, translateVector);
		translate();
		m_animationUniform = glm::translate(m_animationUniform, -translateVector);

		drawArrays();
	}

	void ModelJoint::cullAndDraw()
	{
		glm::vec3 translateVector(m_offsetX, m_offsetY, m_offsetZ);
		std::shared_ptr<ShaderProgram> shader = m_context.lock()->getCurrentShader();

		m_animationUniform = glm::translate(m_animationUniform, translateVector);
		translate();
		glm::mat4 partMatrix = m_animationUniform;
		m_animationUniform = glm::translate(m_animationUniform, -translateVector);

		if (m_model.lock()->getCullAnimation())
		{
			if (shader->checkModelInView() && m_animationUniform == glm::mat4(1))
			{
				drawArrays();
			}
			else
			{
				glm::vec3 partCentre = partMatrix * glm::vec4(0, 0, 0, 1);
				glm::mat3 partRotation = glm::mat3(m_animationUniform);
				glm::vec3 partSize = getSize();

				if (shader->
					checkViewingFrustum(partCentre, partSize, partRotation))
				{
					drawArrays();
				}
				else
				{
					m_animationUniform = glm::mat4(1);
				}
			}
		}
		else
		{
			glm::vec3 partCentre = partMatrix * glm::vec4(0, 0, 0, 1);
			glm::mat3 partRotation = glm::mat3(m_animationUniform);
			glm::vec3 partSize = getSize();

			if (shader->
				checkViewingFrustum(partCentre, partSize, partRotation))
			{
				drawArrays();
			}
			else
			{
				m_animationUniform = glm::mat4(1);
			}
		}
	}

	glm::vec3 ModelJoint::getSize()
	{
		return glm::vec3(m_maxX - m_minX, m_maxY - m_minY, m_maxZ - m_minZ);
	}

	void ModelJoint::translate()
	{
		//std::vector<std::shared_ptr<ModelAnimation> > animations =
		//	m_model.lock()->getAnimations();
		//std::shared_ptr<ModelFrame> frame;
		//std::shared_ptr<Translation> translation;

		//glm::vec3 translateVector(0);

		//for (std::vector<std::shared_ptr<ObjAnimation> >::iterator itr = animations.begin();
		//	itr != animations.end(); itr++)
		//{
		//	if ((*itr)->getEnabled())
		//	{
		//		frame = (*itr)->getMergeFrame();
		//		translation = frame->getTranslation(m_self.lock());

		//		if (translation != nullptr)
		//		{
		//			translateVector = glm::vec3(translation->getX(), translation->getY(),
		//				translation->getZ());
		//			m_animationUniform = glm::translate(m_animationUniform, translateVector);

		//			m_animationUniform = glm::rotate(m_animationUniform,
		//				translation->getZRotation(), glm::vec3(0, 0, 1));
		//			m_animationUniform = glm::rotate(m_animationUniform,
		//				translation->getYRotation(), glm::vec3(0, 1, 0));
		//			m_animationUniform = glm::rotate(m_animationUniform,
		//				translation->getXRotation(), glm::vec3(1, 0, 0));
		//		}
		//	}
		//}
	}

	void ModelJoint::drawArrays()
	{
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

	void ModelJoint::generateArrays()
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