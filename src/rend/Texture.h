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

struct Texture : public TextureAdapter, public std::sr1::noncopyable
{
  ~Texture();

  void setSize(unsigned int width, unsigned int height);
  void setPixel(unsigned int x, unsigned int y, vec3 rgb);
  void setPixel(unsigned int x, unsigned int y, vec4 rgba);

  vec4 getPixel(unsigned int x, unsigned int y) const;
  ivec2 getSize() const;
  int getWidth() const;
  int getHeight() const;

  GLuint getId();
  GLuint getTexId();

private:
  friend struct Context;

  std::sr1::shared_ptr<Context> context;
  std::sr1::zero_initialized<GLuint> id;
  std::sr1::vector<vec4> data;
  ivec2 size;
  std::sr1::zero_initialized<bool> dirty;
  std::sr1::zero_initialized<int> bpp;

  //GLuint getId();

};

}
