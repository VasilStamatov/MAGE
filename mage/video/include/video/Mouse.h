#pragma once

#include <math/vec.h>

#include <bitset>
#include <cstdint>

namespace mage
{
namespace video
{

// ------------------------------------------------------------------------------

enum class MouseButton : std::uint8_t
{
  Unknown,
  LeftMouseButton,
  MiddleMouseButton,
  RightMouseButton,

  NumButtons
};

// ------------------------------------------------------------------------------

class Window;

// ------------------------------------------------------------------------------

class Mouse
{
public:
  Mouse(Window& _sourceWindow);

  // ------------------------------------------------------------------------------

  void Refresh();

  // ------------------------------------------------------------------------------

  void PressButton(MouseButton _button) noexcept;
  void ReleaseButton(MouseButton _button) noexcept;

  // ------------------------------------------------------------------------------

  void SetMousePosition(math::Vec2d _screenSpacePosition) noexcept;
  void SetMouseScrollValue(math::Vec2d _scroll) noexcept;

  // ------------------------------------------------------------------------------

  bool IsButtonPressed(MouseButton _button) const noexcept;
  bool IsButtonHeldDown(MouseButton _button) const noexcept;

  // ------------------------------------------------------------------------------

  const math::Vec2d& GetCurrentCursorPos() const noexcept;
  const math::Vec2d& GetPreviousCursorPos() const noexcept;
  const math::Vec2d& GetMouseScrollValue() const noexcept;

  // ------------------------------------------------------------------------------

private:
  std::bitset<(std::uint8_t)MouseButton::NumButtons> m_currentButtonsState;
  std::bitset<(std::uint8_t)MouseButton::NumButtons> m_previousButtonsState;
  math::Vec2d m_currentCursorPos;
  math::Vec2d m_previousCursorPos;
  math::Vec2d m_mouseScrollValue;
};

// ------------------------------------------------------------------------------

} // namespace video
} // namespace mage