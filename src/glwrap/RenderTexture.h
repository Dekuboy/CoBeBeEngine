#ifndef RENDTEXTURE_H
#define RENDTEXTURE_H
#include "Texture.h"

namespace glwrap
{
	class RenderTexture : public Texture
	{
		friend class DepthBuffer;
		friend class Context;
		GLuint m_fbo;

	public:
		RenderTexture(int width, int height);
		RenderTexture(int width, int height, bool _base);

		GLuint getFbId();
		virtual void clear();

	};
}

#endif