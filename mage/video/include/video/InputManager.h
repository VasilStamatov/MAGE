#pragma once

#include "Keyboard.h"
#include "Mouse.h"

namespace mage
{
namespace video
{

// ------------------------------------------------------------------------------

class Window;

// ------------------------------------------------------------------------------

class InputManager
{
public:
  InputManager();

  // ------------------------------------------------------------------------------

  void Initialize(Window& _window);

  // ------------------------------------------------------------------------------

  void Shutdown();

  // ------------------------------------------------------------------------------

  void Update();

  // ------------------------------------------------------------------------------

  bool IsKeyPressed(KeyboardKey _key) const noexcept;
  bool IsKeyHeldDown(KeyboardKey _key) const noexcept;

  // ------------------------------------------------------------------------------

  bool IsButtonPressed(MouseButton _button) const noexcept;
  bool IsButtonHeldDown(MouseButton _button) const noexcept;

  // ------------------------------------------------------------------------------

  const math::Vec2d& GetCurrentCursorPos() const noexcept;
  const math::Vec2d& GetPreviousCursorPos() const noexcept;
  const math::Vec2d& GetMouseScrollValue() const noexcept;

  // ------------------------------------------------------------------------------

  Keyboard& GetKeyboard();

  // ------------------------------------------------------------------------------

  Mouse& GetMouse();

  // ------------------------------------------------------------------------------

private:
  std::unique_ptr<Keyboard> m_keyboard;
  std::unique_ptr<Mouse> m_mouse;
};

// ------------------------------------------------------------------------------

} // namespace video
} // namespace mage