#include "Buffer.h"
#include "Exception.h"
#include "Context.h"

namespace rend
{

Buffer::~Buffer()
{
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  GLuint delId = id;
  glDeleteBuffers(1, &delId);
  pollForError();
}

int Buffer::getSize()
{
  if(type == GL_FLOAT_VEC3) return floatData.size() / 3;
  else if(type == GL_FLOAT_VEC2) return floatData.size() / 2;
  else if(type == GL_FLOAT_VEC4) return floatData.size() / 4;
  else if(type == GL_FLOAT) return floatData.size() / 1;
  else throw Exception("TODO: Support other types of data");
}

void Buffer::add(float value)
{
  if(type != 0 && type != GL_FLOAT)
  {
    throw Exception("Attempt to mix types");
  }

  type = GL_FLOAT;
  floatData.push_back(value);
  dirty = true;
}

void Buffer::add(vec2 value)
{
  if(type != 0 && type != GL_FLOAT_VEC2)
  {
    throw Exception("Attempt to mix types");
  }

  type = GL_FLOAT_VEC2;
  floatData.push_back(value.x);
  floatData.push_back(value.y);
  dirty = true;
}

void Buffer::add(vec3 value)
{
  if(type != 0 && type != GL_FLOAT_VEC3)
  {
    throw Exception("Attempt to mix types");
  }

  type = GL_FLOAT_VEC3;
  floatData.push_back(value.x);
  floatData.push_back(value.y);
  floatData.push_back(value.z);
  dirty = true;
}

void Buffer::add(vec4 value)
{
  if(type != 0 && type != GL_FLOAT_VEC4)
  {
    throw Exception("Attempt to mix types");
  }

  type = GL_FLOAT_VEC4;
  floatData.push_back(value.x);
  floatData.push_back(value.y);
  floatData.push_back(value.z);
  floatData.push_back(value.w);
  dirty = true;
}

GLuint Buffer::getId()
{
  if(dirty)
  {
    glBindBuffer(GL_ARRAY_BUFFER, id);
    pollForError();

    if(type == GL_FLOAT || type == GL_FLOAT_VEC2 || type == GL_FLOAT_VEC3 || type == GL_FLOAT_VEC4)
    {
      glBufferData(GL_ARRAY_BUFFER, sizeof(floatData.at(0)) * floatData.size(),
        &floatData.at(0), GL_STATIC_DRAW);

      pollForError();
    }
    else
    {
      throw Exception("TODO: Support other types of data");
    }

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    pollForError();

    dirty = false;
  }

  return id;
}

}
