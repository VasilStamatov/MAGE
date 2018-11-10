#include "renderer/Renderer.h"

#include "exceptions/RuntimeError.h"
#include "renderer/GLCommon.h"

#include <iostream>

#include <glew.h>

namespace mage
{
namespace graphics
{

// ------------------------------------------------------------------------------

Renderer::Renderer() {}

// ------------------------------------------------------------------------------

void Renderer::Initialize()
{
  glewExperimental = true; // Needed in core profile

  if (glewInit() != GLEW_OK)
  {
    throw RUNTIME_ERROR("Could not initialize GLEW");
  }

  GLCall(auto version = glGetString(GL_VERSION));
  std::cout << "Initialized OpenGL v" << version << std::endl;
  ;
}

// ------------------------------------------------------------------------------

void Renderer::Shutdown() {}

// ------------------------------------------------------------------------------

} // namespace graphics
} // namespace mage