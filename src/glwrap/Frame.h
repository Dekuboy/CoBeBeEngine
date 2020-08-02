#include <memory>
#include <vector>
#include <glm/glm.hpp>

namespace glwrap
{
	class Animation;
	class Part;

	class Translation
	{
	public:
		Translation(std::shared_ptr<Part> _part, glm::vec3 _position,
			glm::vec3 _rotation);
		~Translation();

		std::shared_ptr<Part> getPart();

		float getX();
		float getY();
		float getZ();

		float getRelativeX();
		float getRelativeY();
		float getRelativeZ();

		void setX(float _x);
		void setY(float _y);
		void setZ(float _z);

		float getXRotation();
		float getYRotation();
		float getZRotation();

		void setXRotation(float _xRotation);
		void setYRotation(float _yRotation);
		void setZRotation(float _ZRotation);

	private:
		std::weak_ptr<Part> m_part;
		
		float m_x;
		float m_y;
		float m_z;

		float m_xRotation;
		float m_yRotation;
		float m_zRotation;

	};

	// ------------------------------------------------------------------

	class Frame
	{
	public:
		Frame(std::shared_ptr<Animation> _animation);

		static void copy(std::shared_ptr<Frame> _source, std::shared_ptr<Frame> _destination);
		static void merge(std::shared_ptr<Frame> _source, std::shared_ptr<Frame> _destination,
			double _weight = 0.5f);

		std::vector<std::shared_ptr<Translation> > getTranslations();
		std::shared_ptr<Translation> getTranslation(std::shared_ptr<Part> _part, bool _add = false);

	private:
		friend class Animation;

		std::shared_ptr<Animation> m_animation;
		std::vector<std::shared_ptr<Translation> > m_translations;

	};
}