#include "Context.h"
#include "Texture.h"
#include "RenderTexture.h"
#include "Exception.h"
#include "Shader.h"
#include "Buffer.h"
#include "Mesh.h"

#include <GL/glew.h>

namespace rend
{

std::sr1::shared_ptr<Context> Context::initialize()
{
  std::sr1::shared_ptr<Context> rtn = std::sr1::make_shared<Context>();

  if(glewInit() != GLEW_OK)
  {
    throw Exception("Failed to initialize glew");
  }

  rtn->self = rtn;

  return rtn;
}

std::sr1::shared_ptr<Shader> Context::createShader()
{
  GLuint id = 0;
  id = glCreateProgram();

  if(id == 0)
  {
    throw Exception("Failed to create shader program");
  }

  pollForError();

  std::sr1::shared_ptr<Shader> rtn = std::sr1::make_shared<Shader>();
  rtn->context = self.lock();
  rtn->id = id;

  return rtn;
}

std::sr1::shared_ptr<Texture> Context::createTexture()
{
  GLuint id = 0;
  glGenTextures(1, &id);
  pollForError();

  std::sr1::shared_ptr<Texture> rtn = std::sr1::make_shared<Texture>();
  rtn->context = self.lock();
  rtn->id = id;

  rtn->setSize(256, 256);

  return rtn;
}

std::sr1::shared_ptr<RenderTexture> Context::createRenderTexture()
{
  GLuint id = 0;
  glGenTextures(1, &id);
  pollForError();

  GLuint fboId = 0;
  glGenFramebuffers(1, &fboId);
  pollForError();

  GLuint rboId = 0;
  glGenRenderbuffers(1, &rboId);
  pollForError();

  std::sr1::shared_ptr<RenderTexture> rtn = std::sr1::make_shared<RenderTexture>();

  rtn->context = self.lock();
  rtn->id = id;
  rtn->fboId = fboId;
  rtn->rboId = rboId;

  rtn->setSize(256, 256);

  return rtn;
}

std::sr1::shared_ptr<Buffer> Context::createBuffer()
{
  GLuint id = 0;
  glGenBuffers(1, &id);
  pollForError();

  std::sr1::shared_ptr<Buffer> rtn = std::sr1::make_shared<Buffer>();
  rtn->context = self.lock();
  rtn->id = id;

  return rtn;
}

std::sr1::shared_ptr<Mesh> Context::createMesh()
{
  std::sr1::shared_ptr<Mesh> rtn = std::sr1::make_shared<Mesh>();
  rtn->context = self.lock();

  return rtn;
}

}
