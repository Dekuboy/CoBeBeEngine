#include "Shader.h"
#include "Context.h"
#include "Exception.h"
#include "Buffer.h"
#include "Texture.h"
#include "RenderTexture.h"
#include "TextureAdapter.h"
#include "Mesh.h"

#include <sr1/vector>

#include <array>

namespace rend
{

struct VariableInfo
{
  std::string name;
  std::string typeName;
  std::sr1::zero_initialized<GLint> loc;
  std::sr1::zero_initialized<int> type;
  std::sr1::zero_initialized<bool> attrib;

  std::sr1::zero_initialized<float> floatVal;
  mat4 mat4Val;
  vec2 vec2Val;
  vec3 vec3Val;
  vec4 vec4Val;
  std::sr1::shared_ptr<Buffer> bufferVal;
  std::sr1::shared_ptr<TextureAdapter> textureVal;

  static std::string convertType(GLenum type);
};

std::string VariableInfo::convertType(GLenum type)
{
  if(type == GL_FLOAT) return "GL_FLOAT";
  else if(type == GL_FLOAT_VEC2) return "GL_FLOAT_VEC2";
  else if(type == GL_FLOAT_VEC3) return "GL_FLOAT_VEC3";
  else if(type == GL_FLOAT_VEC4) return "GL_FLOAT_VEC4";
  else if(type == GL_FLOAT_MAT4) return "GL_FLOAT_MAT4";
  else if(type == GL_SAMPLER_2D) return "GL_SAMPLER_2D";
  else if(type == GL_FLOAT) return "GL_FLOAT";
  else throw Exception(std::string("Invalid type"));
}

Shader::~Shader()
{
  glDeleteProgram(id);
  pollForError();
}

GLuint Shader::getId()
{
  return id;
}

void Shader::render(const std::sr1::shared_ptr<RenderTexture>& target)
{
  std::array<GLint, 4> viewport = {0};
  glGetIntegerv(GL_VIEWPORT, &viewport.at(0));
  pollForError();

  glBindFramebuffer(GL_FRAMEBUFFER, target->getId());
  pollForError();

  glViewport(0, 0, target->getWidth(), target->getHeight());
  pollForError();

  render();

  glBindFramebuffer(GL_FRAMEBUFFER, 0);
  pollForError();

  glViewport(viewport.at(0), viewport.at(1), viewport.at(2), viewport.at(3));

  //render();
}

void Shader::render()
{
  glEnable(GL_DEPTH_TEST); pollForError();
  glEnable(GL_CULL_FACE); pollForError();
  glEnable(GL_BLEND); pollForError();
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); pollForError();

  glUseProgram(id); pollForError();

  int activeTexture = 0;
  int vertices = -1;

  for(std::sr1::vector<std::sr1::shared_ptr<VariableInfo> >::iterator it = cache.begin();
    it != cache.end(); it++)
  {
    if((*it)->attrib == false)
    {
      if((*it)->type == GL_FLOAT_MAT4)
      {
        glUniformMatrix4fv((*it)->loc, 1, false, glm::value_ptr((*it)->mat4Val)); pollForError();
      }
      else if((*it)->type == GL_FLOAT_VEC2)
      {
        glUniform2fv((*it)->loc, 1, glm::value_ptr((*it)->vec2Val)); pollForError();
      }
      else if((*it)->type == GL_FLOAT_VEC3)
      {
        glUniform3fv((*it)->loc, 1, glm::value_ptr((*it)->vec3Val)); pollForError();
      }
      else if((*it)->type == GL_FLOAT_VEC4)
      {
        glUniform4fv((*it)->loc, 1, glm::value_ptr((*it)->vec4Val)); pollForError();
      }
      else if((*it)->type == GL_SAMPLER_2D)
      {
        glActiveTexture(GL_TEXTURE0 + activeTexture); pollForError();
        glBindTexture(GL_TEXTURE_2D, (*it)->textureVal->getTexId()); pollForError();
        glUniform1i((*it)->loc, activeTexture); pollForError();
        activeTexture++;
      }
      else if((*it)->type == GL_FLOAT)
      {
        glUniform1f((*it)->loc, (*it)->floatVal); pollForError();
      }
    }
    else
    {
      int size = 0;
      if((*it)->type == GL_FLOAT) size = 1;
      else if((*it)->type == GL_FLOAT_VEC2) size = 2;
      else if((*it)->type == GL_FLOAT_VEC3) size = 3;
      else if((*it)->type == GL_FLOAT_VEC4) size = 4;
      else throw Exception("Invalid buffer type");

      glBindBuffer(GL_ARRAY_BUFFER, (*it)->bufferVal->getId()); pollForError();
      glVertexAttribPointer((*it)->loc, size, GL_FLOAT, GL_FALSE, 0, 0); pollForError();
      glEnableVertexAttribArray((*it)->loc); pollForError();
      glBindBuffer(GL_ARRAY_BUFFER, 0); pollForError();

      size = (*it)->bufferVal->getSize();

      if(vertices == -1)
      {
        vertices = size;
      }

      if(vertices != size)
      {
        throw Exception("The specified attribute streams are of different sizes");
      }
    }
  }

