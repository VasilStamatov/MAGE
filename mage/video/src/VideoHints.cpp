#include "video/VideoHints.h"

#include <assert.h>
#include <string>

#include <GLFW/glfw3.h>

namespace mage
{
namespace video
{

namespace
{

// ------------------------------------------------------------------------------

std::string HintValueToString(std::int32_t _value)
{
  if (_value == GLFW_DONT_CARE)
  {
    return "Don't care";
  }
  else
  {
    return std::to_string(_value);
  }
}

// ------------------------------------------------------------------------------

void CheckHintNumber(std::int32_t _value)
{
  assert((_value >= GLFW_DONT_CARE) && (_value <= INT_MAX));
}

// ------------------------------------------------------------------------------

} // namespace

// ------------------------------------------------------------------------------

VideoHints::VideoHints()
    : m_framebufferHints()
    , m_contextHints()
    , m_windowHints()
    , m_monitorHints()
{
}

// ------------------------------------------------------------------------------

void VideoHints::ResetToDefaults()
{
  *this = VideoHints();
  glfwDefaultWindowHints();
}

// ------------------------------------------------------------------------------

void VideoHints::FromVideoMode(const GLFWvidmode* _vidmode)
{
  m_framebufferHints.m_redBits = _vidmode->redBits;
  m_framebufferHints.m_greenBits = _vidmode->greenBits;
  m_framebufferHints.m_blueBits = _vidmode->blueBits;
  m_monitorHints.m_refreshRate = _vidmode->refreshRate;
}

// ------------------------------------------------------------------------------

void VideoHints::Apply() const
{
  ApplyMonitorHints();
  ApplyWindowHints();
  ApplyFramebufferHints();
  ApplyContextHints();
}

// ------------------------------------------------------------------------------

void VideoHints::ApplyMonitorHints() const
{
  CheckHintNumber(m_monitorHints.m_refreshRate);
  glfwWindowHint(GLFW_REFRESH_RATE, m_monitorHints.m_refreshRate);
}

// ------------------------------------------------------------------------------

void VideoHints::ApplyWindowHints() const
{
  glfwWindowHint(GLFW_RESIZABLE, m_windowHints.m_resizable ? true : false);
  glfwWindowHint(GLFW_VISIBLE, m_windowHints.m_visible ? true : false);
  glfwWindowHint(GLFW_DECORATED, m_windowHints.m_decorated ? true : false);
  glfwWindowHint(GLFW_FOCUSED, m_windowHints.m_focused ? true : false);
  glfwWindowHint(GLFW_AUTO_ICONIFY, m_windowHints.m_autoIconify ? true : false);
  glfwWindowHint(GLFW_FLOATING, m_windowHints.m_floating ? true : false);
}

// ------------------------------------------------------------------------------

void VideoHints::ApplyFramebufferHints() const
{
  CheckHintNumber(m_framebufferHints.m_redBits);
  CheckHintNumber(m_framebufferHints.m_greenBits);
  CheckHintNumber(m_framebufferHints.m_blueBits);
  CheckHintNumber(m_framebufferHints.m_alphaBits);
  CheckHintNumber(m_framebufferHints.m_depthBits);
  CheckHintNumber(m_framebufferHints.m_stencilBits);
  CheckHintNumber(m_framebufferHints.m_samples);

  glfwWindowHint(GLFW_RED_BITS, m_framebufferHints.m_redBits);
  glfwWindowHint(GLFW_GREEN_BITS, m_framebufferHints.m_greenBits);
  glfwWindowHint(GLFW_BLUE_BITS, m_framebufferHints.m_blueBits);
  glfwWindowHint(GLFW_ALPHA_BITS, m_framebufferHints.m_alphaBits);
  glfwWindowHint(GLFW_DEPTH_BITS, m_framebufferHints.m_depthBits);
  glfwWindowHint(GLFW_STENCIL_BITS, m_framebufferHints.m_stencilBits);

  glfwWindowHint(GLFW_SAMPLES, m_framebufferHints.m_samples);
  glfwWindowHint(GLFW_STEREO, m_framebufferHints.m_stereo ? true : false);
  glfwWindowHint(GLFW_SRGB_CAPABLE,
                 m_framebufferHints.m_sRGBCapable ? true : false);
  glfwWindowHint(GLFW_DOUBLEBUFFER,
                 m_framebufferHints.m_doubleBuffer ? true : false);
}

// ------------------------------------------------------------------------------

void VideoHints::ApplyContextHints() const
{
  std::int32_t api = GLFW_OPENGL_API;
  std::int32_t profile = GLFW_OPENGL_ANY_PROFILE;
  std::int32_t robustness = GLFW_NO_ROBUSTNESS;
  std::int32_t releaseBehavior = GLFW_ANY_RELEASE_BEHAVIOR;

  switch (m_contextHints.m_clientAPI)
  {
    case ContextHints::ClientAPI::None:
    {
      api = GLFW_NO_API;
      break;
    }
    case ContextHints::ClientAPI::OpenGL:
    {
      api = GLFW_OPENGL_API;
      break;
    }
    case ContextHints::ClientAPI::OpenGL_ES:
    {
      api = GLFW_OPENGL_ES_API;
      break;
    }
  }

  switch (m_contextHints.m_openGLProfile)
  {
    case ContextHints::OpenGLProfile::Any:
    {
      profile = GLFW_OPENGL_ANY_PROFILE;
      break;
    }
    case ContextHints::OpenGLProfile::Compatibility:
    {
      profile = GLFW_OPENGL_COMPAT_PROFILE;
      break;
    }
    case ContextHints::OpenGLProfile::Core:
    {
      profile = GLFW_OPENGL_CORE_PROFILE;
      break;
    }
  }

  switch (m_contextHints.m_contextRobustness)
  {
    case ContextHints::ContextRobustness::LoseContextOnReset:
    {
      robustness = GLFW_LOSE_CONTEXT_ON_RESET;
      break;
    }
    case ContextHints::ContextRobustness::NoResetNotification:
    {
      robustness = GLFW_NO_RESET_NOTIFICATION;
      break;
    }
    case ContextHints::ContextRobustness::NoRobustness:
    {
      robustness = GLFW_NO_ROBUSTNESS;
      break;
    }
  }

  switch (m_contextHints.m_contextReleaseBehavior)
  {
    case ContextHints::ContextReleaseBehavior::Any:
    {
      releaseBehavior = GLFW_ANY_RELEASE_BEHAVIOR;
      break;
    }
    case ContextHints::ContextReleaseBehavior::Flush:
    {
      releaseBehavior = GLFW_RELEASE_BEHAVIOR_FLUSH;
      break;
    }
    case ContextHints::ContextReleaseBehavior::None:
    {
      releaseBehavior = GLFW_RELEASE_BEHAVIOR_NONE;
      break;
    }
  }

  glfwWindowHint(GLFW_CLIENT_API, api);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,
                 m_contextHints.m_contextVersionMajor);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,
                 m_contextHints.m_contextVersionMinor);

