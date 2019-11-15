#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <rend/rend.h>
#include "Component.h"

namespace cobebe
{
	class Renderer : public Component
	{
	public:
		Renderer();
		~Renderer();
		void onInit();
	private:
		void onDisplay();

		GLuint m_programId;
		GLuint m_vaoId;
		SDL_Window *m_window;
		std::shared_ptr<rend::Context> m_context;
		std::shared_ptr<rend::Shader> m_shader;
	};
}