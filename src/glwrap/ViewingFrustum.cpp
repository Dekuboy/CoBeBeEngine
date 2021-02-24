#include "ViewingFrustum.h"

namespace glwrap
{
	Plane::Plane()
	{
		m_planeEquation = glm::vec4(0);
	}

	Plane::Plane(glm::vec4 _planeEquation)
	{
		m_planeEquation = _planeEquation;
	}

	glm::vec4 Plane::getPlaneEquation()
	{
		return m_planeEquation;
	}

	void Plane::setPlaneEquation(glm::vec4  _planeEquation)
	{
		m_planeEquation = _planeEquation;
	}

	void Plane::normalize()
	{
		glm::vec3 normal = m_planeEquation;
		m_planeEquation /= glm::length(normal);
	}

	ViewingFrustum::ViewingFrustum()
	{
		m_planes.resize(6);
	}

	void ViewingFrustum::constructFrustum(glm::mat4 _clipSpace)
	{
		Plane plane;
		glm::mat4 clipSpace = glm::transpose(_clipSpace);
		glm::vec4 row4 = clipSpace[3];
		int i = 0;
		for (std::list<Plane>::iterator itr = m_planes.begin(); itr != m_planes.end(); itr++)
		{
			itr->setPlaneEquation(row4 + clipSpace[i]);
			itr->normalize();
			itr++;
			itr->setPlaneEquation(row4 - clipSpace[i]);
			itr->normalize();
			i++;
		}
	}

	bool ViewingFrustum::checkPoint(glm::vec3 _point)
	{
		glm::vec4 plane, pos = glm::vec4(_point, 1);
		for (std::list<Plane>::iterator itr = m_planes.begin(); itr != m_planes.end(); itr++)
		{
			plane = itr->getPlaneEquation();
			if (glm::dot(pos, plane) < 0.0f)
			{
				return false;
			}
		}
		return true;
	}

	bool ViewingFrustum::checkCube(glm::vec3 _centre, glm::vec3 _size)
	{
		glm::vec3 half = _size / 2.0f;
		glm::vec4 basePos = glm::vec4(_centre + half, 1);
		glm::vec4 pos, planeEquation;
		int polarity = -1;
		for (std::list<Plane>::iterator itr = m_planes.begin(); itr != m_planes.end(); itr++)
		{
			pos = basePos;
			planeEquation = itr->getPlaneEquation();
			polarity = -1;
			for (int i = 0; i < 2; i++)
			{
				pos.x -= _size.x;
				if (glm::dot(pos, planeEquation) > 0.0f)
				{
					break;
				}
				pos.y += (float)polarity * _size.y;
				if (glm::dot(pos, planeEquation) > 0.0f)
				{
					break;
				}
				pos.x += _size.x;
				if (glm::dot(pos, planeEquation) > 0.0f)
				{
					break;
				}
				pos.z += (float)polarity * _size.z;
				if (glm::dot(pos, planeEquation) > 0.0f)
				{
					break;
				}
				if (polarity == -1)
				{
					polarity = 1;
				}
				else
				{
					return false;
				}
			}
		}
		return true;
	}

	bool ViewingFrustum::checkCube(glm::vec3 _centre, glm::vec3 _size, glm::mat3 _rotation)
	{
		glm::vec3 xVec = (_size.x / 2.0f) * _rotation[0];
		glm::vec3 yVec = (_size.y / 2.0f) * _rotation[1];
		glm::vec3 zVec = (_size.z / 2.0f) * _rotation[2];
		glm::vec3 basePos = _centre + xVec + yVec + zVec, pos;
		glm::vec4 planeEquation;
		int polarity = -1;
		for (std::list<Plane>::iterator itr = m_planes.begin(); itr != m_planes.end(); itr++)
		{
			pos = basePos;
			planeEquation = itr->getPlaneEquation();
			polarity = -1;
			for (int i = 0; i < 2; i++)
			{
				pos -= xVec;
				if (glm::dot(glm::vec4(pos, 1), planeEquation) > 0.0f)
				{
					break;
				}
				pos += (float)polarity * yVec;
				if (glm::dot(glm::vec4(pos, 1), planeEquation) > 0.0f)
				{
					break;
				}
				pos += xVec;
				if (glm::dot(glm::vec4(pos, 1), planeEquation) > 0.0f)
				{
					break;
				}
				pos += (float)polarity * zVec;
				if (glm::dot(glm::vec4(pos, 1), planeEquation) > 0.0f)
				{
					break;
				}
				if (polarity == -1)
				{
					polarity = 1;
				}
				else
				{
					return false;
				}
			}
		}
		return true;
	}

	bool ViewingFrustum::checkSphere(glm::vec3 _centre, float _radius)
	{
		glm::vec4 pos = glm::vec4(_centre, 1);
		for (std::list<Plane>::iterator itr = m_planes.begin(); itr != m_planes.end(); itr++)
		{
			if (glm::dot(pos, itr->getPlaneEquation()) < -_radius)
			{
				return false;
			}
		}
		return true;
	}

}