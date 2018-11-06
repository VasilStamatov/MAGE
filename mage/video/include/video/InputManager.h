#pragma once

#include "Keyboard.h"
#include "Mouse.h"
#include "messaging/MessageBus.h"

namespace mage
{
namespace video
{

// ------------------------------------------------------------------------------

class InputManager
{
public:
  InputManager(messaging::MessageBus& _messageBus);

  // ------------------------------------------------------------------------------

  void Initialize();

  // ------------------------------------------------------------------------------

  void Shutdown();

  // ------------------------------------------------------------------------------

  void Update();

  // ------------------------------------------------------------------------------

  void OnWindowCreatedEvent(struct OnWindowCreated* _event);

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

  messaging::MessageBus& m_applicationMessageBus;
};

// ------------------------------------------------------------------------------

} // namespace video
} // namespace mage