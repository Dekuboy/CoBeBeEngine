#include <glwrap/glwrap.h>

namespace cobebe
{
	class Environment;
	class Core;
	class Texture;
	class Shader;

	/**
	* \brief Holds values to draw GUI to screen
	*/
	class Canvas
	{
	public:
		/**
		* \brief Draws and scales input texture to screen
		*/
		void drawTexture(std::shared_ptr<Texture> _image,
			glm::vec3 _position, glm::vec3 _size);

	private:
		friend class Core;

		glm::mat4 m_projection; ///< Orthographic matrix for drawing to screen
		int m_currentWidth; ///< Current matrix width to scale to screen
		int m_currentHeight; ///< Current matrix height to scale to screen
		std::shared_ptr<Shader> m_staticShader; ///< Minimal Shader draws without a view matrix

		std::weak_ptr<Environment> m_environment; ///< Pointer to environment to get screen size
		std::weak_ptr<Core> m_core; /// Pointer to games Core

		/**
		* \brief Sets the orthographic matrix based on current values
		*/
		void setProjection();

		/**
		* \brief Initialises variables after Core pointer set
		*/
		void onInit();

	};
}