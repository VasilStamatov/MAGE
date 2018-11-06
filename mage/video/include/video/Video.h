#pragma once

#include "Window.h"
#include "messaging/MessageBus.h"

namespace mage
{
namespace video
{

// ------------------------------------------------------------------------------

struct OnWindowCreated
{
  OnWindowCreated(Window& _window)
      : m_window(_window)
  {
  }
  Window& m_window;
};

// ------------------------------------------------------------------------------

class Video
{
public:
  Video(messaging::MessageBus& _messageBus);

  // ------------------------------------------------------------------------------

  void Initialize();

  // ------------------------------------------------------------------------------

  void Shutdown();

  // ------------------------------------------------------------------------------

  void SwapBuffers();

  // ------------------------------------------------------------------------------

  bool ShouldClose() const;

  // ------------------------------------------------------------------------------

private:
  void CreateFullscreenWindow(std::string _title, GLFWmonitor* _monitor,
                              std::int32_t _width, std::int32_t _height);

  // ------------------------------------------------------------------------------

  void CreateBorderlessFullscreenWindow(std::string _title,
                                        GLFWmonitor* _monitor);

  // ------------------------------------------------------------------------------

  void CreateWindowedWindow(std::string _title, std::int32_t _width,
                            std::int32_t _height);

  // ------------------------------------------------------------------------------

private:
  std::unique_ptr<Window> m_window;
  messaging::MessageBus& m_applicationMessageBus;
};

} // namespace video
} // namespace mage