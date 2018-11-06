#include "video/Keyboard.h"

#include "video/InputManager.h"
#include "video/Window.h"

#define GLFW_INCLUDE_VULKAN
#include <glfw3.h>

namespace mage
{
namespace video
{

// ------------------------------------------------------------------------------

namespace
{

// ------------------------------------------------------------------------------

KeyboardKey GetKeyboardKeyFromGLFWKey(std::int32_t _key)
{
  switch (_key)
  {
    case GLFW_KEY_UNKNOWN:
      return KeyboardKey::Unknown;
    case GLFW_KEY_BACKSPACE:
      return KeyboardKey::Backspace;
    case GLFW_KEY_TAB:
      return KeyboardKey::Tab;
    case GLFW_KEY_ENTER:
      return KeyboardKey::Return;
    case GLFW_KEY_PAUSE:
      return KeyboardKey::Pause;
    case GLFW_KEY_ESCAPE:
      return KeyboardKey::Escape;
    case GLFW_KEY_SPACE:
      return KeyboardKey::Space;
    case GLFW_KEY_COMMA:
      return KeyboardKey::Comma;
    case GLFW_KEY_MINUS:
      return KeyboardKey::Minus;
    case GLFW_KEY_PERIOD:
      return KeyboardKey::Period;
    case GLFW_KEY_SLASH:
      return KeyboardKey::Slash;
    case GLFW_KEY_0:
      return KeyboardKey::Zero;
    case GLFW_KEY_1:
      return KeyboardKey::One;
    case GLFW_KEY_2:
      return KeyboardKey::Two;
    case GLFW_KEY_3:
      return KeyboardKey::Three;
    case GLFW_KEY_4:
      return KeyboardKey::Four;
    case GLFW_KEY_5:
      return KeyboardKey::Five;
    case GLFW_KEY_6:
      return KeyboardKey::Six;
    case GLFW_KEY_7:
      return KeyboardKey::Seven;
    case GLFW_KEY_8:
      return KeyboardKey::Eight;
    case GLFW_KEY_9:
      return KeyboardKey::Nine;
    case GLFW_KEY_SEMICOLON:
      return KeyboardKey::Semicolon;
    case GLFW_KEY_EQUAL:
      return KeyboardKey::Equals;
    case GLFW_KEY_LEFT_BRACKET:
      return KeyboardKey::LeftBracket;
    case GLFW_KEY_BACKSLASH:
      return KeyboardKey::Backslash;
    case GLFW_KEY_RIGHT_BRACKET:
      return KeyboardKey::RightBracket;
    case GLFW_KEY_A:
      return KeyboardKey::A;
    case GLFW_KEY_B:
      return KeyboardKey::B;
    case GLFW_KEY_C:
      return KeyboardKey::C;
    case GLFW_KEY_D:
      return KeyboardKey::D;
    case GLFW_KEY_E:
      return KeyboardKey::E;
    case GLFW_KEY_F:
      return KeyboardKey::F;
    case GLFW_KEY_G:
      return KeyboardKey::G;
    case GLFW_KEY_H:
      return KeyboardKey::H;
    case GLFW_KEY_I:
      return KeyboardKey::I;
    case GLFW_KEY_J:
      return KeyboardKey::J;
    case GLFW_KEY_K:
      return KeyboardKey::K;
    case GLFW_KEY_L:
      return KeyboardKey::L;
    case GLFW_KEY_M:
      return KeyboardKey::M;
    case GLFW_KEY_N:
      return KeyboardKey::N;
    case GLFW_KEY_O:
      return KeyboardKey::O;
    case GLFW_KEY_P:
      return KeyboardKey::P;
    case GLFW_KEY_Q:
      return KeyboardKey::Q;
    case GLFW_KEY_R:
      return KeyboardKey::R;
    case GLFW_KEY_S:
      return KeyboardKey::S;
    case GLFW_KEY_T:
      return KeyboardKey::T;
    case GLFW_KEY_U:
      return KeyboardKey::U;
    case GLFW_KEY_V:
      return KeyboardKey::V;
    case GLFW_KEY_W:
      return KeyboardKey::W;
    case GLFW_KEY_X:
      return KeyboardKey::X;
    case GLFW_KEY_Y:
      return KeyboardKey::Y;
    case GLFW_KEY_Z:
      return KeyboardKey::Z;
    case GLFW_KEY_DELETE:
      return KeyboardKey::Delete;
    case GLFW_KEY_KP_DECIMAL:
      return KeyboardKey::Decimal;
    case GLFW_KEY_KP_DIVIDE:
      return KeyboardKey::Divide;
    case GLFW_KEY_KP_MULTIPLY:
      return KeyboardKey::Multiply;
    case GLFW_KEY_KP_SUBTRACT:
      return KeyboardKey::Subtract;
    case GLFW_KEY_KP_ADD:
      return KeyboardKey::Add;
    case GLFW_KEY_KP_ENTER:
      return KeyboardKey::NumpadEnter;
    case GLFW_KEY_KP_EQUAL:
      return KeyboardKey::NumpadEquals;
    case GLFW_KEY_UP:
      return KeyboardKey::ArrowUp;
    case GLFW_KEY_DOWN:
      return KeyboardKey::ArrowDown;
    case GLFW_KEY_RIGHT:
      return KeyboardKey::ArrowRight;
    case GLFW_KEY_LEFT:
      return KeyboardKey::ArrowLeft;
    case GLFW_KEY_INSERT:
      return KeyboardKey::Insert;
    case GLFW_KEY_HOME:
      return KeyboardKey::Home;
    case GLFW_KEY_END:
      return KeyboardKey::End;
    case GLFW_KEY_PAGE_UP:
      return KeyboardKey::PageUp;
    case GLFW_KEY_PAGE_DOWN:
      return KeyboardKey::PageDown;
    case GLFW_KEY_F1:
      return KeyboardKey::F1;
    case GLFW_KEY_F2:
      return KeyboardKey::F2;
    case GLFW_KEY_F3:
      return KeyboardKey::F3;
    case GLFW_KEY_F4:
      return KeyboardKey::F4;
    case GLFW_KEY_F5:
      return KeyboardKey::F5;
    case GLFW_KEY_F6:
      return KeyboardKey::F6;
    case GLFW_KEY_F7:
      return KeyboardKey::F7;
    case GLFW_KEY_F8:
      return KeyboardKey::F8;
    case GLFW_KEY_F9:
      return KeyboardKey::F9;
    case GLFW_KEY_F10:
      return KeyboardKey::F10;
    case GLFW_KEY_F11:
      return KeyboardKey::F11;
    case GLFW_KEY_F12:
      return KeyboardKey::F12;
    case GLFW_KEY_F13:
      return KeyboardKey::F13;
    case GLFW_KEY_F14:
      return KeyboardKey::F14;
    case GLFW_KEY_F15:
      return KeyboardKey::F15;
    case GLFW_KEY_RIGHT_SHIFT:
      return KeyboardKey::RightShift;
    case GLFW_KEY_LEFT_SHIFT:
      return KeyboardKey::LeftShift;
    case GLFW_KEY_RIGHT_CONTROL:
      return KeyboardKey::RightControl;
    case GLFW_KEY_LEFT_CONTROL:
      return KeyboardKey::LeftControl;
    case GLFW_KEY_RIGHT_ALT:
      return KeyboardKey::RightAlt;
    case GLFW_KEY_LEFT_ALT:
      return KeyboardKey::LeftAlt;
    case GLFW_KEY_MENU:
      return KeyboardKey::AppMenu;
    case GLFW_KEY_PRINT_SCREEN:
      return KeyboardKey::SysRq;
  }
  return KeyboardKey::Unknown;
}

// ------------------------------------------------------------------------------

void KeyCallback(GLFWwindow* _handle, int _key, int _scancode, int _action,
                 int _modifiers)
{
  InputManager* inputManager =
      static_cast<InputManager*>(glfwGetWindowUserPointer(_handle));
  Keyboard& keyboard = inputManager->GetKeyboard();

  if (_action != GLFW_RELEASE)
  {
    keyboard.PressKey(GetKeyboardKeyFromGLFWKey(_key));
  }
  else
  {
    keyboard.ReleaseKey(GetKeyboardKeyFromGLFWKey(_key));
  }
}

} // namespace

// ------------------------------------------------------------------------------

Keyboard::Keyboard(Window& _sourceWindow)
    : m_currentKeysState(false)
    , m_previousKeysState(false)
{
  glfwSetKeyCallback(_sourceWindow.GetHandle(), KeyCallback);
}

// ------------------------------------------------------------------------------

void Keyboard::Refresh() { m_previousKeysState = m_currentKeysState; }

// ------------------------------------------------------------------------------

void Keyboard::PressKey(KeyboardKey _Key) noexcept
{
  m_currentKeysState[(std::uint8_t)_Key] = true;
}

// ------------------------------------------------------------------------------

void Keyboard::ReleaseKey(KeyboardKey _Key) noexcept
{
  m_currentKeysState[(std::uint8_t)_Key] = false;
}

// ------------------------------------------------------------------------------

bool Keyboard::IsKeyPressed(KeyboardKey _Key) const noexcept
{
  return m_currentKeysState[(std::uint8_t)_Key] &&
         !m_previousKeysState[(std::uint8_t)_Key];
}

// ------------------------------------------------------------------------------

bool Keyboard::IsKeyHeldDown(KeyboardKey _Key) const noexcept
{
  return m_currentKeysState[(std::uint8_t)_Key];
}

} // namespace video
} // namespace mage