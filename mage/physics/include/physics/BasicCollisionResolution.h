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
class BasicCollisionResolution : public ecs::GameSystem
{
public:
  BasicCollisionResolution();

  virtual void Initialize(mage::ecs::World& _world) override;

  virtual void Tick(ecs::World& _world, float _deltaTime) override;

private:
  void OnCollisionEvent(AABBIntersectionsEvent* _event);

private:
  std::vector<std::pair<ecs::Entity, ecs::Entity>> m_entityIntersections;
};

// ------------------------------------------------------------------------------

} // namespace physics
} // namespace mage