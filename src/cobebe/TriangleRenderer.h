#include "Component.h"
#include <GL/glew.h>
#include <SDL2/SDL.h>

class TriangleRenderer : public Component
{
public:
	~TriangleRenderer();
	void onInit();

private:
	GLuint m_programId;
	GLuint m_vaoId;
	SDL_Window *window;

	void onDisplay();
};