  if(vertices == -1)
  {
    throw Exception("No vertices were submitted for drawing");
  }

  glDrawArrays(GL_TRIANGLES, 0, vertices); pollForError();

  glUseProgram(0); pollForError();

  glDisable(GL_BLEND); pollForError();
  glDisable(GL_CULL_FACE); pollForError();
  glDisable(GL_DEPTH_TEST); pollForError();
}

void Shader::setSampler(const std::string& variable, const std::sr1::shared_ptr<TextureAdapter>& value)
{
  std::sr1::shared_ptr<VariableInfo> vi = getVariableInfo(variable, GL_SAMPLER_2D, false);
  vi->textureVal = value;
}

void Shader::setUniform(const std::string& variable, float value)
{
  std::sr1::shared_ptr<VariableInfo> vi = getVariableInfo(variable, GL_FLOAT, false);
  vi->floatVal = value;
}

void Shader::setUniform(const std::string& variable, mat4 value)
{
  std::sr1::shared_ptr<VariableInfo> vi = getVariableInfo(variable, GL_FLOAT_MAT4, false);
  vi->mat4Val = value;
}

void Shader::setUniform(const std::string& variable, vec2 value)
{
  std::sr1::shared_ptr<VariableInfo> vi = getVariableInfo(variable, GL_FLOAT_VEC2, false);
  vi->vec2Val = value;
}

void Shader::setUniform(const std::string& variable, vec3 value)
{
  std::sr1::shared_ptr<VariableInfo> vi = getVariableInfo(variable, GL_FLOAT_VEC3, false);
  vi->vec3Val = value;
}

void Shader::setUniform(const std::string& variable, vec4 value)
{
  std::sr1::shared_ptr<VariableInfo> vi = getVariableInfo(variable, GL_FLOAT_VEC4, false);
  vi->vec4Val = value;
}

void Shader::setAttribute(const std::string& variable, const std::sr1::shared_ptr<Buffer>& value)
{
  std::sr1::shared_ptr<VariableInfo> vi = getVariableInfo(variable, value->type, true);
  vi->bufferVal = value;
}

void Shader::setMesh(const std::sr1::shared_ptr<Mesh>& value)
{
  for(std::sr1::vector<std::sr1::shared_ptr<BufferData> >::iterator it =
    value->buffers.begin(); it != value->buffers.end(); it++)
  {
    setAttribute((*it)->name, (*it)->buffer);
  }

  for(std::sr1::vector<std::sr1::shared_ptr<TextureData> >::iterator it =
    value->textures.begin(); it != value->textures.end(); it++)
  {
    setSampler((*it)->name, (*it)->texture);
  }
}

