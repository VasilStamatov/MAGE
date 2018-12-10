#include "physics/BasicCollisionResolution.h"

#include "core/Application.h"
#include "ecs_common/TransformComponent.h"
#include "physics/MotionSystem.h"

namespace mage
{
namespace physics
{

// ------------------------------------------------------------------------------

BasicCollisionResolution::BasicCollisionResolution() {}

// ------------------------------------------------------------------------------

void BasicCollisionResolution::Initialize(core::World& _world)
{
  auto& appMsgBus = _world.GetApplication().GetMessageBus();

  appMsgBus.Subscribe(this, &BasicCollisionResolution::OnCollisionEvent);
}

// ------------------------------------------------------------------------------

void BasicCollisionResolution::Simulate(core::World& _world,
                                        float _deltaSeconds)
{
  for (auto&& intersections : m_entityIntersections)
  {
    auto* motionA = _world.GetComponent<Motion>(intersections.first);
    auto* motionB = _world.GetComponent<Motion>(intersections.second);

    if (motionB && motionA)
    {
      motionB->m_acceleration = motionA->m_acceleration;
      motionB->m_velocity = motionA->m_velocity;
    }
    else if (motionB)
    {
      motionB->m_acceleration *= -1;
      motionB->m_velocity *= -1.1f;
    }

    if (motionA)
    {
      motionA->m_acceleration *= -1;
      motionA->m_velocity *= -1.1f;
    }
  }

  m_entityIntersections.clear();
}

// ------------------------------------------------------------------------------

void BasicCollisionResolution::OnCollisionEvent(AABBIntersectionsEvent* _event)
{
  m_entityIntersections = _event->m_entityIntersections;
}

// ------------------------------------------------------------------------------

} // namespace physics
} // namespace mage