  glfwWindowHint(GLFW_CONTEXT_ROBUSTNESS, robustness);
  glfwWindowHint(GLFW_CONTEXT_RELEASE_BEHAVIOR, releaseBehavior);

  if (m_contextHints.m_clientAPI != ContextHints::ClientAPI::None)
  {
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT,
                   m_contextHints.m_openGLForwardCompatible ? true : false);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT,
                   m_contextHints.m_openGLDebugContext ? true : false);
    glfwWindowHint(GLFW_OPENGL_PROFILE, profile);
  }
}

// ------------------------------------------------------------------------------

std::ostream& operator<<(std::ostream& _stream,
                         ContextHints::ClientAPI _ClientAPI)
{
  switch (_ClientAPI)
  {
    case ContextHints::ClientAPI::None:
    {
      _stream << "None";
      break;
    }
    case ContextHints::ClientAPI::OpenGL:
    {
      _stream << "OpenGL";
      break;
    }
    case ContextHints::ClientAPI::OpenGL_ES:
    {
      _stream << "OpenGL ES";
      break;
    }
    default:
    {
      _stream << "Unknown - " << static_cast<std::uint8_t>(_ClientAPI);
    }
  }
  return _stream;
}

// ------------------------------------------------------------------------------

std::ostream& operator<<(std::ostream& _stream,
                         ContextHints::ContextRobustness _ContextRobustness)
{
  switch (_ContextRobustness)
  {
    case ContextHints::ContextRobustness::LoseContextOnReset:
    {
      _stream << "Lose Context On Reset";
      break;
    }
    case ContextHints::ContextRobustness::NoResetNotification:
    {
      _stream << "No Reset Notification";
      break;
    }
    case ContextHints::ContextRobustness::NoRobustness:
    {
      _stream << "No Robustness";
      break;
    }
    default:
    {
      _stream << "Unknown - " << static_cast<std::uint8_t>(_ContextRobustness);
    }
  }
  return _stream;
}

