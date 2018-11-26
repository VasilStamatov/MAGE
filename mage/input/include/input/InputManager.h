#pragma once

#include "InputKeys.h"

#include <array>
#include <functional>

struct GLFWwindow;

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

enum class CursorState
{
  Visible, ///< makes the cursor visible and behaving normally
  Hidden, ///< makes the cursor invisible when it is over the client area of the
          /// window but does not restrict the cursor from leaving
  Disabled ///< hides and grabs the cursor, providing virtual and unlimited
           ///< cursor
           /// movement
};

/////////////////////////////////////////////////
/// Event that can be sent to change the cursor state
/////////////////////////////////////////////////
struct SetCursorStateEvent
{
  CursorState m_newState;
};

/////////////////////////////////////////////////
/// Event that is broadcasted whenever the cursor position changes.
/////////////////////////////////////////////////
struct CursorPositionMovedEvent
{
  float m_xPos = 0.0f;
  float m_yPos = 0.0f;
};

/////////////////////////////////////////////////
/// Event that is broadcasted whenever the scroll value changes.
/////////////////////////////////////////////////
struct MouseScrollChangedEvent
{
  float m_xOffset = 0.0f;
  float m_yOffset = 0.0f;
};

/////////////////////////////////////////////////
/// Event that is broadcasted whenever a Key is pressed.
/////////////////////////////////////////////////
struct OnKeyPress
{
  InputKey m_key;
};

/////////////////////////////////////////////////
/// Event that is broadcasted whenever a Key is released.
/////////////////////////////////////////////////
struct OnKeyRelease
{
  InputKey m_key;
};

// ------------------------------------------------------------------------------

/////////////////////////////////////////////////
/// The input manager registers the input callbacks which then send broadcast
/// the events.
/////////////////////////////////////////////////
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

  void OnSetCursorStateEvent(SetCursorStateEvent* _event);

private:
  GLFWwindow* m_windowHandle;
};

// ------------------------------------------------------------------------------

} // namespace input
} // namespace mage