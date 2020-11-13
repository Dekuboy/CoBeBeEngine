#include <cobebe/Collider/StaticModelCollider.h>
#include <cobebe/Core/Entity.h>
#include <cobebe/Renderer/Renderer.h>
#include <cobebe/Resources/RendAssets.h>
#include <cobebe/Core/Transform.h>
#include <glm/ext.hpp>

int triBoxOverlap(float boxcenter[3],
	float boxhalfsize[3], float triverts[3][3]);

namespace cobebe
{
	bool ColliderColumn::isColliding(glm::vec3 _position, glm::vec3 _size)
	{
		for (std::vector<glwrap::Face>::iterator i = m_faces.begin(); i != m_faces.end(); i++)
		{
			float f[3][3] = { 0 };
			f[0][0] = i->pa.x;
			f[0][1] = i->pa.y;
			f[0][2] = i->pa.z;
			f[1][0] = i->pb.x;
			f[1][1] = i->pb.y;
			f[1][2] = i->pb.z;
			f[2][0] = i->pc.x;
			f[2][1] = i->pc.y;
			f[2][2] = i->pc.z;

			float bc[3] = { 0 };
			bc[0] = _position.x;
			bc[1] = _position.y;
			bc[2] = _position.z;
			float bhs[3] = { 0 };
			bhs[0] = _size.x / 2.0f;
			bhs[1] = _size.y / 2.0f;
			bhs[2] = _size.z / 2.0f;

			if (triBoxOverlap(bc, bhs, f))
			{
				return true;
			}
		}

		return false;
	}

	void ColliderColumn::getColliding(glm::vec3 _position, glm::vec3 _size,
		std::vector<glwrap::Face>& _collisions)
	{
		for (std::vector<glwrap::Face>::iterator i = m_faces.begin(); i != m_faces.end(); i++)
		{
			float f[3][3] = { 0 };
			f[0][0] = i->pa.x;
			f[0][1] = i->pa.y;
			f[0][2] = i->pa.z;
			f[1][0] = i->pb.x;
			f[1][1] = i->pb.y;
			f[1][2] = i->pb.z;
			f[2][0] = i->pc.x;
			f[2][1] = i->pc.y;
			f[2][2] = i->pc.z;

			float bc[3] = { 0 };
			bc[0] = _position.x;
			bc[1] = _position.y;
			bc[2] = _position.z;
			float bhs[3] = { 0 };
			bhs[0] = _size.x / 2.0f;
			bhs[1] = _size.y / 2.0f;
			bhs[2] = _size.z / 2.0f;

			if (triBoxOverlap(bc, bhs, f))
			{
				_collisions.push_back(*i);
			}
		}
	}

	StaticModelCollider::StaticModelCollider() : Collider(0)
	{
		m_resolution = 0;
		m_tryStep = 0;
		m_maxStep = 0;
		m_tryInc = 0;
		m_maxInc = 0;
	}

	StaticModelCollider::StaticModelCollider(int _mask) : Collider(_mask)
	{

	}

	Extent StaticModelCollider::getExtent()
	{
		return m_extent;
	}

	bool StaticModelCollider::isColliding(glwrap::Face& _face, glm::vec3 _position,
		glm::vec3 _size)
	{
		float f[3][3] = { 0 };
		f[0][0] = _face.pa.x;
		f[0][1] = _face.pa.y;
		f[0][2] = _face.pa.z;
		f[1][0] = _face.pb.x;
		f[1][1] = _face.pb.y;
		f[1][2] = _face.pb.z;
		f[2][0] = _face.pc.x;
		f[2][1] = _face.pc.y;
		f[2][2] = _face.pc.z;

		float bc[3] = { 0 };
		bc[0] = _position.x;
		bc[1] = _position.y;
		bc[2] = _position.z;
		float bhs[3] = { 0 };
		bhs[0] = _size.x / 2.0f;
		bhs[1] = _size.y / 2.0f;
		bhs[2] = _size.z / 2.0f;

		if (triBoxOverlap(bc, bhs, f))
		{
			return true;
		}

		return false;
	}

