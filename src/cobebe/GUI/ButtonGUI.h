#include <cobebe/Core/Component.h>
#include <string>

namespace cobebe
{
	class Transform;
	class Texture;
	class Canvas;

	/**
	* \brief GUI element for interaction on click
	* -virtual activate function
	*/
	class ButtonGUI : public Component
	{
	public:
		/**
		* \brief Sets texture to draw when static
		*/
		void setTextureStatic(std::string _path);
		/**
		* \brief Sets texture to draw when static
		*/
		void setTextureStatic(std::shared_ptr<Texture> _texture);

		/**
		* \brief Sets texture to draw when highlighted
		*/
		void setTextureHighlighted(std::string _path);
		/**
		* \brief Sets texture to draw when highlighted
		*/
		void setTextureHighlighted(std::shared_ptr<Texture> _texture);

		/**
		* \brief Sets texture to draw when pressed
		*/
		void SetTexturePressed(std::string _path);
		/**
		* \brief Sets texture to draw when pressed
		*/
		void setTexturePressed(std::shared_ptr<Texture> _texture);

		/**
		* \brief Sets the GUI in Screen or World space
		*/
		void setWorldGUI(bool _switch);

		/**
		* \brief Sets the button ready to click on canvas
		*/
		void setInCanvas(bool _switch);

	private:
		friend class Canvas;

		std::weak_ptr<Transform> m_transform; //!< Pointer to position and scale for drawing and raycasting
		std::shared_ptr<Texture> m_textureStatic; //!< Loaded texture to apply when static
		std::shared_ptr<Texture> m_textureHighlighted; //!< Loaded texture to apply when highlighted
		std::shared_ptr<Texture> m_texturePressed; //!< Loaded texture to apply when pressed

		std::shared_ptr<Canvas> m_canvas; //!< Pointer to canvas for drawing to screen
		bool m_isHighlighted; //!< Checks if mouse is ready to click button
		bool m_isClicked; //!< Checks if button is currently clicked

		bool m_isWorldGUI; //!< Checks if GUI is in screen or world space

		/**
		* \brief Checks for ray collision
		*/
		virtual float checkHighlight();

		/**
		* \brief Activates on button click
		*/
		virtual void activate();

		virtual void onInit();
		virtual void onTick();
		virtual void onGUI();

	};
}