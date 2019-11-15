#ifndef REND_TEXTUREADAPTER_H
#define REND_TEXTUREADAPTER_H

#include "mathutil.h"

#include <GL/glew.h>

namespace rend
{

struct TextureAdapter
{
  virtual GLuint getTexId() = 0;
  virtual ivec2 getSize() const = 0;
};

}

#endif
