#include <cobebe/Core/Component.h>
#include <string>

namespace cobebe
{
	class Transform;
	class Texture;
	class Canvas;

	class ImageGUI : public Component
	{
	public:
		void setTexture(std::string _path);

	private:
		std::weak_ptr<Transform> m_transform;
		std::shared_ptr<Texture> m_texture;

		std::shared_ptr<Canvas> m_canvas;

		void onInit();
		void onGUI();

	};
}