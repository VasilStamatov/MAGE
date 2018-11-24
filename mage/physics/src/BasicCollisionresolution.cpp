#include "physics/BasicCollisionResolution.h"

#include "ecs/World.h"
#include "ecs_common/TransformComponent.h"
#include "messaging/MessageBus.h"
#include "physics/MotionSystem.h"

namespace mage
{
namespace physics
{

// ------------------------------------------------------------------------------

BasicCollisionResolution::BasicCollisionResolution() {}

// ------------------------------------------------------------------------------

void BasicCollisionResolution::Initialize(mage::ecs::World& _world)
{
  auto& appMsgBus = _world.GetApplicationMessageBus();

  appMsgBus.Subscribe(this, &BasicCollisionResolution::OnCollisionEvent);
}

// ------------------------------------------------------------------------------

void BasicCollisionResolution::Tick(ecs::World& _world, float _deltaTime)
{
  for (auto&& intersections : m_entityIntersections)
  {
    auto& motionA = _world.GetComponent<Motion>(intersections.first);
    // auto& motionB = _world.GetComponent<Motion>(intersections.second);

    // motionB.m_acceleration = motionA.m_acceleration;
    // motionB.m_velocity = motionA.m_velocity;

    motionA.m_acceleration *= -1;
    motionA.m_velocity *= -1.1f;
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