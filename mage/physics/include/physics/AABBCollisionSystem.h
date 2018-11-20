#pragma once

#include "ecs/GameSystem.h"
#include "math/AABB.h"

namespace mage
{
namespace physics
{

// ------------------------------------------------------------------------------

struct AABBCollider : public ecs::Component
{
  AABBCollider(math::AABB _AABB);

  math::AABB m_AABB;
};

// ------------------------------------------------------------------------------

class AABBCollisionSystem : public ecs::GameSystem
{
public:
  AABBCollisionSystem();

  virtual void Tick(ecs::World& _world, float _deltaTime) override;
};

// ------------------------------------------------------------------------------

struct AABBIntersectionsEvent
{
  std::vector<std::pair<ecs::Entity, ecs::Entity>> m_entityIntersections;
};

// ------------------------------------------------------------------------------

} // namespace physics
} // namespace mage