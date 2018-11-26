#pragma once

#include "ecs/GameSystem.h"
#include "math/AABB.h"

namespace mage
{
namespace physics
{

// ------------------------------------------------------------------------------

/////////////////////////////////////////////////
/// AABB Collider component stores the AABB data of an entity.
/////////////////////////////////////////////////
struct AABBCollider : public ecs::Component
{
  AABBCollider(math::AABB _AABB);

  math::AABB m_AABB;
};

// ------------------------------------------------------------------------------

/////////////////////////////////////////////////
/// AABB Collision system checks for intersections between all entities with an
/// AABB component and a transform.
/////////////////////////////////////////////////
class AABBCollisionSystem : public ecs::GameSystem
{
public:
  AABBCollisionSystem();

  virtual void Tick(ecs::World& _world, float _deltaTime) override;
};

// ------------------------------------------------------------------------------

/////////////////////////////////////////////////
/// Event broadcasted with all intersections that happaned that frame
/////////////////////////////////////////////////
struct AABBIntersectionsEvent
{
  std::vector<std::pair<ecs::Entity, ecs::Entity>> m_entityIntersections;
};

// ------------------------------------------------------------------------------

} // namespace physics
} // namespace mage