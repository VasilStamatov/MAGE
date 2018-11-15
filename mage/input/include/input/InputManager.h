#pragma once

#include "InputKeys.h"

#include <array>
#include <functional>

namespace mage
{

// ------------------------------------------------------------------------------

namespace video
{
struct OnWindowCreated;
}

// ------------------------------------------------------------------------------

namespace messaging
{
class MessageBus;
}

// ------------------------------------------------------------------------------

namespace input
{

// ------------------------------------------------------------------------------

// Broadcasted events
struct CursorPositionMovedEvent
{
  float m_xPos = 0.0f;
  float m_yPos = 0.0f;
};

struct MouseScrollChangedEvent
{
  float m_xOffset = 0.0f;
  float m_yOffset = 0.0f;
};

struct OnKeyPress
{
  InputKey m_key;
};

struct OnKeyRelease
{
  InputKey m_key;
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
};

// ------------------------------------------------------------------------------

} // namespace input
} // namespace mage