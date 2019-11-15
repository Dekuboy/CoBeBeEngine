#include "Exception.h"

#include <GL/glew.h>

#include <iostream>

namespace rend
{

Exception::Exception(const std::string& message)
{
  this->message = message;
}

Exception::~Exception() throw() { }

const char* Exception::what() const throw()
{
  return message.c_str();
}

void pollForError()
{
  //while(true)
  {
    GLenum err = glGetError();

    if(err == GL_NO_ERROR)
    {
      //break;
      return;
    }

    throw Exception("OpenGL emitted an error");
    //throw Exception((char*)gluErrorString(err));
    //std::cout << "Warning: " << (char*)gluErrorString(err) << std::endl;
  }
}

}
