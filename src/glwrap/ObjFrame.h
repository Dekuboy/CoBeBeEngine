#include <memory>
#include <vector>
#include <glm/glm.hpp>

namespace glwrap
{
	class ObjAnimation;
	class ObjPart;

	class Translation
	{
	public:
		Translation(std::shared_ptr<ObjPart> _part, glm::vec3 _position,
			glm::vec3 _rotation);
		~Translation();

		std::shared_ptr<ObjPart> getPart();

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
		std::weak_ptr<ObjPart> m_part;
		
		float m_x;
		float m_y;
		float m_z;

		float m_xRotation;
		float m_yRotation;
		float m_zRotation;

	};

	// ------------------------------------------------------------------

	class ObjFrame
	{
	public:
		ObjFrame(std::shared_ptr<ObjAnimation> _animation);

		static void copy(std::shared_ptr<ObjFrame> _source, std::shared_ptr<ObjFrame> _destination);
		static void merge(std::shared_ptr<ObjFrame> _source, std::shared_ptr<ObjFrame> _destination,
			double _weight = 0.5f);

		std::vector<std::shared_ptr<Translation> > getTranslations();
		std::shared_ptr<Translation> getTranslation(std::shared_ptr<ObjPart> _part, bool _add = false);

	private:
		friend class ObjAnimation;

		std::shared_ptr<ObjAnimation> m_animation;
		std::vector<std::shared_ptr<Translation> > m_translations;

	};
}