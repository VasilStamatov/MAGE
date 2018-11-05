#pragma once

#include "Keyboard.h"
#include "Mouse.h"

#include <cstdint>
#include <string>

struct GLFWmonitor;
struct GLFWwindow;

namespace mage
{
namespace video
{

// ------------------------------------------------------------------------------

class Window
{
public:
  // ------------------------------------------------------------------------------

  struct Frame
  {
    Frame(std::int32_t _left, std::int32_t _top, std::int32_t _right,
          std::int32_t _bottom);

    std::int32_t m_left;
    std::int32_t m_top;
    std::int32_t m_right;
    std::int32_t m_bottom;
  };

  // ------------------------------------------------------------------------------

  struct ScreenPosition
  {
    ScreenPosition(std::int32_t _x, std::int32_t _y);

    std::int32_t m_x;
    std::int32_t m_y;
  };

  // ------------------------------------------------------------------------------

  struct ScreenSize
  {
    ScreenSize(std::int32_t _width, std::int32_t _height);

    std::int32_t m_width;
    std::int32_t m_height;
  };

  // ------------------------------------------------------------------------------

public:
  // ------------------------------------------------------------------------------

  Window(std::string _title, GLFWmonitor* _monitor, std::int32_t _width,
         std::int32_t _height);
  Window(std::string _title, GLFWmonitor* _monitor);
  Window(std::string _title, std::int32_t _width, std::int32_t _height);

  // ------------------------------------------------------------------------------

  ~Window();

  // ------------------------------------------------------------------------------

  Window(const Window&) = delete;
  Window& operator=(const Window&) = delete;

  // ------------------------------------------------------------------------------

  Window(Window&& _other);
  Window& operator=(Window&& _rhs);

  // ------------------------------------------------------------------------------

  void MakeCurrent();
  void SwapBuffers();

  // ------------------------------------------------------------------------------

  bool ShouldClose() const;
  ScreenPosition GetPosition() const;
  ScreenSize GetSize() const;
  ScreenSize GetFramebufferSize() const;
  Frame GetFrame() const;

  // ------------------------------------------------------------------------------

  GLFWwindow* GetHandle() const;

  // ------------------------------------------------------------------------------

private:
  std::string m_title;

  ScreenPosition m_position;
  ScreenSize m_size;

  GLFWwindow* m_handle;
};

// ------------------------------------------------------------------------------

} // namespace video
} // namespace mage