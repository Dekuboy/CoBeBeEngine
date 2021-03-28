#include <glwrap/ObjFrame.h>
#include <glwrap/ObjPart.h>

namespace glwrap
{
	ObjTranslation::ObjTranslation(std::shared_ptr<ObjPart> _part, glm::vec3 _position,
		glm::vec3 _rotation)
	{
		m_part = _part;
		
		m_x = _position.x;
		m_y = _position.y;
		m_z = _position.z;

		m_xRotation = _rotation.x;
		m_yRotation = _rotation.y;
		m_zRotation = _rotation.z;
	}

	ObjTranslation::~ObjTranslation()
	{

	}

	std::shared_ptr<ObjPart> ObjTranslation::getPart()
	{
		return m_part.lock();
	}

	float ObjTranslation::getX()
	{
		return m_x;
	}

	float ObjTranslation::getY()
	{
		return m_y;
	}

	float ObjTranslation::getZ()
	{
		return m_z;
	}

	float ObjTranslation::getRelativeX()
	{
		return (m_x / m_part.lock()->getSize().x) * 100.0f;
		//return x / part->getSize().x;
	}

	float ObjTranslation::getRelativeY()
	{
		return (m_y / m_part.lock()->getSize().y) * 100.0f;
		//std::cout << part->getName() << " " << y << " " << part->getSize().y << std::endl;
		//return y / part->getSize().y;
		//return y;
	}

	float ObjTranslation::getRelativeZ()
	{
		return (m_z / m_part.lock()->getSize().z) * 100.0f;
		//return z / part->getSize().z;
	}

	void ObjTranslation::setX(float _x)
	{
		m_x = _x;
	}

	void ObjTranslation::setY(float _y)
	{
		m_y = _y;
	}

	void ObjTranslation::setZ(float _z)
	{
		m_z = _z;
	}

	float ObjTranslation::getXRotation()
	{
		return m_xRotation;
	}

	float ObjTranslation::getYRotation()
	{
		return m_yRotation;
	}

	float ObjTranslation::getZRotation()
	{
		return m_zRotation;
	}

	void ObjTranslation::setXRotation(float _xRotation)
	{
		m_xRotation = _xRotation;
	}

	void ObjTranslation::setYRotation(float _yRotation)
	{
		m_yRotation = _yRotation;
	}

	void ObjTranslation::setZRotation(float _zRotation)
	{
		m_zRotation = _zRotation;
	}


	// ------------------------------------------------------------------


	ObjFrame::ObjFrame(std::shared_ptr<ObjAnimation> _animation)
	{
		m_animation = _animation;
	}

	void ObjFrame::copy(std::shared_ptr<ObjFrame> _source, std::shared_ptr<ObjFrame> _destination)
	{
		std::shared_ptr<ObjTranslation> translation;
		std::shared_ptr<ObjPart> part;
		glm::vec3 position, rotation;
		_destination->m_translations.clear();

		for (std::vector<std::shared_ptr<ObjTranslation> >::iterator itr = _source->m_translations.begin();
			itr != _source->m_translations.end(); itr++)
		{
			translation = (*itr);
			part = translation->getPart();
			position = glm::vec3(translation->getX(), translation->getY(), translation->getZ());
			rotation = glm::vec3(translation->getXRotation(), translation->getYRotation(), translation->getZRotation());
			_destination->m_translations.push_back(std::make_shared<ObjTranslation>(part,
				position,
				rotation));
		}
	}

	void ObjFrame::merge(std::shared_ptr<ObjFrame> _source, std::shared_ptr<ObjFrame> _destination, double _weight)
	{
		std::shared_ptr<ObjTranslation> translation;
		std::shared_ptr<ObjTranslation> to;
		std::shared_ptr<ObjPart> part;

		glm::vec3 empty(0);

		for (std::vector<std::shared_ptr<ObjTranslation> >::iterator itr = _source->m_translations.begin();
			itr != _source->m_translations.end(); itr++)
		{
			to = NULL;
			translation = (*itr);

			for (std::vector<std::shared_ptr<ObjTranslation> >::iterator second = _destination->m_translations.begin();
				second != _destination->m_translations.end(); second++)
			{
				if (translation->getPart() == (*second)->getPart())
				{
					to = (*second);
				}
			}

			if (to == nullptr)
			{
				part = translation->getPart();
				_destination->m_translations.push_back(std::make_shared<ObjTranslation>
					(part, empty, empty));

				to = _destination->m_translations.at(_destination->m_translations.size() - 1);
			}

			float dX = translation->getX() - to->getX();
			float dY = translation->getY() - to->getY();
			float dZ = translation->getZ() - to->getZ();

			float dRX = translation->getXRotation() - to->getXRotation();
			float dRY = translation->getYRotation() - to->getYRotation();
			float dRZ = translation->getZRotation() - to->getZRotation();

			to->setX(to->getX() + dX * _weight);
			to->setY(to->getY() + dY * _weight);
			to->setZ(to->getZ() + dZ * _weight);

			to->setXRotation(to->getXRotation() + dRX * _weight);
			to->setYRotation(to->getYRotation() + dRY * _weight);
			to->setZRotation(to->getZRotation() + dRZ * _weight);
		}
	}

	std::vector<std::shared_ptr<ObjTranslation> > ObjFrame::getTranslations()
	{
		return m_translations;
	}

	std::shared_ptr<ObjTranslation> ObjFrame::getTranslation(std::shared_ptr<ObjPart> _part, bool _add)
	{
		for (std::vector<std::shared_ptr<ObjTranslation> >::iterator itr = m_translations.begin();
			itr != m_translations.end(); itr++)
		{
			if ((*itr)->getPart() == _part)
			{
				return (*itr);
			}
		}

		if (_add == true)
		{
			glm::vec3 empty(0);
			m_translations.push_back(std::make_shared<ObjTranslation>(_part, empty, empty));

			return m_translations.at(m_translations.size() - 1);
		}

		return NULL;
	}
}