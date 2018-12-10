#pragma once

#include "ecs/GameSystem.h"
#include "input/InputManager.h"

namespace mage
{
namespace gui
{

// ------------------------------------------------------------------------------

/////////////////////////////////////////////////
/// Systems which keeps track of all gui to check if one is pressed.
/////////////////////////////////////////////////
class ButtonEventHandler : public ecs::GameSystem
{
public:
  ButtonEventHandler();

  virtual void Initialize(core::World& _world) override;

  virtual void Tick(core::World& _world, float _deltaSeconds) override;

private:
  void OnMouseMove(input::CursorPositionMovedEvent* _event);
  void OnKeyPress(input::OnKeyPress* _event);
  void OnKeyRelease(input::OnKeyRelease* _event);

private:
  float m_lastMouseX = 0.0f;
  float m_lastMouseY = 0.0f;
  bool m_leftMouseButtonClicked = false;
};

// ------------------------------------------------------------------------------

} // namespace gui
} // namespace mage