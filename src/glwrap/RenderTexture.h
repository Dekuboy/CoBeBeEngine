#ifndef _GLWRAP_RENDTEXTURE
#define _GLWRAP_RENDTEXTURE
#include <glwrap/Texture.h>

namespace glwrap
{
	class RenderTexture : public Texture
	{
	public:
		RenderTexture(int _width, int _height);
		RenderTexture(int _width, int _height, int _multisamples);
		RenderTexture(int _width, int _height, bool _base);

		GLuint getFbId();
		int getSamples();
		virtual void clear();

	protected:
		GLuint m_fbo;
		int m_multisamples;

	};
}

#endif