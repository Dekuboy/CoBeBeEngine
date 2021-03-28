#include <memory>
#include <vector>
#include <glm/glm.hpp>

namespace glwrap
{
	class ObjAnimation;
	class ObjPart;

	/**
	* \brief Store information on part movement during animation frame
	*/
	class ObjTranslation
	{
	public:
		ObjTranslation(std::shared_ptr<ObjPart> _part, glm::vec3 _position,
			glm::vec3 _rotation);
		~ObjTranslation();
		
		/**
		* \brief Get ObjPart that Translation applies to
		*/
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
		std::weak_ptr<ObjPart> m_part; //!< ObjPart that Translation applies to
		
		float m_x;
		float m_y;
		float m_z;

		float m_xRotation;
		float m_yRotation;
		float m_zRotation;

	};

	// ------------------------------------------------------------------

	/**
	* \brief Contains information on part positions during frame of animation
	*/
	class ObjFrame
	{
	public:
		ObjFrame(std::shared_ptr<ObjAnimation> _animation);

		/**
		* \brief Copy _source values to _destination
		*/
		static void copy(std::shared_ptr<ObjFrame> _source, std::shared_ptr<ObjFrame> _destination);
		/**
		* \brief Merge from _source to _destination and store in _destination
		*/
		static void merge(std::shared_ptr<ObjFrame> _source, std::shared_ptr<ObjFrame> _destination,
			double _weight = 0.5f);

		/**
		* \brief Get list of different part movements in frame
		*/
		std::vector<std::shared_ptr<ObjTranslation> > getTranslations();
		/**
		* \brief Get translation of a specific part of the object 
		* -if _add, add a translation to base position if there is no part translation
		*/
		std::shared_ptr<ObjTranslation> getTranslation(std::shared_ptr<ObjPart> _part, bool _add = false);

	private:
		friend class ObjAnimation;

		std::weak_ptr<ObjAnimation> m_animation; //!< Parent animation that frame is attached to
		std::vector<std::shared_ptr<ObjTranslation> > m_translations; //!< The translations that apply to separate parts during frame

	};
}