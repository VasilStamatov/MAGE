#include "renderer/GLCommon.h"

#include "logger/LogDispatch.h"

#include <GLEW/glew.h>

namespace mage
{
namespace graphics
{

// ------------------------------------------------------------------------------

std::uint32_t GLCheckError() { return glGetError(); }

// ------------------------------------------------------------------------------

bool GLLogCall(const char* _function, const char* _file, int _line)
{
  std::uint32_t error = GLCheckError();
  if (error != GL_NO_ERROR)
  {
    std::string errorString("[GL ERROR] : " + std::to_string(error) + '\n' +
                            "\t File: " + _file + '\n' +
                            "\t Function: " + _function + '\n' +
                            "\t Line: " + std::to_string(_line) + '\n');

    LOG_FATAL("OpenGL", errorString);
    return false;
  }
  return true;
}

// ------------------------------------------------------------------------------

} // namespace graphics
} // namespace mage