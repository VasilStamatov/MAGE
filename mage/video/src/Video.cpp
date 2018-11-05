#include "video/Video.h"

#include "exceptions/RuntimeError.h"
#include "video/VideoHints.h"

#include <iostream>

#define GLFW_INCLUDE_VULKAN
#include <glfw3.h>

namespace mage
{
namespace video
{

namespace
{

// ------------------------------------------------------------------------------

std::string IntepretGLFWerrorcode(int _code)
{
  switch (_code)
  {
    case GLFW_NOT_INITIALIZED:
      return "GLFW has not been initialized";
    case GLFW_NO_CURRENT_CONTEXT:
      return "No context is current for this thread";
    case GLFW_INVALID_ENUM:
      return "One of the arguments to the function was an invalid enum value";
    case GLFW_INVALID_VALUE:
      return "One of the arguments to the function was an invalid value";
    case GLFW_OUT_OF_MEMORY:
      return "A memory allocation failed";
    case GLFW_API_UNAVAILABLE:
      return "GLFW could not find support for the requested client API on the "
             "system";
    case GLFW_VERSION_UNAVAILABLE:
      return "The requested OpenGL or OpenGL ES version is not available";
    case GLFW_PLATFORM_ERROR:
      return "A platform - specific error occurred that does not match any of "
             "the more specific categories";
    case GLFW_FORMAT_UNAVAILABLE:
      return "The requested format is not supported or available";
    default:
      return std::string("Unknown error code: ") + std::to_string(_code);
  }
}

// ------------------------------------------------------------------------------

void GLFWErrorCallback(int _error, const char* _description)
{
  std::cout << "GLFW error (" << IntepretGLFWerrorcode(_error)
            << "): " << _description << std::endl;
}

// ------------------------------------------------------------------------------

} // namespace

// ------------------------------------------------------------------------------

Video::Video()
    : m_window()
{
}

// ------------------------------------------------------------------------------

void Video::Initialize()
{
  const std::string title = "Application Window";
  const std::int32_t width = 500;
  const std::int32_t height = 500;
  const bool fullscreen = false;
  const bool borderless = false;

  glfwSetErrorCallback(&GLFWErrorCallback);

  if (!glfwInit())
  {
    throw RUNTIME_ERROR("Failed to initialize GLFW");
  }

  std::cout << "GLFW v" << glfwGetVersionString() << std::endl;

  VideoHints videoHints;
  videoHints.m_windowHints.m_resizable = false;
  videoHints.m_windowHints.m_visible = true;
  videoHints.m_windowHints.m_decorated = true;
  videoHints.m_windowHints.m_focused = true;
  videoHints.m_windowHints.m_autoIconify = true;
  videoHints.m_windowHints.m_floating = false;

  GLFWmonitor* monitor = glfwGetPrimaryMonitor();

  videoHints.FromVideoMode(glfwGetVideoMode(monitor));

  videoHints.m_framebufferHints.m_stereo = false;
  videoHints.m_framebufferHints.m_samples = 0;
  videoHints.m_framebufferHints.m_sRGBCapable = true;
  videoHints.m_framebufferHints.m_doubleBuffer = true;

  videoHints.m_contextHints.m_clientAPI = ContextHints::ClientAPI::None;
  videoHints.m_contextHints.m_contextVersionMajor = 4;
  videoHints.m_contextHints.m_contextVersionMinor = 0;

  videoHints.m_contextHints.m_openGLForwardCompatible = true;
  videoHints.m_contextHints.m_openGLProfile = ContextHints::OpenGLProfile::Core;

#ifndef NDEBUG
  videoHints.m_contextHints.m_openGLDebugContext = true;
#else
  videoHints.m_contextHints.m_openGLDebugContext = false;
#endif

  videoHints.m_contextHints.m_contextRobustness =
      ContextHints::ContextRobustness::NoRobustness;
  videoHints.m_contextHints.m_contextReleaseBehavior =
      ContextHints::ContextReleaseBehavior::Any;

  std::cout << videoHints << std::endl;

  videoHints.Apply();

  if (fullscreen)
  {
    if (borderless)
    {
      CreateBorderlessFullscreenWindow(std::move(title), monitor);
    }
    else
    {
      CreateFullscreenWindow(std::move(title), monitor, width, height);
    }
  }
  else
  {
    CreateWindowedWindow(std::move(title), width, height);
  }
}

// ------------------------------------------------------------------------------

void Video::Shutdown()
{
  m_window.reset();
  glfwTerminate();
}

// ------------------------------------------------------------------------------

void Video::SwapBuffers()
{
  glfwPollEvents();
  m_window->SwapBuffers();
}

// ------------------------------------------------------------------------------

bool Video::ShouldClose() const { return m_window->ShouldClose(); }

// ------------------------------------------------------------------------------

Window& Video::GetWindow() { return *m_window; }

// ------------------------------------------------------------------------------

void Video::CreateFullscreenWindow(std::string _title, GLFWmonitor* _monitor,
                                   std::int32_t _width, std::int32_t _height)
{
  m_window =
      std::make_unique<Window>(std::move(_title), _monitor, _width, _height);
}

// ------------------------------------------------------------------------------

void Video::CreateBorderlessFullscreenWindow(std::string _title,
                                             GLFWmonitor* _monitor)
{
  m_window = std::make_unique<Window>(std::move(_title), _monitor);
}

// ------------------------------------------------------------------------------

void Video::CreateWindowedWindow(std::string _title, std::int32_t _width,
                                 std::int32_t _height)
{
  m_window = std::make_unique<Window>(std::move(_title), _width, _height);
}

// ------------------------------------------------------------------------------

} // namespace video
} // namespace mage