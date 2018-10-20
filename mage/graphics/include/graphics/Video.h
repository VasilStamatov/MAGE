#pragma once

#include "Window.h"

namespace mage
{
namespace graphics
{

class Video
{
public:
  Video();

  void Initialize();
  void Shutdown();

  void SwapBuffers();

private:
  void CreateFullscreenWindow(std::string _title, GLFWmonitor* _monitor,
                              std::int32_t _width, std::int32_t _height);
  void CreateBorderlessFullscreenWindow(std::string _title,
                                        GLFWmonitor* _monitor);
  void CreateWindowedWindow(std::string _title, std::int32_t _width,
                            std::int32_t _height);

private:
  std::unique_ptr<Window> m_window;
};

} // namespace graphics
} // namespace mage