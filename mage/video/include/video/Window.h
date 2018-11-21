#pragma once

#include <cstdint>
#include <string>

struct GLFWmonitor;
struct GLFWwindow;

namespace mage
{

namespace messaging
{
class MessageBus;
}

namespace video
{

// ------------------------------------------------------------------------------

class Window
{
public:
  Window(messaging::MessageBus& _appMessageBus, std::string _title,
         GLFWmonitor* _monitor, std::int32_t _width, std::int32_t _height);

  Window(messaging::MessageBus& _appMessageBus, std::string _title,
         GLFWmonitor* _monitor);

  Window(messaging::MessageBus& _appMessageBus, std::string _title,
         std::int32_t _width, std::int32_t _height);

  // ------------------------------------------------------------------------------

  ~Window();

  // ------------------------------------------------------------------------------

  Window(const Window&) = delete;
  Window& operator=(const Window&) = delete;

  // ------------------------------------------------------------------------------

  Window(Window&& _other) = delete;
  Window& operator=(Window&& _rhs) = delete;

  // ------------------------------------------------------------------------------

  void MakeCurrent();
  void SwapBuffers();

  // ------------------------------------------------------------------------------

  bool ShouldClose() const;

  // ------------------------------------------------------------------------------

  GLFWwindow* GetHandle() const;

  // ------------------------------------------------------------------------------

  std::pair<int, int> GetFramebufferSize();

  // ------------------------------------------------------------------------------

private:
  GLFWwindow* m_handle;
};

// ------------------------------------------------------------------------------

// ----- Events ------

struct OnWindowFramebufferResized
{
  std::int32_t m_width;
  std::int32_t m_height;
};

struct OnWindowCreated
{
  Window& m_window;
};

// ------------------------------------------------------------------------------

} // namespace video
} // namespace mage