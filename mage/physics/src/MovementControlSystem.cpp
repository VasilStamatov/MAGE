#include "physics/MovementControlSystem.h"

#include "ecs/World.h"
#include "messaging/MessageBus.h"
#include "physics/MotionSystem.h"

namespace mage
{
namespace physics
{

// ------------------------------------------------------------------------------

MovementControls::MovementControls(input::InputKey _forwardKey,
                                   input::InputKey _backKey,
                                   input::InputKey _rightKey,
                                   input::InputKey _leftKey)
    : m_forwardKey(std::move(_forwardKey))
    , m_backKey(std::move(_backKey))
    , m_rightKey(std::move(_rightKey))
    , m_leftKey(std::move(_leftKey))
{
}

// ------------------------------------------------------------------------------

MovementControlSystem::MovementControlSystem()
{
  m_systemSignature.AddComponent<Motion>();
  m_systemSignature.AddComponent<MovementControls>();
}

// ------------------------------------------------------------------------------

void MovementControlSystem::Initialize(mage::ecs::World& _world)
{
  auto& appMsgBus = _world.GetApplicationMessageBus();

  appMsgBus.Subscribe(this, &MovementControlSystem::OnKeyPress);
  appMsgBus.Subscribe(this, &MovementControlSystem::OnKeyRelease);
}

// ------------------------------------------------------------------------------

void MovementControlSystem::Tick(ecs::World& _world, float _deltaTime)
{
  for (auto&& entity : m_registeredEntities)
  {
    auto& movementControls = _world.GetComponent<MovementControls>(entity);
    auto& motion = _world.GetComponent<Motion>(entity);

    for (auto&& key : m_pressedKeys)
    {
      if (key == movementControls.m_forwardKey)
      {
        motion.m_acceleration += math::Vec3f(0.0f, 0.0f, -0.001f);
      }
      else if (key == movementControls.m_backKey)
      {
        motion.m_acceleration += math::Vec3f(0.0f, 0.0f, 0.001f);
      }
      else if (key == movementControls.m_rightKey)
      {
        motion.m_acceleration += math::Vec3f(0.001f, 0.0f, 0.0f);
      }
      else if (key == movementControls.m_leftKey)
      {
        motion.m_acceleration += math::Vec3f(-0.001f, 0.0f, 0.0f);
      }
    }
  }
}

// ------------------------------------------------------------------------------

void MovementControlSystem::OnKeyPress(mage::input::OnKeyPress* _event)
{
  m_pressedKeys.push_back(_event->m_key);
}

// ------------------------------------------------------------------------------

void MovementControlSystem::OnKeyRelease(mage::input::OnKeyRelease* _event)
{
  m_pressedKeys.erase(
      std::find(m_pressedKeys.begin(), m_pressedKeys.end(), _event->m_key));
}

// ------------------------------------------------------------------------------

} // namespace physics
} // namespace mage