	bool StaticModelCollider::isColliding(glm::vec3 _position, glm::vec3 _size)
	{
		for (std::vector<glwrap::Face>::iterator i = m_collisions.begin();
			i != m_collisions.end(); i++)
		{
			float f[3][3] = { 0 };
			f[0][0] = i->pa.x;
			f[0][1] = i->pa.y;
			f[0][2] = i->pa.z;
			f[1][0] = i->pb.x;
			f[1][1] = i->pb.y;
			f[1][2] = i->pb.z;
			f[2][0] = i->pc.x;
			f[2][1] = i->pc.y;
			f[2][2] = i->pc.z;

			float bc[3] = { 0 };
			bc[0] = _position.x;
			bc[1] = _position.y;
			bc[2] = _position.z;
			float bhs[3] = { 0 };
			bhs[0] = _size.x / 2.0f;
			bhs[1] = _size.y / 2.0f;
			bhs[2] = _size.z / 2.0f;

			if (triBoxOverlap(bc, bhs, f))
			{
				return true;
			}
		}

		return false;
	}

	void StaticModelCollider::getColliding(glm::vec3 _position, glm::vec3 _size)
	{
		glm::vec3 pos = _position - m_extent.m_min;
		size_t x = (size_t)(pos.x / m_cols.at(0)->m_size.x);
		size_t y = (size_t)(pos.z / m_cols.at(0)->m_size.z);
		size_t idx = y * m_resolution + x;

		if (idx >= m_cols.size()) return;

		m_cols.at(idx)->getColliding(_position, _size, m_collisions);
	}

	glm::vec3 StaticModelCollider::getCollisionResponse(glm::vec3 _position,
		glm::vec3 _size, bool& _solved)
	{
		glm::vec3 solve = _position;
		_solved = false;

		m_collisions.clear();
		getColliding(solve, _size);

		if (!isColliding(solve, _size))
		{
			_solved = true;
			return solve;
		}

		// Favour Y faces first.
		for (std::vector<glwrap::Face>::iterator it = m_collisions.begin();
			it != m_collisions.end(); it++)
		{
			if (!isColliding(*it, solve, _size))
			{
				continue;
			}

			glm::vec3 n = faceNormal(*it);
			n = glm::normalize(n);
			//std::cout << n.x << " " << n.y << " " << n.z << std::endl;
			if (n.y < fabs(n.x) + fabs(n.z)) continue;

			float amount = m_tryStep;

			while (true)
			{
				solve = solve + n * amount;

				if (!isColliding(*it, solve, _size))
				{
					break;
				}

				solve = solve - n * amount;
				amount += m_tryStep;

				if (amount > m_maxStep)
				{
					break;
				}
			}
		}

		if (!isColliding(solve, _size))
		{
			_solved = true;
			return solve;
		}

		float amount = m_tryInc;

		while (true)
		{
			glm::vec3 total;

			// Try to uncollide using face normals
			for (std::vector<glwrap::Face>::iterator it = m_collisions.begin();
				it != m_collisions.end(); it++)
			{
				glm::vec3 n = faceNormal(*it);
				n = glm::normalize(n);
				total = total + n;
				solve = solve + n * amount;

				if (!isColliding(solve, _size))
				{
					_solved = true;
					return solve;
				}

				solve = solve - n * amount;
			}

			// Try to uncollide using averaged face normals
			total = glm::normalize(total);
			solve = solve + total * amount;

			if (!isColliding(solve, _size))
			{
				_solved = true;
				return solve;
			}

			solve = solve - total * amount;
			amount += m_tryInc;

			if (amount > m_maxInc)
			{
				break;
			}
		}

		_solved = false;
		return _position;
	}

	void StaticModelCollider::generateExtent()
	{
		std::vector<glm::vec3> positions;
		std::vector<std::shared_ptr<glwrap::Face> > faces;
		std::shared_ptr<Renderer> mr = getEntity()->getComponent<Renderer>();
		std::shared_ptr<Mesh> model = mr->getMesh();
		std::shared_ptr<WavefrontModel> objMtlModel = mr->getWavefrontModel();
		glm::mat3 modelMatrix = getTransform()->getModel();
		if (model)
		{
			faces = model->getFaces();
		}
		else if (objMtlModel)
		{
			faces = objMtlModel->getFaces();
		}

		for (size_t f = 0; f < faces.size(); f++)
		{
			glwrap::Face face = *faces.at(f);
			positions.push_back(modelMatrix * face.pa);
			positions.push_back(modelMatrix * face.pb);
			positions.push_back(modelMatrix * face.pc);
		}

		m_extent.m_max = positions.at(0);
		m_extent.m_min = positions.at(0);

		for (size_t i = 1; i < positions.size(); i++)
		{
			if (positions.at(i).x > m_extent.m_max.x) m_extent.m_max.x = positions.at(i).x;
			if (positions.at(i).y > m_extent.m_max.y) m_extent.m_max.y = positions.at(i).y;
			if (positions.at(i).z > m_extent.m_max.z) m_extent.m_max.z = positions.at(i).z;
			if (positions.at(i).x < m_extent.m_min.x) m_extent.m_min.x = positions.at(i).x;
			if (positions.at(i).y < m_extent.m_min.y) m_extent.m_min.y = positions.at(i).y;
			if (positions.at(i).z < m_extent.m_min.z) m_extent.m_min.z = positions.at(i).z;
		}

		m_extent.m_min = m_extent.m_min - glm::vec3(1);
		m_extent.m_max = m_extent.m_max + glm::vec3(1);
	}

