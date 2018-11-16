#include "video/Window.h"

#include "messaging/MessageBus.h"

#include <GLFW/glfw3.h>

namespace mage
{
namespace video
{

// ------------------------------------------------------------------------------

// ----- Window Callbacks -----
namespace
{

void FramebufferSizeCallback(GLFWwindow* _handle, int _width, int _height)
{
  auto* appMessageBus =
      static_cast<messaging::MessageBus*>(glfwGetWindowUserPointer(_handle));

  OnWindowFramebufferResized framebufferResizedEvent{_width, _height};
  appMessageBus->Broadcast(&framebufferResizedEvent);
}

} // namespace

// ------------------------------------------------------------------------------

Window::Window(messaging::MessageBus& _appMessageBus, std::string _title,
               GLFWmonitor* _monitor, std::int32_t _width, std::int32_t _height)
    : m_handle(nullptr)
{
  m_handle =
      glfwCreateWindow(_width, _height, _title.c_str(), _monitor, nullptr);

  glfwSetWindowUserPointer(m_handle, &_appMessageBus);

  glfwSetFramebufferSizeCallback(m_handle, &FramebufferSizeCallback);

  MakeCurrent();

  OnWindowCreated windowCreatedEvent{*this};
  _appMessageBus.Broadcast(&windowCreatedEvent);
}

// ------------------------------------------------------------------------------

Window::Window(messaging::MessageBus& _appMessageBus, std::string _title,
               GLFWmonitor* _monitor)
    : m_handle(nullptr)
{
  auto* videoMode = glfwGetVideoMode(_monitor);

  m_handle = glfwCreateWindow(videoMode->width, videoMode->height,
                              _title.c_str(), _monitor, nullptr);

  glfwSetWindowUserPointer(m_handle, &_appMessageBus);

  glfwSetFramebufferSizeCallback(m_handle, &FramebufferSizeCallback);

  MakeCurrent();

  OnWindowCreated windowCreatedEvent{*this};
  _appMessageBus.Broadcast(&windowCreatedEvent);
}

// ------------------------------------------------------------------------------

Window::Window(messaging::MessageBus& _appMessageBus, std::string _title,
               std::int32_t _width, std::int32_t _height)
    : m_handle(nullptr)
{
  m_handle =
      glfwCreateWindow(_width, _height, _title.c_str(), nullptr, nullptr);

  glfwSetWindowUserPointer(m_handle, &_appMessageBus);

  glfwSetFramebufferSizeCallback(m_handle, &FramebufferSizeCallback);

  MakeCurrent();

  OnWindowCreated windowCreatedEvent{*this};
  _appMessageBus.Broadcast(&windowCreatedEvent);
}

// ------------------------------------------------------------------------------

Window::~Window()
{
  if (m_handle)
  {
    glfwDestroyWindow(m_handle);
    m_handle = nullptr;
  }
}

// ------------------------------------------------------------------------------

void Window::MakeCurrent() { glfwMakeContextCurrent(m_handle); }

// ------------------------------------------------------------------------------

void Window::SwapBuffers() { glfwSwapBuffers(m_handle); }

// ------------------------------------------------------------------------------

bool Window::ShouldClose() const { return glfwWindowShouldClose(m_handle); }

// ------------------------------------------------------------------------------

GLFWwindow* Window::GetHandle() const { return m_handle; }

// ------------------------------------------------------------------------------

} // namespace video
} // namespace mage