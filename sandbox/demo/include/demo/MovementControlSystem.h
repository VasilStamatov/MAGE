#pragma once

#include <ecs/GameSystem.h>
#include <input/InputManager.h>

// ------------------------------------------------------------------------------

struct MovementControls : public mage::ecs::Component
{
  MovementControls() = default;
  MovementControls(mage::input::InputKey _rightKey,
                   mage::input::InputKey _leftKey);

  mage::input::InputKey m_rightKey = mage::input::InputKey::D;
  mage::input::InputKey m_leftKey = mage::input::InputKey::A;
};

// ------------------------------------------------------------------------------

class MovementControlSystem : public mage::ecs::GameSystem
{
public:
  MovementControlSystem();

  virtual void Initialize(mage::ecs::World& _world) override;

  virtual void Tick(mage::ecs::World& _world, float _deltaTime) override;

private:
  void OnKeyPress(mage::input::OnKeyPress* _event);
  void OnKeyRelease(mage::input::OnKeyRelease* _event);

private:
  std::vector<mage::input::InputKey> m_pressedKeys;
};

// ------------------------------------------------------------------------------
