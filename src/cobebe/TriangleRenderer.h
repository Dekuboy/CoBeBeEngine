#include <cobebe/Core/Component.h>
#include <GL/glew.h>
#include <SDL2/SDL.h>

class TriangleRenderer : public cobebe::Component
{
public:
	void onInit();

private:
	GLuint m_programId;
	GLuint m_vaoId;

	void onDisplay();
};