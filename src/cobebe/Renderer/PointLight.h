#include <glwrap/glwrap.h>
#include <glm/glm.hpp>
#include <memory>
#include <vector>

namespace cobebe
{
	class Lighting;
	class Shader;
	class Core;

	/**
	* \brief Holds values for point lights in the engine
	*/
	class PointLight
	{
	public:
		PointLight();

		/**
		* \brief Retrieves PointLight position
		*/
		glm::vec3 getPosition();
		/**
		* \brief Sets PointLight position and updates matrices
		*/
		void setPosition(glm::vec3 _position);

		/**
		* \brief Retrieves PointLight Colour
		*/
		glm::vec3 getColour();
		/**
		* \brief Sets PointLightColour
		*/
		void setColour(glm::vec3 _lightCol);

		/**
		* \brief Retrieves PointLight effective radius
		*/
		float getRadius();
		/**
		* \brief Sets PointLight effective Radius
		*/
		void setRadius(float _radius);

	private:
		friend class Lighting;
		glm::vec3 m_position; ///< Stored position, when changed, the light space matrices updates
		glm::vec3 m_colour; ///< Stored colour
		float m_radius; ///< Stored effective light radius
		std::vector<glm::mat4> m_lightSpaces; ///< DepthCube perspective matrices to pass in

		std::shared_ptr<glwrap::DepthCube> m_depthCube; ///< DepthCube to render shadows to

		std::weak_ptr<Core> m_core; ///< Pointer to games core

	};
}