#include <cobebe/Collider/Collider.h>
#include <glwrap/glwrap.h>

/**
* Code sourced from GEP Labs
*/

namespace cobebe
{
	/**
	* \brief Stores max and min xyz values
	*/
	struct Extent
	{
		glm::vec3 m_max; ///< Max xyz extent
		glm::vec3 m_min; ///< Min xyz extent
	};

	/**
	* \brief Partition Column within StaticModelCollider
	*/
	struct ColliderColumn
	{
		glm::vec3 m_position; ///< Position of column
		glm::vec3 m_size; ///< Scale of column
		std::vector<glwrap::Face> m_faces; ///< Faces within column

		/**
		* \brief Checks if input is colliding with column faces
		*/
		bool isColliding(glm::vec3 _position, glm::vec3 _size);

		/**
		* \brief Returns all faces currently colliding
		*/
		void getColliding(glm::vec3 _position, glm::vec3 _size,
			std::vector<glwrap::Face>& _collisions);
	};

	/**
	* \brief Converts current model loaded to Renderer to partitions for collisions
	* -Assumes model is at O
	*/
	class StaticModelCollider : public Collider
	{
	public:
		StaticModelCollider();

		/**
		* \brief Retrieves Extent values
		*/
		Extent getExtent();

		/**
		* \brief Check for collision with face
		*/
		bool isColliding(glwrap::Face& _face, glm::vec3 _position,
			glm::vec3 _size);

		/**
		* \brief Checks for collisions with previously collided faces
		*/
		bool isColliding(glm::vec3 _position, glm::vec3 _size);
		/**
		* \brief Gets all colliding faces within appropriate partition
		*/
		void getColliding(glm::vec3 _position, glm::vec3 _size);

		/**
		* \brief Find new position which doesn't collide
		*/
		glm::vec3 getCollisionResponse(glm::vec3 _position,
			glm::vec3 _size, bool& _solved);

	private:
		std::vector<std::shared_ptr<ColliderColumn> > m_cols; ///< Partitions of model containing faces
		Extent m_extent; ///< Max and min xyz values

		float m_resolution; ///< Partition divisor for allocating size
		float m_tryStep; ///< Distance to step per test
		float m_maxStep; ///< Max step height
		float m_tryInc; ///< Distance to increment per test
		float m_maxInc; ///< Max increment for cludge

		std::vector<glwrap::Face> m_collisions; ///< Faces currently colliding

		/**
		* \brief Find the max and min xyz values
		*/
		void generateExtent();
		/**
		* \brief Add face to partition
		*/
		void addFace(glwrap::Face _face);
		/**
		* \brief Find face normal
		*/
		glm::vec3 faceNormal(glwrap::Face& _face);

		void onInit();

	};
}