	void StaticModelCollider::addFace(glwrap::Face _face)
	{
		glm::mat3 modelMatrix = getTransform()->getModel();
		glm::vec3 vertexPosition = modelMatrix * _face.pa;
		float f[3][3] = { 0 };
		f[0][0] = vertexPosition.x;
		f[0][1] = vertexPosition.y;
		f[0][2] = vertexPosition.z;
		vertexPosition = modelMatrix * _face.pb;
		f[1][0] = vertexPosition.x;
		f[1][1] = vertexPosition.y;
		f[1][2] = vertexPosition.z;
		vertexPosition = modelMatrix * _face.pc;
		f[2][0] = vertexPosition.x;
		f[2][1] = vertexPosition.y;
		f[2][2] = vertexPosition.z;

		bool found = false;

		for (size_t i = 0; i < m_cols.size(); i++)
		{
			float bc[3] = { 0 };
			bc[0] = m_cols.at(i)->m_position.x;
			bc[1] = m_cols.at(i)->m_position.y;
			bc[2] = m_cols.at(i)->m_position.z;

			// Overlap columns for sub column collision
			glm::vec3 s = m_cols.at(i)->m_size;
			s.x += 1;
			s.z += 1;

			float bhs[3] = { 0 };
			bhs[0] = s.x / 2.0f;
			bhs[1] = s.y / 2.0f;
			bhs[2] = s.z / 2.0f;

			if (triBoxOverlap(bc, bhs, f))
			{
				m_cols.at(i)->m_faces.push_back(_face);
				//std::cout << "Pushing face into " << i << std::endl;
				found = true;
			}
		}

		if (!found)
		{
			throw Exception("Face not assigned spatial partition");
		}
	}

	glm::vec3 StaticModelCollider::faceNormal(glwrap::Face& _face)
	{
		glm::vec3 N = glm::cross(
			_face.pa - _face.pc,
			_face.pb - _face.pc);

		return N;
	}

	void StaticModelCollider::onInit()
	{
		m_resolution = 10;
		m_tryStep = 0.001f;
		m_maxStep = 1.0f;
		m_tryInc = 0.01f;
		m_maxInc = 0.5f;

		std::shared_ptr<Renderer> mr = getEntity()->getComponent<Renderer>();
		if (mr)
		{
			std::vector<std::shared_ptr<glwrap::Face> > faces;
			std::shared_ptr<Mesh> model = mr->getMesh();
			std::shared_ptr<WavefrontModel> objMtlModel = mr->getWavefrontModel();
			if (model)
			{
				faces = model->getFaces();
			}
			else if (objMtlModel)
			{
				faces = objMtlModel->getFaces();
			}
			else
			{
				return;
			}
			generateExtent();

			// Create collision columns
			glm::vec3 size = m_extent.m_max - m_extent.m_min;
			glm::vec3 colSize = size / m_resolution;
			colSize.y = size.y;

			for (size_t y = 0; y < m_resolution; y++)
			{
				glm::vec3 pos = m_extent.m_min + colSize / 2.0f;
				pos.z += (float)y * colSize.z;

				for (size_t x = 0; x < m_resolution; x++)
				{
					std::shared_ptr<ColliderColumn> cc = std::make_shared<ColliderColumn>();
					cc->m_size = colSize;

					// Overlap columns for sub column collision
					//cc->size.x += 1.0f;
					//cc->size.z += 1.0f;
					// Conflicts with x / y index generation when matching column to collide with.
					// Done when adding face instead.

					cc->m_position = pos;
					m_cols.push_back(cc);
					pos.x += colSize.x;
				}
			}

			glwrap::Face face;

			for (size_t f = 0; f < faces.size(); f++)
			{
				face = *faces.at(f);
				addFace(face);
			}
		}
	}
}