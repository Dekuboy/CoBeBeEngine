#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <cobebe/Resources/Asset.h>
#include <cobebe/Resources/Resources.h>
#include <cobebe/NonCopyable.h>

namespace cobebe
{
	class Renderer;
	class Canvas;
	class Lighting;
	class Camera;

	/**
	* \brief Stores a VertexArray to set in Renderer
	*/
	class Mesh : public Asset
	{
	public:
		/**
		* \brief Retrieves all VertexArray faces
		*/
		std::vector<std::shared_ptr<glwrap::Face>> getFaces();

	private:
		friend class Renderer;

		std::shared_ptr<glwrap::VertexArray> m_internal; ///< Pointer to OpenGL VertexArray

		void onLoad(const std::string& _path);

	};


	/**
	* \brief Stores a Texture to set for drawing in Shader
	*/
	class Texture : public Asset
	{
	public:

	private:
		friend class Renderer;
		friend class Canvas;

		std::shared_ptr<glwrap::Texture> m_internal; ///< Pointer to OpenGL Texture

		void onLoad(const std::string& _path);

	};


	/**
	* \brief Stores a Shader to set in Renderer
	*/
	class Shader : public Asset
	{
	public:
		/**
		* \brief Get the internal glwrap ShaderProgram
		*/
		const std::shared_ptr<glwrap::ShaderProgram> getInternal();

		/**
		* \brief Set emissive in Lighting shader
		*/
		void setEmissive(glm::vec3 _emissive);
		/**
		* \brief Set ambient in Lighting shader
		*/
		void setAmbient(glm::vec3 _ambient);
		/**
		* \brief Set light position in Lighting shader
		*/
		void setLightPos(glm::vec3 _lightPos);
		/**
		* \brief Set global light direction in Lighting Shader
		*/
		void setLightDir(glm::vec3 _lightDir);
		/**
		* \brief Set global light colour in Lighting Shader
		*/
		void setLightCol(glm::vec3 _lightCol);
		/**
		* \brief Set lightspace for depth shading in Lighting Shader
		*/
		void setLightSpace(glm::mat4 _lightSpace);

		/**
		* \brief Set lightspaces for depth shading in Lighting Shader
		*/
		void setLightSpace(std::vector<glm::mat4> _lightSpace);

		/**
		* \brief Set point light count Lighting Shader
		*/
		void setPointLightCount(int _count);
		/**
		* \brief Set depthcubes to use in Lighting Shader
		*/
		void setDepthCubes(std::vector<std::shared_ptr<glwrap::DepthCube>> _depthCubes);
		/**
		* \brief Set light positions for depth shading in Lighting Shader
		*/
		void setPointLightPositions(std::vector<glm::vec3> _pointLightPositions);
		/**
		* \brief Set light colours for depth shading in Lighting Shader
		*/
		void setPointLightColours(std::vector<glm::vec3> _pointColours);
		/**
		* \brief Set light far planes for depth shading in Lighting Shader
		*/
		void setFarPlanes(std::vector<float> _farPlanes);

		/**
		* \brief Check if global lighting values have been set for shader
		*/
		bool getUniformCheck();
		/**
		* \brief Set if global lighting values have been set for shader to input value
		*/
		void setUniformCheck(bool _switch);

		/**
		* \brief Set current Camera view to input
		*/
		void setCam(std::shared_ptr<Camera> _camera);

		/**
		* \brief Sets checks for uniform variables to false on tick
		*/
		void resetChecks();

	private:
		friend class Renderer;
		friend class Canvas;
		friend class Lighting;

		std::shared_ptr<glwrap::ShaderProgram> m_internal; ///< Pointer to OpenGL ShaderProgram
		bool m_uniformCheck; ///< Checks if lighting uniforms need to be set
		bool m_shadowCheck; ///< Checks if shadow uniforms need to be set

		std::shared_ptr<Camera> m_camSet; ///< Stores current camera view active

		void onLoad(const std::string& _path);

	};
}