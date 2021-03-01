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
	class Transform;

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

		glm::vec3 m_position; //!< Position in world space
		glm::mat3 m_rotation; //!< Rotation in world space

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
		* \brief Get the near plane
		*/
		float getNearPlane();
		/**
		* \brief Get the far plane
		*/
		float getFarPlane();
		/**
		* \brief Get the aspect ratio
		*/
		float getAspect();

		/**
		* \brief Use current View and Projection matrices to generate ViewingFrustum
		*/
		void setViewingFrustum();

		/**
		* \brief Draws to cameras RenderTexture
		*/
		void draw(std::shared_ptr<glwrap::ShaderProgram> _shaderInternal, std::shared_ptr<Transform> _transform, std::shared_ptr<glwrap::VertexArray> _meshInternal);
		/**
		* \brief Draws to cameras RenderTexture
		*/
		void draw(std::shared_ptr<glwrap::ShaderProgram> _shaderInternal);
		/**
		* \brief Draws to cameras RenderTexture
		*/
		void draw(std::shared_ptr<glwrap::ShaderProgram> _shaderInternal, std::shared_ptr<Transform> _transform, std::shared_ptr<glwrap::ObjMtlModel> _meshInternal, std::string _textureUniform);

		/**
		* \brief Draws to cameras RenderTexture (Culls parts individually)
		*/
		void cullAndDraw(std::shared_ptr<glwrap::ShaderProgram> _shaderInternal, std::shared_ptr<Transform> _transform, std::shared_ptr<glwrap::VertexArray> _meshInternal);
		/**
		* \brief Draws to cameras RenderTexture (Culls parts individually)
		*/
		void cullAndDraw(std::shared_ptr<glwrap::ShaderProgram> _shaderInternal, std::shared_ptr<Transform> _transform, std::shared_ptr<glwrap::ObjMtlModel> _meshInternal, std::string _textureUniform);



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

		bool m_isOn; //!< Checks if the Camera is on
		bool m_isDrawReady; //!< Checks if the variables for drawing have been set each frame
		std::shared_ptr<glwrap::RenderTexture> m_texture; //!< Camera draws to internal RenderTexture
		std::shared_ptr<glwrap::GBuffer> m_gBuffer; //!< Defers lighting to later
		std::shared_ptr<Lighting> m_lighting; //!< Holds all variables regarding Lighting
		std::shared_ptr<glwrap::ViewingFrustum> m_frustum; //!< Holds frustum planes for culling

		glm::mat4 m_projection; //!< The projection matrix for passing to shader
		float m_near; //!< The near plane used in perspective
		float m_far; //!< The far plane used in perspective
		float m_angle; //!< The angle used in perspective
		float m_aspect; //!< The aspect ratio used in perspective

	};
}