#include <cobebe/Core/Component.h>
#include <glm/glm.hpp>

namespace cobebe
{
	/**
	* \brief Stores the world space variables of an Entity
	*/
	class Transform : public Component
	{
	public:
		Transform();

		glm::vec3 m_position; ///< Position of Entity in world space
		glm::mat3 m_rotation; ///< Rotation of Entity in world space
		glm::vec3 m_scale; ///< Scale of Entity in world space

		/**
		* \brief Returns the model matrix for rendering
		*/
		glm::mat4 getModel();

	private:
		glm::mat4 m_model; ///< Stores model matrix for rendering
		void onPreDisplay();

	};
}