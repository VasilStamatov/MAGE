#pragma once

#include "AABBCollisionSystem.h"

namespace mage
{
namespace physics
{

// ------------------------------------------------------------------------------

/////////////////////////////////////////////////
/// This is a basic example of collision resolution system.
/////////////////////////////////////////////////
class BasicCollisionResolution : public PhysicsSystem
{
public:
  BasicCollisionResolution();

  virtual void Initialize(core::World& _world) override;

  virtual void Simulate(core::World& _world, float _deltaSeconds) override;

private:
  void OnCollisionEvent(AABBIntersectionsEvent* _event);

private:
  std::vector<std::pair<ecs::Entity, ecs::Entity>> m_entityIntersections;
};

// ------------------------------------------------------------------------------

} // namespace physics
} // namespace mage