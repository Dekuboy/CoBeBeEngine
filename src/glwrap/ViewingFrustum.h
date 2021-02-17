#include <glm/glm.hpp>
#include <list>

namespace glwrap
{
	class Plane
	{
	public:
		Plane();
		Plane(glm::vec4 _planeEquation);

		glm::vec4 getPlaneEquation();
		void setPlaneEquation(glm::vec4 _planeEquation);

		void normalize();

	private:
		glm::vec4 m_planeEquation;

	};

	class ViewingFrustum
	{
	public:
		ViewingFrustum();

		void constructFrustum(glm::mat4 _clipSpace);

		bool checkPoint(glm::vec3 _point);
		bool checkCube(glm::vec3 _centre, glm::vec3 _size);
		bool checkCube(glm::vec3 _centre, glm::vec3 _size, glm::mat3 _rotation);
		bool checkSphere(glm::vec3 _centre, float _radius);

	private:
		std::list<Plane> m_planes; ///< Viewing planes: L,R,B,T,N,F

	};

}