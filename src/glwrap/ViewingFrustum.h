#include <glm/glm.hpp>
#include <list>

namespace glwrap
{
	/**
	* \brief Represents a plane using the plane equation
	* ax + by +cz + d = 0
	*/
	class Plane
	{
	public:
		Plane();
		Plane(glm::vec4 _planeEquation);

		/**
		* \brief Gets the values that represent the plane
		*/
		glm::vec4 getPlaneEquation();
		/**
		* \brief Sets the values that represent the plane
		*/
		void setPlaneEquation(glm::vec4 _planeEquation);

		/**
		* \brief Normalise the values in the plane equation
		*/
		void normalize();

	private:
		glm::vec4 m_planeEquation; //!< Values that represent the plane (ax+by+cz+d=0)

	};

	/**
	* \brief Represents the camera view within world space and culls out objects out of view
	*/
	class ViewingFrustum
	{
	public:
		ViewingFrustum();

		/**
		* \brief Creates the viewing planes based on input matrix
		* -_clipSpace = (projection matrix) * (inverse view matrix)
		*/
		void constructFrustum(glm::mat4 _clipSpace);

		/**
		* \brief Checks if a point in the world is within viewing space
		*/
		bool checkPoint(glm::vec3 _point);
		/**
		* \brief Checks if a cube is within viewing space
		*/
		bool checkCube(glm::vec3 _centre, glm::vec3 _size);
		/**
		* \brief Checks if a rotated cube is within viewing space
		*/
		bool checkCube(glm::vec3 _centre, glm::vec3 _size, glm::mat3 _rotation);
		/**
		* \brief Checks if a sphere is within viewing space
		*/
		bool checkSphere(glm::vec3 _centre, float _radius);

	private:
		std::list<Plane> m_planes; //!< Viewing planes: L,R,B,T,N,F

	};

}