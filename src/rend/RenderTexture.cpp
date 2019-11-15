#include "RenderTexture.h"
#include "Context.h"
#include "Exception.h"

namespace rend
{

RenderTexture::~RenderTexture()
{
  GLuint delId = id;
  glDeleteTextures(1, &delId);
  pollForError();

  delId = fboId;
  glDeleteFramebuffers(1, &delId); 
  pollForError();

  delId = rboId;
  glDeleteRenderbuffers(1, &delId); 
  pollForError();
}

GLuint RenderTexture::getTexId()
{
  return id;
}

void RenderTexture::clear()
{
  glBindFramebuffer(GL_FRAMEBUFFER, getId());
  pollForError();

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  pollForError();

  glBindFramebuffer(GL_FRAMEBUFFER, 0);
  pollForError();
}

GLuint RenderTexture::getId()
{
  if(dirty)
  {
    glBindFramebuffer(GL_FRAMEBUFFER, fboId);
    pollForError();

    glBindTexture(GL_TEXTURE_2D, id); pollForError();
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, size.x, size.y, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    pollForError();
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    pollForError();
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    pollForError();
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, id, 0);
    pollForError();
    glBindTexture(GL_TEXTURE_2D, 0);
    pollForError();

    glBindRenderbuffer(GL_RENDERBUFFER, rboId);
    pollForError();
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, size.x, size.y);
    pollForError();
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rboId);
    pollForError();
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
    pollForError();

    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
      throw Exception("FrameBuffer is not complete");
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    pollForError();
    dirty = false;
  }

  return fboId;
}

ivec2 RenderTexture::getSize() const
{
  return size;
}

int RenderTexture::getWidth() const
{
  return size.x;
}

int RenderTexture::getHeight() const
{
  return size.y;
}

void RenderTexture::setSize(unsigned int width, unsigned int height)
{
  dirty = true;
  size = ivec2(width, height);
}

}
