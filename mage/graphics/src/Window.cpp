#include "graphics/Window.h"

// #define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

namespace mage
{
namespace graphics
{

Window::Frame::Frame(std::int32_t _left, std::int32_t _top, std::int32_t _right,
                     std::int32_t _bottom)
    : m_left(_left)
    , m_top(_top)
    , m_right(_right)
    , m_bottom(_bottom)
{
}

Window::ScreenPosition::ScreenPosition(std::int32_t _x, std::int32_t _y)
    : m_x(_x)
    , m_y(_y)
{
}

Window::ScreenSize::ScreenSize(std::int32_t _width, std::int32_t _height)
    : m_width(_width)
    , m_height(_height)
{
}

Window::Window(std::string _title, GLFWmonitor* _monitor, std::int32_t _width,
               std::int32_t _height)
    : m_title(std::move(_title))
    , m_position(0, 0)
    , m_size(_width, _height)
    , m_handle(nullptr)
{
  m_handle = glfwCreateWindow(m_size.m_width, m_size.m_height, m_title.c_str(),
                              _monitor, nullptr);

  glfwSetWindowUserPointer(m_handle, this);
  glfwGetWindowPos(m_handle, &m_position.m_x, &m_position.m_y);

  // glfwSetFramebufferSizeCallback(m_handle, &FramebufferSizeCallback);
  // glfwSetWindowCloseCallback(m_handle, &WindowCloseCallback);
  // glfwSetWindowFocusCallback(m_handle, &WindowFocusCallback);
  // glfwSetWindowIconifyCallback(m_handle, &WindowIconifyCallback);
  // glfwSetWindowPosCallback(m_handle, &WindowPositionCallback);
  // glfwSetWindowRefreshCallback(m_handle, &WindowRefreshCallback);
  // glfwSetWindowSizeCallback(m_handle, &WindowResizeCallback);

  MakeCurrent();
}

Window::Window(std::string _title, GLFWmonitor* _monitor)
    : m_title(std::move(_title))
    , m_position(0, 0)
    , m_size(0, 0)
    , m_handle(nullptr)
{
  auto* videMode = glfwGetVideoMode(_monitor);

  m_size.m_width = videMode->width;
  m_size.m_height = videMode->height;

  m_handle = glfwCreateWindow(m_size.m_width, m_size.m_height, m_title.c_str(),
                              _monitor, nullptr);

  glfwSetWindowUserPointer(m_handle, this);
  glfwGetWindowPos(m_handle, &m_position.m_x, &m_position.m_y);

  // glfwSetFramebufferSizeCallback(m_handle, &FramebufferSizeCallback);
  // glfwSetWindowCloseCallback(m_handle, &WindowCloseCallback);
  // glfwSetWindowFocusCallback(m_handle, &WindowFocusCallback);
  // glfwSetWindowIconifyCallback(m_handle, &WindowIconifyCallback);
  // glfwSetWindowPosCallback(m_handle, &WindowPositionCallback);
  // glfwSetWindowRefreshCallback(m_handle, &WindowRefreshCallback);
  // glfwSetWindowSizeCallback(m_handle, &WindowResizeCallback);

  MakeCurrent();
}
Window::Window(std::string _title, std::int32_t _width, std::int32_t _height)
    : m_title(std::move(_title))
    , m_position(0, 0)
    , m_size(_width, _height)
    , m_handle(nullptr)
{
  m_handle = glfwCreateWindow(m_size.m_width, m_size.m_height, m_title.c_str(),
                              nullptr, nullptr);

  glfwSetWindowUserPointer(m_handle, this);
  glfwGetWindowPos(m_handle, &m_position.m_x, &m_position.m_y);

  // glfwSetFramebufferSizeCallback(m_handle, &FramebufferSizeCallback);
  // glfwSetWindowCloseCallback(m_handle, &WindowCloseCallback);
  // glfwSetWindowFocusCallback(m_handle, &WindowFocusCallback);
  // glfwSetWindowIconifyCallback(m_handle, &WindowIconifyCallback);
  // glfwSetWindowPosCallback(m_handle, &WindowPositionCallback);
  // glfwSetWindowRefreshCallback(m_handle, &WindowRefreshCallback);
  // glfwSetWindowSizeCallback(m_handle, &WindowResizeCallback);

  MakeCurrent();
}
Window::~Window()
{
  if (m_handle)
  {
    glfwDestroyWindow(m_handle);
    m_handle = nullptr;
  }
}

Window::Window(Window&& _other)
    : m_title(std::move(_other.m_title))
    , m_position(std::move(_other.m_position))
    , m_size(std::move(_other.m_size))
    , m_handle(_other.m_handle)
{
  _other.m_handle = nullptr;

  if (m_handle)
  {
    glfwSetWindowUserPointer(m_handle, this);
  }

  MakeCurrent();
}
Window& Window::operator=(Window&& _rhs)
{
  if (m_handle)
  {
    glfwDestroyWindow(m_handle);
  }

  m_title = std::move(_rhs.m_title);
  m_position = std::move(_rhs.m_position);
  m_size = std::move(_rhs.m_size);
  m_handle = std::move(_rhs.m_handle);

  if (m_handle)
  {
    glfwSetWindowUserPointer(m_handle, this);
  }

  MakeCurrent();

  return *this;
}

void Window::MakeCurrent() { glfwMakeContextCurrent(m_handle); }
void Window::SwapBuffers() { glfwSwapBuffers(m_handle); }

Window::ScreenPosition Window::GetPosition() const { return m_position; }
Window::ScreenSize Window::GetSize() const { return m_size; }
Window::ScreenSize Window::GetFramebufferSize() const
{
  ScreenSize framebufferSize(0, 0);
  glfwGetFramebufferSize(m_handle, &framebufferSize.m_width,
                         &framebufferSize.m_height);
  return framebufferSize;
}
Window::Frame Window::GetFrame() const
{
  Frame result(0, 0, 0, 0);

  glfwGetWindowFrameSize(m_handle, &result.m_left, &result.m_top,
                         &result.m_right, &result.m_bottom);

  return result;
}

} // namespace graphics
} // namespace mage