#include "video/Mouse.h"

#include "video/InputManager.h"
#include "video/Window.h"

#include <glfw3.h>

namespace mage
{
namespace video
{

namespace
{

// ------------------------------------------------------------------------------

MouseButton GetMouseButtonFromGLFWButton(std::int32_t _button) noexcept
{
  switch (_button)
  {
    case GLFW_KEY_UNKNOWN:
      return MouseButton::Unknown;
    case GLFW_MOUSE_BUTTON_LEFT:
      return MouseButton::LeftMouseButton;
    case GLFW_MOUSE_BUTTON_RIGHT:
      return MouseButton::RightMouseButton;
    case GLFW_MOUSE_BUTTON_MIDDLE:
      return MouseButton::MiddleMouseButton;
  }
  return MouseButton::Unknown;
}

// ------------------------------------------------------------------------------

void CursorPositionCallback(GLFWwindow* _window, double _posX, double _posY)
{
  InputManager* inputManager =
      static_cast<InputManager*>(glfwGetWindowUserPointer(_window));
  inputManager->GetMouse().SetMousePosition(math::Vec2d(_posX, _posY));
}

// ------------------------------------------------------------------------------

void MouseButtonCallback(GLFWwindow* _window, std::int32_t _button,
                         std::int32_t _action, std::int32_t _mods)
{
  InputManager* inputManager =
      static_cast<InputManager*>(glfwGetWindowUserPointer(_window));

  _mods;

  if (_action != GLFW_RELEASE)
  {
    inputManager->GetMouse().PressButton(GetMouseButtonFromGLFWButton(_button));
  }
  else
  {
    inputManager->GetMouse().ReleaseButton(
        GetMouseButtonFromGLFWButton(_button));
  }
}

// ------------------------------------------------------------------------------

void MouseScrollCallback(GLFWwindow* _window, double _xOffset, double _yOffset)
{
  InputManager* inputManager =
      static_cast<InputManager*>(glfwGetWindowUserPointer(_window));

  inputManager->GetMouse().SetMouseScrollValue(math::Vec2d(_xOffset, _yOffset));
}

// ------------------------------------------------------------------------------

} // namespace

// ------------------------------------------------------------------------------

Mouse::Mouse(Window& _sourceWindow)
    : m_currentButtonsState(false)
    , m_previousButtonsState(false)
    , m_currentCursorPos(0.0)
    , m_previousCursorPos(0.0)
    , m_mouseScrollValue(0.0)
{
  glfwSetMouseButtonCallback(_sourceWindow.GetHandle(), MouseButtonCallback);
  glfwSetScrollCallback(_sourceWindow.GetHandle(), MouseScrollCallback);
  glfwSetCursorPosCallback(_sourceWindow.GetHandle(), CursorPositionCallback);
}

// ------------------------------------------------------------------------------

void Mouse::Refresh()
{
  m_mouseScrollValue[1] = 0.0;
  m_previousCursorPos = m_currentCursorPos;
  m_previousButtonsState = m_currentButtonsState;
}

// ------------------------------------------------------------------------------

void Mouse::PressButton(MouseButton _button) noexcept
{
  m_currentButtonsState[(std::uint8_t)_button] = true;
}

// ------------------------------------------------------------------------------

void Mouse::ReleaseButton(MouseButton _button) noexcept
{
  m_currentButtonsState[(std::uint8_t)_button] = false;
}

// ------------------------------------------------------------------------------

void Mouse::SetMousePosition(math::Vec2d _screenSpacePosition) noexcept
{
  m_previousCursorPos = std::move(m_currentCursorPos);
  m_currentCursorPos = std::move(_screenSpacePosition);
}

// ------------------------------------------------------------------------------

void Mouse::SetMouseScrollValue(math::Vec2d _scroll) noexcept
{
  m_mouseScrollValue = std::move(_scroll);
}

// ------------------------------------------------------------------------------

bool Mouse::IsButtonPressed(MouseButton _button) const noexcept
{
  return m_currentButtonsState[(std::uint8_t)_button] &&
         !m_previousButtonsState[(std::uint8_t)_button];
}

// ------------------------------------------------------------------------------

bool Mouse::IsButtonHeldDown(MouseButton _button) const noexcept
{
  return m_currentButtonsState[(std::uint8_t)_button];
}

// ------------------------------------------------------------------------------

const math::Vec2d& Mouse::GetCurrentCursorPos() const noexcept
{
  return m_currentCursorPos;
}

// ------------------------------------------------------------------------------

const math::Vec2d& Mouse::GetPreviousCursorPos() const noexcept
{
  return m_previousCursorPos;
}

// ------------------------------------------------------------------------------

const math::Vec2d& Mouse::GetMouseScrollValue() const noexcept
{
  return m_mouseScrollValue;
}

// ------------------------------------------------------------------------------

} // namespace video
} // namespace mage