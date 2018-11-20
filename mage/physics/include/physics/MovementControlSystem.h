#pragma once

#include "ecs/GameSystem.h"
#include "input/InputManager.h"

namespace mage
{
namespace physics
{

// ------------------------------------------------------------------------------

struct MovementControls : public ecs::Component
{
  MovementControls() = default;
  MovementControls(input::InputKey _forwardKey, input::InputKey _backKey,
                   input::InputKey _rightKey, input::InputKey _leftKey);

  input::InputKey m_forwardKey = input::InputKey::W;
  input::InputKey m_backKey = input::InputKey::S;
  input::InputKey m_rightKey = input::InputKey::D;
  input::InputKey m_leftKey = input::InputKey::A;
};

// ------------------------------------------------------------------------------

class MovementControlSystem : public ecs::GameSystem
{
public:
  MovementControlSystem();

  virtual void Initialize(mage::ecs::World& _world) override;

  virtual void Tick(ecs::World& _world, float _deltaTime) override;

private:
  void OnKeyPress(mage::input::OnKeyPress* _event);
  void OnKeyRelease(mage::input::OnKeyRelease* _event);

private:
  std::vector<input::InputKey> m_pressedKeys;
};

// ------------------------------------------------------------------------------

} // namespace physics
} // namespace mage