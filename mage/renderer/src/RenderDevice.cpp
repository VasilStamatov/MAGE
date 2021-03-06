#include "renderer/RenderDevice.h"

#include "exceptions/RuntimeError.h"
#include "logger/LogDispatch.h"
#include "renderer/GLCommon.h"

#include <GLEW/glew.h>

namespace mage
{
namespace graphics
{

// ------------------------------------------------------------------------------

namespace
{

// ------------------------------------------------------------------------------

std::uint32_t GetGLBlendFunction(RendererBlendFunction _function)
{
  switch (_function)
  {
    case RendererBlendFunction::Zero:
      return GL_ZERO;
    case RendererBlendFunction::One:
      return GL_ONE;
    case RendererBlendFunction::SourceAlpha:
      return GL_SRC_ALPHA;
    case RendererBlendFunction::DestinationAlpha:
      return GL_DST_ALPHA;
    case RendererBlendFunction::OneMinusSourceAlpha:
      return GL_ONE_MINUS_SRC_ALPHA;
  }
  return 0;
}

// ------------------------------------------------------------------------------

std::uint32_t GetGLBlendEquation(RendererBlendEquation _equation)
{
  switch (_equation)
  {
    case RendererBlendEquation::Add:
      return GL_ZERO;
    case RendererBlendEquation::Subtract:
      return GL_ONE;
  }
  return 0;
}

// ------------------------------------------------------------------------------

std::uint32_t GetGLDepthFunc(DepthFunc _func)
{
  switch (_func)
  {
    case DepthFunc::Never:
      return GL_NEVER;
    case DepthFunc::Less:
      return GL_LESS;
    case DepthFunc::Equal:
      return GL_EQUAL;
    case DepthFunc::LessOrEqual:
      return GL_LEQUAL;
    case DepthFunc::Greater:
      return GL_GREATER;
    case DepthFunc::NotEqual:
      return GL_NOTEQUAL;
    case DepthFunc::GreaterOrEqual:
      return GL_GEQUAL;
    case DepthFunc::Always:
      return GL_ALWAYS;
  }
  return 0;
}

// ------------------------------------------------------------------------------

} // namespace

// ------------------------------------------------------------------------------

RenderDevice::RenderDevice() {}

// ------------------------------------------------------------------------------

void RenderDevice::Initialize()
{
  glewExperimental = true; // Needed in core profile

  if (glewInit() != GLEW_OK)
  {
    throw RUNTIME_ERROR("Could not initialize GLEW");
  }

  GLCall(auto version = glGetString(GL_VERSION));
  GLCall(auto vendor = glGetString(GL_VENDOR));
  GLCall(auto renderer = glGetString(GL_RENDERER));

  std::stringstream initInfo;
  initInfo
      << "----------------------------------\n Initialized OpenGL:\n\tVersion: "
      << version << "\n\tVendor: " << vendor << "\n\tRenderer: " << renderer
      << "\n----------------------------------\n";

  LOG_INFO("RenderDevice", initInfo.str());

  SetDepthTesting(true);
  SetBlend(true);
  SetBlendFunction(RendererBlendFunction::SourceAlpha,
                   RendererBlendFunction::OneMinusSourceAlpha);

  GLCall(glClearColor(0.0f, 0.0f, 0.0f, 0.0f));
  GLCall(glEnable(GL_CULL_FACE));
  GLCall(glFrontFace(GL_CCW));
  GLCall(glCullFace(GL_BACK));
}

// ------------------------------------------------------------------------------

void RenderDevice::RenderDevice::Shutdown() {}

// ------------------------------------------------------------------------------

void RenderDevice::ClearBuffer(RendererBufferType _buffer)
{
  std::uint32_t buffers = 0;

  switch (_buffer)
  {
    case RendererBufferType::Color:
      buffers |= GL_COLOR_BUFFER_BIT;
      break;
    case RendererBufferType::Depth:
      buffers |= GL_DEPTH_BUFFER_BIT;
      break;
    case RendererBufferType::Stencil:
      buffers |= GL_STENCIL_BUFFER_BIT;
      break;
    case RendererBufferType::Color_Depth:
      buffers |= GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT;
      break;
    case RendererBufferType::Color_Depth_Stencil:
      buffers |=
          GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT;
      break;
    case RendererBufferType::Depth_Stencil:
      buffers |= GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT;
      break;
  }

  GLCall(glClear(buffers));
}

// ------------------------------------------------------------------------------

void RenderDevice::SetDepthTesting(bool _enabled)
{
  if (_enabled)
  {
    GLCall(glEnable(GL_DEPTH_TEST));
  }
  else
  {
    GLCall(glDisable(GL_DEPTH_TEST));
  }
}

// ------------------------------------------------------------------------------

void RenderDevice::SetDepthFunc(DepthFunc _func)
{
  GLCall(glDepthFunc(GetGLDepthFunc(_func)));
}

// ------------------------------------------------------------------------------

void RenderDevice::SetBlend(bool _enabled)
{
  if (_enabled)
  {
    GLCall(glEnable(GL_BLEND));
  }
  else
  {
    GLCall(glDisable(GL_BLEND));
  }
}

// ------------------------------------------------------------------------------

void RenderDevice::SetCulling(bool _enabled)
{
  if (_enabled)
  {
    GLCall(glEnable(GL_CULL_FACE));
  }
  else
  {
    GLCall(glDisable(GL_CULL_FACE));
  }
}

// ------------------------------------------------------------------------------

void RenderDevice::SetViewport(std::uint32_t _x, std::uint32_t _y,
                               std::uint32_t _width, std::uint32_t _height)
{
  GLCall(glViewport(_x, _y, _width, _height));
}

// ------------------------------------------------------------------------------

void RenderDevice::SetBlendFunction(RendererBlendFunction _source,
                                    RendererBlendFunction _destination)
{
  GLCall(glBlendFunc(GetGLBlendFunction(_source),
                     GetGLBlendFunction(_destination)));
}

// ------------------------------------------------------------------------------

void RenderDevice::SetBlendEquation(RendererBlendEquation _blendEquation)
{
  GLCall(glBlendEquation(GetGLBlendEquation(_blendEquation)));
}

// ------------------------------------------------------------------------------

} // namespace graphics
} // namespace mage