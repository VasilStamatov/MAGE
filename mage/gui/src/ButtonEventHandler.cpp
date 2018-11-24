#include "gui/ButtonEventhandler.h"

#include "ecs/World.h"
#include "gui/Button.h"
#include "messaging/MessageBus.h"

namespace mage
{
namespace gui
{

// ------------------------------------------------------------------------------

ButtonEventHandler::ButtonEventHandler()
{
  m_systemSignature.AddComponent<Button>();
  m_systemSignature.AddComponent<GUICallback>();
}

// ------------------------------------------------------------------------------

void ButtonEventHandler::Initialize(ecs::World& _world)
{
  auto& appMsgBus = _world.GetApplicationMessageBus();

  appMsgBus.Subscribe(this, &ButtonEventHandler::OnMouseMove);
  appMsgBus.Subscribe(this, &ButtonEventHandler::OnKeyPress);
  appMsgBus.Subscribe(this, &ButtonEventHandler::OnKeyRelease);

  // Ensure the cursor is enabled
  input::SetCursorStateEvent cursorState{input::CursorState::Visible};

  appMsgBus.Broadcast(&cursorState);
}

// ------------------------------------------------------------------------------

void ButtonEventHandler::Tick(ecs::World& _world, float _deltaTime)
{
  for (auto&& entity : m_registeredEntities)
  {
    auto& button = _world.GetComponent<Button>(entity);
    auto& callback = _world.GetComponent<GUICallback>(entity);

    int xMin = button.m_screenPos[0];
    int yMin = button.m_screenPos[1];

    int xMax = button.m_screenPos[0] + button.m_size[0];
    int yMax = button.m_screenPos[1] + button.m_size[1];

    const bool insideX = m_lastMouseX > xMin && m_lastMouseX < xMax;
    const bool insideY = m_lastMouseY > yMin && m_lastMouseY < yMax;

    if (insideX && insideY && m_leftMouseButtonClicked)
    {
      m_leftMouseButtonClicked = false;
      callback.m_onClickCallback();
    }
  }
}

// ------------------------------------------------------------------------------

void ButtonEventHandler::OnMouseMove(input::CursorPositionMovedEvent* _event)
{
  m_lastMouseX = _event->m_xPos;
  m_lastMouseY = _event->m_yPos;
}

// ------------------------------------------------------------------------------

void ButtonEventHandler::OnKeyPress(input::OnKeyPress* _event)
{
  if (_event->m_key == input::InputKey::LeftMouseButton)
  {
    m_leftMouseButtonClicked = true;
  }
}

// ------------------------------------------------------------------------------

void ButtonEventHandler::OnKeyRelease(input::OnKeyRelease* _event)
{
  if (_event->m_key == input::InputKey::LeftMouseButton)
  {
    m_leftMouseButtonClicked = false;
  }
}

// ------------------------------------------------------------------------------

} // namespace gui
} // namespace mage