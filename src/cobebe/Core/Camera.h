#include <memory>
#include <string>
#include <glm/glm.hpp>
#include <glwrap/glwrap.h>

namespace cobebe
{
	class Core;
	class Texture;
	class Renderer;

	/**
	* Represents a cameras position and perspective
	* -holds a RenderTexture to draw to
	*/
	class Camera
	{
	public:
		/**
		* \brief Sets initial position and rotation
		*/
		Camera();

		glm::vec3 m_position; ///< Position in world space
		glm::mat3 m_rotation; ///< Rotation in world space

		/**
		* \brief Creates and returns a view matrix
		*/
		glm::mat4 getView();

		/** 
		* \brief Returns cameras perspective/orthographic matrix
		*/
		glm::mat4 getProjection();
		/**
		* \brief Sets projection matrix to perspective
		*/
		void setPerspective(float _angle, float _width, float _height, float _near, float _far);

		/**
		* \brief Draws to cameras RenderTexture
		*/
		void draw(std::shared_ptr<glwrap::ShaderProgram> _shaderInternal, std::shared_ptr<glwrap::VertexArray> _meshInternal);

	private:
		friend class Core;

		bool m_isOn; ///< Checks if the Camera is on
		std::shared_ptr<glwrap::RenderTexture> m_texture; ///< Camera draws to internal RenderTexture

		glm::mat4 m_projection; ///< The projection matrix for passing to shader
	};
}