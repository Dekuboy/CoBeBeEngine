#include <glwrap/glwrap.h>
#include <list>

namespace cobebe
{
	class Environment;
	class Core;
	class Texture;
	class Shader;
	class Entity;

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
		/**
		* \brief Draws texture to screen using perspective
		*/
		void drawTextureInWorld(std::shared_ptr<Texture> _image,
			glm::vec3 _position, glm::vec3 _size);

		/**
		* \brief Add button to total
		*/
		void addButton(std::shared_ptr<Entity> _button);

		/**
		* \brief Remove button from total
		*/
		void removeButton(std::shared_ptr<Entity> _button);

		/**
		* \brief Check for button from the mouse position and activate if necessary
		*/
		void queryButton();

		/**
		* \brief Change highlighted button to input
		*/
		void switchButton(std::shared_ptr<Entity> _button);

		/**
		* \brief Change highlighted button by list order
		*/
		void scrollButton(bool _toNext);

		/**
		* \brief Get the button currently highlighted
		*/
		std::shared_ptr<Entity> getHighlighted();

	private:
		friend class Core;

		glm::mat4 m_projection; ///< Orthographic matrix for drawing to screen
		int m_currentWidth; ///< Current matrix width to scale to screen
		int m_currentHeight; ///< Current matrix height to scale to screen
		std::shared_ptr<Shader> m_staticShader; ///< Minimal Shader draws without a view matrix

		std::list<std::weak_ptr<Entity> > m_buttonList; ///< List of buttons in scene
		std::weak_ptr<Entity> m_currentButton; ///< Current button highlighted
		std::weak_ptr<Entity> m_clickedButton; ///< Current button clicked

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