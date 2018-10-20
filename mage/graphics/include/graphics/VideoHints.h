#pragma once

#include <cstdint>
#include <ostream>

struct GLFWvidmode;

namespace mage
{
namespace graphics
{

struct ContextHints
{
  enum class ClientAPI : std::uint8_t
  {
    OpenGL,
    OpenGL_ES
  };

  friend std::ostream& operator<<(std::ostream& _stream, ClientAPI _clientAPI);

  enum class ContextRobustness : std::uint8_t
  {
    NoRobustness,
    NoResetNotification,
    LoseContextOnReset
  };

  friend std::ostream& operator<<(std::ostream& _stream,
                                  ContextRobustness _contextRobustness);

  enum class ContextReleaseBehavior : std::uint8_t
  {
    Any,   // the default behavior of the context creation API will be used
    Flush, // the pipeline will be flushed whenever the context is released from
           // being the current one
    None   // the pipeline will not be flushed on release
  };

  friend std::ostream&
  operator<<(std::ostream& _stream,
             ContextReleaseBehavior _contextReleaseBehavior);

  enum class OpenGLProfile : std::uint8_t
  {
    Any,
    Compatibility,
    Core
  };

  friend std::ostream& operator<<(std::ostream& _stream,
                                  OpenGLProfile _openGLProfile);

  // specifies which client API to create the context for. This is a hard
  // constraint
  ClientAPI m_clientAPI = ClientAPI::OpenGL;

  // specify the client API version that the created context must be compatible
  // with. The exact behavior of these hints depend on the requested client API
  std::int32_t m_contextVersionMajor = 1;
  std::int32_t m_contextVersionMinor = 0;

  // specifies which OpenGL profile to create the context for. When requesting
  // an openGL profile below v3.2 you must use ANY_PROFILE. If OpenGL ES is
  // requested, this hint is ignored
  OpenGLProfile m_openGLProfile = OpenGLProfile::Any;

  // specifies the robustness strategy to be used by the context
  ContextRobustness m_contextRobustness = ContextRobustness::NoRobustness;

  // specifies the release behavior to be used by the context
  ContextReleaseBehavior m_contextReleaseBehavior = ContextReleaseBehavior::Any;

  // specifies whether the OpenGL context should be forward-compatible, i.e. one
  // where all functionality deprecated in the requested version of OpenGL is
  // removed. This may only be used if the requested OpenGL version is 3.0 or
  // above. If OpenGL ES is requested, this hint is ignored
  bool m_openGLForwardCompatible = false;

  // specifies whether to create a debug OpenGL context, which may have
  // additional error and performance issue reporting functionality. If OpenGL
  // ES is requested, this hint is ignored
  bool m_openGLDebugContext = false;
};

struct WindowHints
{
  // specifies whether the windowed mode window will be resizable by the user.
  bool m_resizable = true;

  // specifies whether the windowed mode window will be initially visible. This
  // hint is ignored for full screen windows
  bool m_visible = true;

  // specifies whether the windowed mode window will have window decorations
  // such as a border, a close widget, etc. An undecorated window may still
  // allow the user to generate close events on some platforms. This hint is
  // ignored for full screen windows
  bool m_decorated = true;

  // specifies whether the windowed mode window will be given input focus when
  // created. This hint is ignored for full screen and initially hidden windows
  bool m_focused = true;

  // specifies whether the full screen window will automatically iconify and
  // restore the previous video mode on input focus loss.This hint is ignored
  // for windowed mode windows
  bool m_autoIconify = true;

  // specifies whether the windowed mode window will be floating above other
  // regular windows, also called topmost or always-on-top. This is intended
  // primarily for debugging purposes and cannot be used to implement proper
  // full screen windows. This hint is ignored for full screen windows
  bool m_floating = false;
};

struct FramebufferHints
{
  // specify the desired bit depths of the various components of the default
  // framebuffer; use -1 if there's no preference
  std::int32_t m_redBits = 8;
  std::int32_t m_greenBits = 8;
  std::int32_t m_blueBits = 8;
  std::int32_t m_alphaBits = 8;
  std::int32_t m_depthBits = 24;
  std::int32_t m_stencilBits = 8;

  // specifies the desired number of samples to use for multisampling. 0
  // disables multisampling. -1 means the application has no preference
  std::int32_t m_samples = 0;

  // specifies whether to use stereoscopic rendering.This is a hard constraint
  bool m_stereo = false;

  // specifies whether the framebuffer should be sRGB capable
  bool m_sRGBCapable = false;

  // specifies whether the framebuffer should be double buffered.You nearly
  // always want to use double buffering.This is a hard constraint
  bool m_doubleBuffer = true;
};

struct MonitorHints
{
  // specifies the desired refresh rate for full screen windows. If set to -1,
  // the highest available refresh rate will be used. This hint is ignored for
  // windowed mode windows
  std::int32_t m_refreshRate = 0;
};

class VideoHints
{
public:
  VideoHints();

  // to GLFW defaults (notably openGL 1.0!)
  void ResetToDefaults();

  // acquires the current bitsettings and refresh rate for a given monitor (for
  // borderless fullscreen windows)
  void FromVideoMode(const GLFWvidmode* _vidmode);

  // applies the current settings for the next window to be created
  void Apply();

  friend std::ostream& operator<<(std::ostream& _stream,
                                  const VideoHints& _hints);

  // the following values reflect the defaults from GLFW
  FramebufferHints m_framebufferHints;
  ContextHints m_contextHints;
  WindowHints m_windowHints;
  MonitorHints m_monitorHints;
};

} // namespace graphics
} // namespace mage