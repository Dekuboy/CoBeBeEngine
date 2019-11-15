#include "mathutil.h"

#include <GL/glew.h>

#include <sr1/vector>
#include <sr1/memory>
#include <sr1/zero_initialized>
#include <sr1/noncopyable>

namespace rend
{

struct Context;
struct Shader;

struct Buffer : public std::sr1::noncopyable
{
  ~Buffer();

  void add(float value);
  void add(vec2 value);
  void add(vec3 value);
  void add(vec4 value);

  GLuint getId();
  int getSize();

private:
  friend struct Context;
  friend struct Shader;

  std::sr1::shared_ptr<Context> context;
  std::sr1::vector<float> floatData;
  std::sr1::zero_initialized<int> type;
  std::sr1::zero_initialized<bool> dirty;
  std::sr1::zero_initialized<GLuint> id;

};

}
