#include "renderer/GLCommon.h"

#include <iostream>
#include <sstream>

#include <glew.h>

namespace mage
{
namespace renderer
{

// ------------------------------------------------------------------------------

void GLClearError()
{
  while (glGetError() != GL_NO_ERROR)
  {
  }
}

// ------------------------------------------------------------------------------

bool GLLogCall(const char* _function, const char* _file, int _line)
{
  GLenum error = glGetError();
  if (error != GL_NO_ERROR)
  {
    std::stringstream errorString;
    errorString << "[GL ERROR] : " << error << "\n";
    errorString << "\t File: " << _file << "\n";
    errorString << "\t Function: " << _function << "\n";
    errorString << "\t Line: " << _line << "\n";
    std::cout << errorString.str();
    return false;
  }
  return true;
}

// ------------------------------------------------------------------------------

} // namespace renderer
} // namespace mage