#include "mathutil.h"
#include "TextureAdapter.h"

#include <GL/glew.h>

#include <sr1/memory>
#include <sr1/noncopyable>
#include <sr1/zero_initialized>
#include <sr1/vector>

namespace rend
{

struct Context;
struct Shader;

struct RenderTexture : public TextureAdapter, public std::sr1::noncopyable
{
  ~RenderTexture();

  void setSize(unsigned int width, unsigned int height);

  ivec2 getSize() const;
  int getWidth() const;
  int getHeight() const;

  GLuint getTexId();
  GLuint getId();
  void clear();

private:
  friend struct Context;
  friend struct Shader;

  std::sr1::shared_ptr<Context> context;
  std::sr1::zero_initialized<GLuint> fboId;
  std::sr1::zero_initialized<GLuint> rboId;
  std::sr1::zero_initialized<GLuint> id;
  ivec2 size;
  std::sr1::zero_initialized<bool> dirty;

};

}
