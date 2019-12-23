#ifndef RENDTEXTURE_H
#define RENDTEXTURE_H
#include <glwrap/Texture.h>

namespace glwrap
{
	class RenderTexture : public Texture
	{
	public:
		RenderTexture(int _width, int _height);
		RenderTexture(int _width, int _height, bool _base);

		GLuint getFbId();
		virtual void clear();

	private:
		friend class DepthBuffer;
		friend class Context;
		GLuint m_fbo;

	};
}

#endif