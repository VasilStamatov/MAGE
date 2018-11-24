#pragma once

#include "ecs/GameSystem.h"
#include "input/InputManager.h"

namespace mage
{
namespace gui
{

// ------------------------------------------------------------------------------

class ButtonEventHandler : public ecs::GameSystem
{
public:
  ButtonEventHandler();

  virtual void Initialize(ecs::World& _world) override;

  virtual void Tick(ecs::World& _world, float _deltaTime) override;

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