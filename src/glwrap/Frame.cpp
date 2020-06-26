#include <glwrap/Frame.h>
#include <glwrap/Part.h>

namespace glwrap
{
	Translation::Translation(std::shared_ptr<Part> _part, float _x, float _y, float _z,
		float _xRotation, float _yRotation, float _zRotation)
	{
		m_part = _part;
		
		m_x = _x;
		m_y = _y;
		m_z = _z;

		m_xRotation = _xRotation;
		m_yRotation = _yRotation;
		m_zRotation = _zRotation;
	}

	Translation::~Translation()
	{

	}

	std::shared_ptr<Part> Translation::getPart()
	{
		return m_part.lock();
	}

	float Translation::getX()
	{
		return m_x;
	}

	float Translation::getY()
	{
		return m_y;
	}

	float Translation::getZ()
	{
		return m_z;
	}

	float Translation::getRelativeX()
	{
		return (m_x / m_part.lock()->getSize().x) * 100.0f;
		//return x / part->getSize().x;
	}

	float Translation::getRelativeY()
	{
		return (m_y / m_part.lock()->getSize().y) * 100.0f;
		//std::cout << part->getName() << " " << y << " " << part->getSize().y << std::endl;
		//return y / part->getSize().y;
		//return y;
	}

	float Translation::getRelativeZ()
	{
		return (m_z / m_part.lock()->getSize().z) * 100.0f;
		//return z / part->getSize().z;
	}

	void Translation::setX(float _x)
	{
		m_x = _x;
	}

	void Translation::setY(float _y)
	{
		m_y = _y;
	}

	void Translation::setZ(float _z)
	{
		m_z = _z;
	}

	float Translation::getXRotation()
	{
		return m_xRotation;
	}

	float Translation::getYRotation()
	{
		return m_yRotation;
	}

	float Translation::getZRotation()
	{
		return m_zRotation;
	}

	void Translation::setXRotation(float _xRotation)
	{
		m_xRotation = _xRotation;
	}

	void Translation::setYRotation(float _yRotation)
	{
		m_yRotation = _yRotation;
	}

	void Translation::setZRotation(float _zRotation)
	{
		m_zRotation = _zRotation;
	}


	// ------------------------------------------------------------------


	Frame::Frame(std::shared_ptr<Animation> _animation)
	{
		m_animation = _animation;
	}

	void Frame::copy(std::shared_ptr<Frame> _source, std::shared_ptr<Frame> _destination)
	{
		std::shared_ptr<Translation> translation;
		_destination->m_translations.clear();

		for (std::vector<std::shared_ptr<Translation>>::iterator itr = _source->m_translations.begin();
			itr != _source->m_translations.end(); itr++)
		{
			translation = (*itr);
			_destination->m_translations.push_back(std::make_shared<Translation>(translation->getPart(),
				translation->getX(), translation->getY(), translation->getZ(),
				translation->getXRotation(), translation->getYRotation(), translation->getZRotation()));
		}
	}

	void Frame::merge(std::shared_ptr<Frame> _source, std::shared_ptr<Frame> _destination, double _weight)
	{
		std::shared_ptr<Translation> translation;
		std::shared_ptr<Translation> to;

		for (std::vector<std::shared_ptr<Translation>>::iterator itr = _source->m_translations.begin();
			itr != _source->m_translations.end(); itr++)
		{
			to = NULL;
			translation = (*itr);

			for (std::vector<std::shared_ptr<Translation>>::iterator second = _destination->m_translations.begin();
				second != _destination->m_translations.end(); second++)
			{
				if (translation->getPart() == (*second)->getPart())
				{
					to = (*second);
				}
			}

			if (to == NULL)
			{
				_destination->m_translations.push_back(std::make_shared<Translation>
					(translation->getPart(), 0, 0, 0, 0, 0, 0));

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

	std::vector<std::shared_ptr<Translation>> Frame::getTranslations()
	{
		return m_translations;
	}

	std::shared_ptr<Translation> Frame::getTranslation(std::shared_ptr<Part> _part, bool _add)
	{
		for (std::vector<std::shared_ptr<Translation>>::iterator itr = m_translations.begin();
			itr != m_translations.end(); itr++)
		{
			if ((*itr)->getPart() == _part)
			{
				return (*itr);
			}
		}

		if (_add == true)
		{
			m_translations.push_back(std::make_shared<Translation>(_part, 0, 0, 0, 0, 0, 0));

			return m_translations.at(m_translations.size() - 1);
		}

		return NULL;
	}
}