std::sr1::shared_ptr<VariableInfo> Shader::getVariableInfo(const std::string& name, GLenum type, bool attrib)
{
  for(std::sr1::vector<std::sr1::shared_ptr<VariableInfo> >::iterator it = cache.begin();
    it != cache.end(); it++)
  {
    if((*it)->name == name)
    {
      if ((*it)->type != type || (*it)->attrib != attrib)
      {
        throw Exception("Variable [" + name + "] requested as wrong type [" +
          VariableInfo::convertType((*it)->type));
      }

      return *it;
    }
  }

  std::sr1::shared_ptr<VariableInfo> rtn = std::sr1::make_shared<VariableInfo>();
  rtn->name = name;
  rtn->attrib = attrib;
  rtn->type = type;
  rtn->typeName = VariableInfo::convertType(type);

  GLsizei unusedA = 0;
  GLint unusedB = 0;
  GLenum rtnType = 0;

  if(attrib == false)
  {
    rtn->loc = glGetUniformLocation(id, name.c_str());
    pollForError();

    if(rtn->loc == -1)
    {
      throw Exception("The specified uniform [" + name + "] was not found in the shader");
    }

    glGetActiveUniform(id, rtn->loc, 0, &unusedA, &unusedB, &rtnType, NULL);
    pollForError();

    if(rtnType != type)
    {
      throw Exception("The requested uniform [" + name + "] had the wrong type [" +
        VariableInfo::convertType(rtn->type) + "]");
    }
  }
  else
  {
    rtn->loc = glGetAttribLocation(id, name.c_str());
    pollForError();

    if(rtn->loc == -1)
    {
      throw Exception("The specified attribute [" + name + "] was not found in the shader");
    }

    glGetActiveAttrib(id, rtn->loc, 0, &unusedA, &unusedB, &rtnType, NULL);
    pollForError();

    if(rtnType != type)
    {
      throw Exception("The requested attribute had the wrong type");
    }
  }

  cache.push_back(rtn);

  return rtn;
}

void Shader::setSource(const std::string& source)
{
  parse(source);
}

void Shader::parse(const std::string& source)
{
  GLuint vertId = 0;
  GLuint fragId = 0;
  int success = 0;
  const GLchar* src = NULL;

  cache.clear();

  std::string vertSrc = "";
  vertSrc += "#version 120\n";
  vertSrc += "#define VERTEX\n";
  vertSrc += source;
  src = vertSrc.c_str();

  vertId = glCreateShader(GL_VERTEX_SHADER);
  pollForError();

  glShaderSource(vertId, 1, &src, NULL);
  pollForError();

  glCompileShader(vertId);
  pollForError();

  glGetShaderiv(vertId, GL_COMPILE_STATUS, &success);
  pollForError();

  if(!success)
  {
    int length = 0;
    glGetShaderiv(vertId, GL_INFO_LOG_LENGTH, &length);
    pollForError();

    std::sr1::vector<char> infoLog(length);
    glGetShaderInfoLog(vertId, length, NULL, &infoLog.at(0));
    pollForError();

    glDeleteShader(vertId);
    pollForError();

    std::string msg = &infoLog.at(0);
    throw Exception(msg);
  }

  std::string fragSrc = "";
  fragSrc += "#version 120\n";
  fragSrc += "#define FRAGMENT\n";
  fragSrc += source;
  src = fragSrc.c_str();

  fragId = glCreateShader(GL_FRAGMENT_SHADER);
  pollForError();

  glShaderSource(fragId, 1, &src, NULL);
  pollForError();

  glCompileShader(fragId);
  pollForError();

  glGetShaderiv(fragId, GL_COMPILE_STATUS, &success);
  pollForError();

  if(!success)
  {
    int length = 0;
    glGetShaderiv(fragId, GL_INFO_LOG_LENGTH, &length);
    pollForError();

    std::sr1::vector<char> infoLog(length);
    glGetShaderInfoLog(fragId, length, NULL, &infoLog.at(0));
    pollForError();

    glDeleteShader(fragId);
    pollForError();

    std::string msg = &infoLog.at(0);
    throw Exception(msg);
  }

  glAttachShader(id, vertId);
  pollForError();

  glAttachShader(id, fragId);
  pollForError();

  glLinkProgram(id);
  pollForError();

  glGetProgramiv(id, GL_LINK_STATUS, &success);
  pollForError();

  if(!success)
  {
    int length = 0;
    glGetProgramiv(id, GL_INFO_LOG_LENGTH, &length);
    pollForError();

    std::sr1::vector<char> infoLog(length);
    glGetProgramInfoLog(id, length, NULL, &infoLog.at(0));
    pollForError();

    std::string msg = &infoLog.at(0);
    throw Exception(msg);
  }

  glDetachShader(id, vertId);
  pollForError();

  glDetachShader(id, fragId);
  pollForError();

  glDeleteShader(vertId);
  pollForError();

  glDeleteShader(fragId);
  pollForError();
}

}
