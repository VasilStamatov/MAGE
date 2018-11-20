#include "physics/AABBCollisionSystem.h"

#include "ecs/World.h"
#include "ecs_common/TransformComponent.h"
#include "messaging/MessageBus.h"

namespace mage
{
namespace physics
{

// ------------------------------------------------------------------------------

AABBCollider::AABBCollider(math::AABB _AABB)
    : m_AABB(std::move(_AABB))
{
}

// ------------------------------------------------------------------------------

AABBCollisionSystem::AABBCollisionSystem()
{
  m_systemSignature.AddComponent<ecs::common::TransformComponent>();
  m_systemSignature.AddComponent<AABBCollider>();
}

// ------------------------------------------------------------------------------

void AABBCollisionSystem::Tick(ecs::World& _world, float _deltaTime)
{
  AABBIntersectionsEvent intersections;

  for (size_t firstE = 0; firstE < m_registeredEntities.size() - 1; firstE++)
  {
    auto& transformFirst = _world
                               .GetComponent<ecs::common::TransformComponent>(
                                   m_registeredEntities[firstE])
                               .m_transform;
    auto& colliderFirst =
        _world.GetComponent<AABBCollider>(m_registeredEntities[firstE]);

    for (size_t secondE = firstE + 1; secondE < m_registeredEntities.size();
         secondE++)
    {
      auto& transformSecond =
          _world
              .GetComponent<ecs::common::TransformComponent>(
                  m_registeredEntities[secondE])
              .m_transform;
      auto& colliderSecond =
          _world.GetComponent<AABBCollider>(m_registeredEntities[secondE]);

      math::AABB worldSpaceAABBFirst =
          colliderFirst.m_AABB.Transform(transformFirst.ToMatrix());
      math::AABB worldSpaceAABBSecond =
          colliderSecond.m_AABB.Transform(transformSecond.ToMatrix());

      if (worldSpaceAABBFirst.Intersects(worldSpaceAABBSecond))
      {
        intersections.m_entityIntersections.emplace_back(
            m_registeredEntities[firstE], m_registeredEntities[secondE]);
      }
    }
  }

  if (!intersections.m_entityIntersections.empty())
  {
    _world.GetApplicationMessageBus().Broadcast(&intersections);
  }
}

// ------------------------------------------------------------------------------

} // namespace physics
} // namespace mage