// ------------------------------------------------------------------------------

std::ostream&
operator<<(std::ostream& _stream,
           ContextHints::ContextReleaseBehavior _ContextReleaseBehavior)
{
  switch (_ContextReleaseBehavior)
  {
    case ContextHints::ContextReleaseBehavior::Any:
    {
      _stream << "Any";
      break;
    }
    case ContextHints::ContextReleaseBehavior::Flush:
    {
      _stream << "Flush";
      break;
    }
    case ContextHints::ContextReleaseBehavior::None:
    {
      _stream << "None";
      break;
    }
    default:
    {
      _stream << "Unknown - "
              << static_cast<std::uint8_t>(_ContextReleaseBehavior);
    }
  }
  return _stream;
}

// ------------------------------------------------------------------------------

std::ostream& operator<<(std::ostream& _stream,
                         ContextHints::OpenGLProfile _OpenGLProfile)
{
  switch (_OpenGLProfile)
  {
    case ContextHints::OpenGLProfile::Any:
    {
      _stream << "Any";
      break;
    }
    case ContextHints::OpenGLProfile::Compatibility:
    {
      _stream << "Compatibility";
      break;
    }
    case ContextHints::OpenGLProfile::Core:
    {
      _stream << "Core";
      break;
    }
    default:
    {
      _stream << "Unknown - " << static_cast<std::uint8_t>(_OpenGLProfile);
    }
  }
  return _stream;
}

// ------------------------------------------------------------------------------

std::ostream& operator<<(std::ostream& _stream, const VideoHints& _hints)
{
  _stream
      << std::boolalpha << "\tWindow hints:"
      << "\n\tResizable: " << _hints.m_windowHints.m_resizable
      << "\n\tVisible: " << _hints.m_windowHints.m_resizable
      << "\n\tDecorated: " << _hints.m_windowHints.m_decorated
      << "\n\tFocused: " << _hints.m_windowHints.m_focused
      << "\n\tAutoIconify: " << _hints.m_windowHints.m_autoIconify
      << "\n\tFloating: " << _hints.m_windowHints.m_floating

      << "\n\tBits:"
      << " | r: " << HintValueToString(_hints.m_framebufferHints.m_redBits)
      << " | g: " << HintValueToString(_hints.m_framebufferHints.m_greenBits)
      << " | b: " << HintValueToString(_hints.m_framebufferHints.m_blueBits)
      << " | a: " << HintValueToString(_hints.m_framebufferHints.m_alphaBits)
      << " | depth: "
      << HintValueToString(_hints.m_framebufferHints.m_depthBits)
      << " | stencil: "
      << HintValueToString(_hints.m_framebufferHints.m_stencilBits)

      << "\n\tStereo: " << _hints.m_framebufferHints.m_stereo << "\n\tSamples: "
      << HintValueToString(_hints.m_framebufferHints.m_samples)
      << "\n\tsRGB: " << _hints.m_framebufferHints.m_sRGBCapable
      << "\n\tDoubleBuffer: " << _hints.m_framebufferHints.m_doubleBuffer
      << "\n\tRefreshRate: "
      << HintValueToString(_hints.m_monitorHints.m_refreshRate)
      << "\n\tClientAPI: " << _hints.m_contextHints.m_clientAPI << " v"
      << _hints.m_contextHints.m_contextVersionMajor << "."
      << _hints.m_contextHints.m_contextVersionMinor
      << "\n\tForwardCompatible: "
      << _hints.m_contextHints.m_openGLForwardCompatible
      << "\n\tContextRobustness: " << _hints.m_contextHints.m_contextRobustness
      << "\n\tContextReleaseBehavior: "
      << _hints.m_contextHints.m_contextReleaseBehavior;

  return _stream;
}

// ------------------------------------------------------------------------------

} // namespace video
} // namespace mage