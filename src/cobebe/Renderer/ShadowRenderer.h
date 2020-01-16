#include <cobebe/Renderer/Renderer.h>

namespace cobebe
{
	/**
	* \brief Displays an Entity to the screen via loaded assets with shadows
	*/
	class ShadowRenderer : public Renderer
	{
	public:

	private:
		void onPreDisplay();
		void onDisplay();

	};
}