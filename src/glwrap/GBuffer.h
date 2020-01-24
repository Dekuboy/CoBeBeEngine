#include "Rendertexture.h"

namespace glwrap
{
	class GBuffer : public RenderTexture
	{
	public:
		GBuffer(int _width, int _height);

		GLuint getNId();
		GLuint getAsId();

	private:
		GLuint m_nId;
		GLuint m_asId;

	};
}