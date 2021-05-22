#include <glwrap/RenderTexture.h>

namespace glwrap
{
	RenderTexture::RenderTexture(int _width, int _height) : Texture(_width, _height, false)
	{
		m_multisamples = 0;
		glGenTextures(1, &m_id);
		glBindTexture(GL_TEXTURE_2D, m_id);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_size.x, m_size.y, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glBindTexture(GL_TEXTURE_2D, 0);

		glGenFramebuffers(1, &m_fbo);
		glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_id, 0);
#if defined(WIN32)
#else
		GLuint rbo = 0;
		glGenRenderbuffers(1, &rbo);
		glBindRenderbuffer(GL_RENDERBUFFER, rbo);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, m_size.x, m_size.y);
		glBindRenderbuffer(GL_RENDERBUFFER, 0);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);
#endif
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	RenderTexture::RenderTexture(int _width, int _height, int _multisamples) : Texture(_width, _height, false)
	{
#if defined(__EMSCRIPTEN__)
#else
		m_multisamples = _multisamples;
		glGenTextures(1, &m_id);
		glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, m_id);
		glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, _multisamples, GL_RGB, m_size.x, m_size.y, GL_TRUE);
		glTexParameteri(GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, 0);

		glGenFramebuffers(1, &m_fbo);
		glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D_MULTISAMPLE, m_id, 0);

		GLuint rbo = 0;
		glGenRenderbuffers(1, &rbo);
		glBindRenderbuffer(GL_RENDERBUFFER, rbo);
		glRenderbufferStorageMultisample(GL_RENDERBUFFER, _multisamples, GL_DEPTH24_STENCIL8, m_size.x, m_size.y);
		glBindRenderbuffer(GL_RENDERBUFFER, 0);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
#endif
	}

	RenderTexture::RenderTexture(int _width, int _height, bool _base) : Texture(_width, _height, false)
	{
		m_multisamples = 0;
	}

	GLuint RenderTexture::getFbId()
	{
		return m_fbo;
	}

	int RenderTexture::getSamples()
	{
		return m_multisamples;
	}

	void RenderTexture::clear()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
}
