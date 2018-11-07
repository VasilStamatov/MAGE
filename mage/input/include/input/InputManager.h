#pragma once

#include "InputKeys.h"

#include <array>
#include <functional>

namespace mage
{

namespace video
{
struct OnWindowCreated;
}

namespace messaging
{
class MessageBus;
}

namespace input
{

// ------------------------------------------------------------------------------

// Received events
struct AddBindingEvent
{
  std::function<void()> m_callback;
  InputKey m_key;
};

// ------------------------------------------------------------------------------

// Broadcasted events
struct CursorPositionMovedEvent
{
  double m_xPos = 0.0;
  double m_yPos = 0.0;
};

struct MouseScrollChangedEvent
{
  double m_xOffset = 0.0;
  double m_yOffset = 0.0;
};

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

  void OnWindowCreatedEvent(video::OnWindowCreated* _event);

  // ------------------------------------------------------------------------------

  void OnAddBindingEvent(AddBindingEvent* _event);

  // ------------------------------------------------------------------------------

  void OnKeyDown(InputKey _key);

  // ------------------------------------------------------------------------------

  void OnKeyUp(InputKey _key);

  // ------------------------------------------------------------------------------

  void OnCursorMoved(double _xPos, double _yPos);

  // ------------------------------------------------------------------------------

  void OnMouseScrollChanged(double _xOffset, double _yOffset);

private:
  using Callback = std::function<void()>;

  // ------------------------------------------------------------------------------

  std::array<Callback, (int)InputKey::NumKeys> m_bindings;
  std::vector<int> m_pressedKeys;

  messaging::MessageBus& m_applicationMessageBus;
};

// ------------------------------------------------------------------------------

} // namespace input
} // namespace mage