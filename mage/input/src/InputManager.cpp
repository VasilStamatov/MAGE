#include "input/InputManager.h"

#include "messaging/MessageBus.h"
#include "video/Window.h"

#include <glfw3.h>

namespace mage
{
namespace input
{

// ------------------------------------------------------------------------------

namespace
{

// ------------------------------------------------------------------------------

InputKey GetInputKeyFromGLFWKey(int _key)
{
  switch (_key)
  {
    case GLFW_KEY_UNKNOWN:
      return InputKey::Unknown;
    case GLFW_KEY_BACKSPACE:
      return InputKey::Backspace;
    case GLFW_KEY_TAB:
      return InputKey::Tab;
    case GLFW_KEY_ENTER:
      return InputKey::Return;
    case GLFW_KEY_PAUSE:
      return InputKey::Pause;
    case GLFW_KEY_ESCAPE:
      return InputKey::Escape;
    case GLFW_KEY_SPACE:
      return InputKey::Space;
    case GLFW_KEY_COMMA:
      return InputKey::Comma;
    case GLFW_KEY_MINUS:
      return InputKey::Minus;
    case GLFW_KEY_PERIOD:
      return InputKey::Period;
    case GLFW_KEY_SLASH:
      return InputKey::Slash;
    case GLFW_KEY_0:
      return InputKey::Zero;
    case GLFW_KEY_1:
      return InputKey::One;
    case GLFW_KEY_2:
      return InputKey::Two;
    case GLFW_KEY_3:
      return InputKey::Three;
    case GLFW_KEY_4:
      return InputKey::Four;
    case GLFW_KEY_5:
      return InputKey::Five;
    case GLFW_KEY_6:
      return InputKey::Six;
    case GLFW_KEY_7:
      return InputKey::Seven;
    case GLFW_KEY_8:
      return InputKey::Eight;
    case GLFW_KEY_9:
      return InputKey::Nine;
    case GLFW_KEY_SEMICOLON:
      return InputKey::Semicolon;
    case GLFW_KEY_EQUAL:
      return InputKey::Equals;
    case GLFW_KEY_LEFT_BRACKET:
      return InputKey::LeftBracket;
    case GLFW_KEY_BACKSLASH:
      return InputKey::Backslash;
    case GLFW_KEY_RIGHT_BRACKET:
      return InputKey::RightBracket;
    case GLFW_KEY_A:
      return InputKey::A;
    case GLFW_KEY_B:
      return InputKey::B;
    case GLFW_KEY_C:
      return InputKey::C;
    case GLFW_KEY_D:
      return InputKey::D;
    case GLFW_KEY_E:
      return InputKey::E;
    case GLFW_KEY_F:
      return InputKey::F;
    case GLFW_KEY_G:
      return InputKey::G;
    case GLFW_KEY_H:
      return InputKey::H;
    case GLFW_KEY_I:
      return InputKey::I;
    case GLFW_KEY_J:
      return InputKey::J;
    case GLFW_KEY_K:
      return InputKey::K;
    case GLFW_KEY_L:
      return InputKey::L;
    case GLFW_KEY_M:
      return InputKey::M;
    case GLFW_KEY_N:
      return InputKey::N;
    case GLFW_KEY_O:
      return InputKey::O;
    case GLFW_KEY_P:
      return InputKey::P;
    case GLFW_KEY_Q:
      return InputKey::Q;
    case GLFW_KEY_R:
      return InputKey::R;
    case GLFW_KEY_S:
      return InputKey::S;
    case GLFW_KEY_T:
      return InputKey::T;
    case GLFW_KEY_U:
      return InputKey::U;
    case GLFW_KEY_V:
      return InputKey::V;
    case GLFW_KEY_W:
      return InputKey::W;
    case GLFW_KEY_X:
      return InputKey::X;
    case GLFW_KEY_Y:
      return InputKey::Y;
    case GLFW_KEY_Z:
      return InputKey::Z;
    case GLFW_KEY_DELETE:
      return InputKey::Delete;
    case GLFW_KEY_KP_DECIMAL:
      return InputKey::Decimal;
    case GLFW_KEY_KP_DIVIDE:
      return InputKey::Divide;
    case GLFW_KEY_KP_MULTIPLY:
      return InputKey::Multiply;
    case GLFW_KEY_KP_SUBTRACT:
      return InputKey::Subtract;
    case GLFW_KEY_KP_ADD:
      return InputKey::Add;
    case GLFW_KEY_KP_ENTER:
      return InputKey::NumpadEnter;
    case GLFW_KEY_KP_EQUAL:
      return InputKey::NumpadEquals;
    case GLFW_KEY_UP:
      return InputKey::ArrowUp;
    case GLFW_KEY_DOWN:
      return InputKey::ArrowDown;
    case GLFW_KEY_RIGHT:
      return InputKey::ArrowRight;
    case GLFW_KEY_LEFT:
      return InputKey::ArrowLeft;
    case GLFW_KEY_INSERT:
      return InputKey::Insert;
    case GLFW_KEY_HOME:
      return InputKey::Home;
    case GLFW_KEY_END:
      return InputKey::End;
    case GLFW_KEY_PAGE_UP:
      return InputKey::PageUp;
    case GLFW_KEY_PAGE_DOWN:
      return InputKey::PageDown;
    case GLFW_KEY_F1:
      return InputKey::F1;
    case GLFW_KEY_F2:
      return InputKey::F2;
    case GLFW_KEY_F3:
      return InputKey::F3;
    case GLFW_KEY_F4:
      return InputKey::F4;
    case GLFW_KEY_F5:
      return InputKey::F5;
    case GLFW_KEY_F6:
      return InputKey::F6;
    case GLFW_KEY_F7:
      return InputKey::F7;
    case GLFW_KEY_F8:
      return InputKey::F8;
    case GLFW_KEY_F9:
      return InputKey::F9;
    case GLFW_KEY_F10:
      return InputKey::F10;
    case GLFW_KEY_F11:
      return InputKey::F11;
    case GLFW_KEY_F12:
      return InputKey::F12;
    case GLFW_KEY_F13:
      return InputKey::F13;
    case GLFW_KEY_F14:
      return InputKey::F14;
    case GLFW_KEY_F15:
      return InputKey::F15;
    case GLFW_KEY_RIGHT_SHIFT:
      return InputKey::RightShift;
    case GLFW_KEY_LEFT_SHIFT:
      return InputKey::LeftShift;
    case GLFW_KEY_RIGHT_CONTROL:
      return InputKey::RightControl;
    case GLFW_KEY_LEFT_CONTROL:
      return InputKey::LeftControl;
    case GLFW_KEY_RIGHT_ALT:
      return InputKey::RightAlt;
    case GLFW_KEY_LEFT_ALT:
      return InputKey::LeftAlt;
    case GLFW_KEY_MENU:
      return InputKey::AppMenu;
    case GLFW_KEY_PRINT_SCREEN:
      return InputKey::SysRq;
    case GLFW_MOUSE_BUTTON_LEFT:
      return InputKey::LeftMouseButton;
    case GLFW_MOUSE_BUTTON_RIGHT:
      return InputKey::RightMouseButton;
    case GLFW_MOUSE_BUTTON_MIDDLE:
      return InputKey::MiddleMouseButton;
  }
  return InputKey::Unknown;
}

// ------------------------------------------------------------------------------

void KeyCallback(GLFWwindow* _handle, int _key, int _scancode, int _action,
                 int _modifiers)
{
  auto* appMessageBus =
      static_cast<messaging::MessageBus*>(glfwGetWindowUserPointer(_handle));

  if (_action == GLFW_PRESS)
  {
    OnKeyPress keyPressEvent{GetInputKeyFromGLFWKey(_key)};
    appMessageBus->Broadcast(&keyPressEvent);
  }
  else if (_action == GLFW_RELEASE)
  {
    OnKeyRelease keyReleaseEvent{GetInputKeyFromGLFWKey(_key)};
    appMessageBus->Broadcast(&keyReleaseEvent);
  }
}

// ------------------------------------------------------------------------------

void MouseButtonCallback(GLFWwindow* _handle, int _button, int _action,
                         int _modifiers)
{
  auto* appMessageBus =
      static_cast<messaging::MessageBus*>(glfwGetWindowUserPointer(_handle));

  if (_action == GLFW_PRESS)
  {
    OnKeyPress keyPressEvent{GetInputKeyFromGLFWKey(_button)};
    appMessageBus->Broadcast(&keyPressEvent);
  }
  else if (_action == GLFW_RELEASE)
  {
    OnKeyRelease keyReleaseEvent{GetInputKeyFromGLFWKey(_button)};
    appMessageBus->Broadcast(&keyReleaseEvent);
  }
}

// ------------------------------------------------------------------------------

void CursorPositionCallback(GLFWwindow* _handle, double _posX, double _posY)
{
  auto* appMessageBus =
      static_cast<messaging::MessageBus*>(glfwGetWindowUserPointer(_handle));

  CursorPositionMovedEvent event{static_cast<float>(_posX),
                                 static_cast<float>(_posY)};
  appMessageBus->Broadcast(&event);
}

// ------------------------------------------------------------------------------

void MouseScrollCallback(GLFWwindow* _handle, double _xOffset, double _yOffset)
{
  auto* appMessageBus =
      static_cast<messaging::MessageBus*>(glfwGetWindowUserPointer(_handle));

  MouseScrollChangedEvent event{static_cast<float>(_xOffset),
                                static_cast<float>(_yOffset)};
  appMessageBus->Broadcast(&event);
}

// ------------------------------------------------------------------------------

} // namespace

// ------------------------------------------------------------------------------

InputManager::InputManager(messaging::MessageBus& _messageBus)
    : m_windowHandle(nullptr)
{
  _messageBus.Subscribe(this, &InputManager::OnWindowCreatedEvent);
  _messageBus.Subscribe(this, &InputManager::OnSetCursorStateEvent);
}

// ------------------------------------------------------------------------------

void InputManager::Initialize() {}

// ------------------------------------------------------------------------------

void InputManager::Shutdown() {}

// ------------------------------------------------------------------------------

void InputManager::Update() { glfwPollEvents(); }

// ------------------------------------------------------------------------------

void InputManager::OnWindowCreatedEvent(video::OnWindowCreated* _event)
{
  m_windowHandle = _event->m_window.GetHandle();

  glfwSetKeyCallback(m_windowHandle, KeyCallback);
  glfwSetMouseButtonCallback(m_windowHandle, MouseButtonCallback);
  glfwSetScrollCallback(m_windowHandle, MouseScrollCallback);
  glfwSetCursorPosCallback(m_windowHandle, CursorPositionCallback);
}

// ------------------------------------------------------------------------------

void InputManager::OnSetCursorStateEvent(SetCursorStateEvent* _event)
{
  int mode = GLFW_CURSOR_NORMAL;

  switch (_event->m_newState)
  {
    case CursorState::Visible:
      mode = GLFW_CURSOR_NORMAL;
      break;
    case CursorState::Hidden:
      mode = GLFW_CURSOR_HIDDEN;
      break;
    case CursorState::Disabled:
      mode = GLFW_CURSOR_DISABLED;
      break;
  }

  glfwSetInputMode(m_windowHandle, GLFW_CURSOR, mode);
}

// ------------------------------------------------------------------------------

} // namespace input
} // namespace mage
