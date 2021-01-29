#include <glwrap/RenderTexture.h>

namespace glwrap
{
	class GBuffer : public RenderTexture
	{
	public:
		GBuffer(int _width, int _height);
		GBuffer(int _width, int _height, int _multisamples);

		GLuint getNId();
		GLuint getAsId();

	private:
		GLuint m_nId;
		GLuint m_asId;

	};
}