#include <cobebe/Core/Component.h>
#include <string>

namespace cobebe
{
	class Transform;
	class Texture;
	class Canvas;

	/**
	* \brief GUI element to draw to screen 
	*/
	class ImageGUI : public Component
	{
	public:
		/**
		* \brief Sets texture to draw as GUI
		*/
		void setTexture(std::string _path);
		/**
		* \brief Sets texture to draw as GUI
		*/
		void setTexture(std::shared_ptr<Texture> _texture);

	private:
		std::weak_ptr<Transform> m_transform; ///< Pointer to position and scale for drawing
		std::shared_ptr<Texture> m_texture; ///< Loaded texture to apply

		std::shared_ptr<Canvas> m_canvas; ///< Pointer to canvas for drawing to screen

		void onInit();
		void onGUI();

	};
}