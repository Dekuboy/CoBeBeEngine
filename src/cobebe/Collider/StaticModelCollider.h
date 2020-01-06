#include <cobebe/Collider/Collider.h>
#include <glwrap/glwrap.h>

namespace cobebe
{
	struct Extent
	{
		glm::vec3 m_max;
		glm::vec3 m_min;
	};

	struct ColliderColumn
	{
		glm::vec3 m_position;
		glm::vec3 m_size;
		std::vector<glwrap::Face> m_faces;

		bool isColliding(glm::vec3 _position, glm::vec3 _size);

		void getColliding(glm::vec3 _position, glm::vec3 _size,
			std::vector<glwrap::Face>& _collisions);
	};

	class StaticModelCollider : public Collider
	{
	public:
		StaticModelCollider();

		Extent getExtent();

		bool isColliding(glwrap::Face& _face, glm::vec3 _position,
			glm::vec3 _size);

		bool isColliding(glm::vec3 _position, glm::vec3 _size);
		void getColliding(glm::vec3 _position, glm::vec3 _size);

		glm::vec3 getCollisionResponse(glm::vec3 _position,
			glm::vec3 _size, bool& _solved);

	private:
		std::vector<std::shared_ptr<ColliderColumn>> m_cols;
		Extent m_extent;

		float m_resolution;
		float m_tryStep;
		float m_maxStep;
		float m_tryInc;
		float m_maxInc;

		std::vector<glwrap::Face> m_collisions;

		void generateExtent();
		void addFace(glwrap::Face _face);
		glm::vec3 faceNormal(glwrap::Face& _face);

		void onInit();

	};
}