#include "video/InputManager.h"

#include "video/Video.h"

#define GLFW_INCLUDE_VULKAN
#include <glfw3.h>

namespace mage
{
namespace video
{

// ------------------------------------------------------------------------------

InputManager::InputManager(messaging::MessageBus& _messageBus)
    : m_keyboard(nullptr)
    , m_mouse(nullptr)
    , m_applicationMessageBus(_messageBus)
{
  m_applicationMessageBus.Subscribe(this, &InputManager::OnWindowCreatedEvent);
}

// ------------------------------------------------------------------------------

void InputManager::Initialize() {}

// ------------------------------------------------------------------------------

void InputManager::Shutdown()
{
  m_keyboard.reset();
  m_mouse.reset();
}

// ------------------------------------------------------------------------------

void InputManager::Update()
{
  m_keyboard->Refresh();
  m_mouse->Refresh();

  glfwPollEvents();
}

// ------------------------------------------------------------------------------

void InputManager::OnWindowCreatedEvent(OnWindowCreated* _event)
{
  glfwSetWindowUserPointer(_event->m_window.GetHandle(), this);

  m_keyboard = std::make_unique<Keyboard>(_event->m_window);
  m_mouse = std::make_unique<Mouse>(_event->m_window);
}

// ------------------------------------------------------------------------------

bool InputManager::IsKeyPressed(KeyboardKey _key) const noexcept
{
  return m_keyboard->IsKeyPressed(_key);
}

// ------------------------------------------------------------------------------

bool InputManager::IsKeyHeldDown(KeyboardKey _key) const noexcept
{
  return m_keyboard->IsKeyHeldDown(_key);
}

// ------------------------------------------------------------------------------

bool InputManager::IsButtonPressed(MouseButton _button) const noexcept
{
  return m_mouse->IsButtonPressed(_button);
}

// ------------------------------------------------------------------------------

bool InputManager::IsButtonHeldDown(MouseButton _button) const noexcept
{
  return m_mouse->IsButtonHeldDown(_button);
}

// ------------------------------------------------------------------------------

const math::Vec2d& InputManager::GetCurrentCursorPos() const noexcept
{
  return m_mouse->GetCurrentCursorPos();
}

// ------------------------------------------------------------------------------

const math::Vec2d& InputManager::GetPreviousCursorPos() const noexcept
{
  return m_mouse->GetPreviousCursorPos();
}

// ------------------------------------------------------------------------------

const math::Vec2d& InputManager::GetMouseScrollValue() const noexcept
{
  return m_mouse->GetMouseScrollValue();
}

// ------------------------------------------------------------------------------

Keyboard& InputManager::GetKeyboard() { return *m_keyboard; }

// ------------------------------------------------------------------------------

Mouse& InputManager::GetMouse() { return *m_mouse; }

// ------------------------------------------------------------------------------

} // namespace video
} // namespace mage
