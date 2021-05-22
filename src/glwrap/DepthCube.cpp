#include <glwrap/DepthCube.h>

namespace glwrap
{
	DepthCube::DepthCube(int width, int height) : RenderTexture(width, height, false)
	{
		glGenFramebuffers(1, &m_fbo);

		glGenTextures(1, &m_id);
		glBindTexture(GL_TEXTURE_CUBE_MAP, m_id);
		for (int i = 0; i < 6; ++i)
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_DEPTH_COMPONENT,
				width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);

		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

#if defined(__EMSCRIPTEN__)
#else
		glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
		glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, m_id, 0);
		glDrawBuffer(GL_NONE);
		glReadBuffer(GL_NONE);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
#endif

		glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	}

#if defined(__EMSCRIPTEN__)
	void DepthCube::bindFrameBuffer(int _face)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,
			GL_TEXTURE_CUBE_MAP_POSITIVE_X + _face, m_id, 0);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
#endif

	void DepthCube::clear()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
#if defined(__EMSCRIPTEN__)
		bindFrameBuffer(0);
		glClear(GL_DEPTH_BUFFER_BIT);
#else
		glClear(GL_DEPTH_BUFFER_BIT);
#endif
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
}