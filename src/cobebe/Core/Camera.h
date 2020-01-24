#include <memory>
#include <string>
#include <glm/glm.hpp>
#include <glwrap/glwrap.h>

namespace cobebe
{
	class Core;
	class Texture;
	class Shader;
	class Lighting;

	/**
	* \brief Represents a cameras position and perspective
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
		/**
		* \brief Draws to cameras RenderTexture
		*/
		void draw(std::shared_ptr<glwrap::ShaderProgram> _shaderInternal);

		/**
		* \brief Draw from GBuffer to RenderTexture
		*/
		void drawLighting(std::shared_ptr<Shader> _shader);

		/**
		* \brief Sets RenderTexture to uniform in passed in shader
		*/
		void setRtUniform(std::string _uniform, std::shared_ptr<glwrap::ShaderProgram> _shaderInternal);
		/**
		* \brief Sets GBuffer variables to appropriate uniforms in passed in shader
		*/
		void setGbUniform(std::shared_ptr<glwrap::ShaderProgram> _shaderInternal);

	private:
		friend class Core;

		bool m_isOn; ///< Checks if the Camera is on
		std::shared_ptr<glwrap::RenderTexture> m_texture; ///< Camera draws to internal RenderTexture
		std::shared_ptr<glwrap::GBuffer> m_gBuffer; ///< Defers lighting to later
		std::shared_ptr<Lighting> m_lighting; ///< Holds all variables regarding Lighting

		glm::mat4 m_projection; ///< The projection matrix for passing to shader
	};
}