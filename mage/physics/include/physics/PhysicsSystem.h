#pragma once

#include "ecs/System.h"

namespace mage
{
namespace physics
{

// ------------------------------------------------------------------------------

class PhysicsSystem : public ecs::System
{
public:
  virtual ~PhysicsSystem() {}

  virtual void Initialize(core::World& _world) {}
  virtual void Uninitialize(core::World& _world) {}

  virtual void Simulate(core::World& _world, float _deltaSeconds) = 0;
};

// ------------------------------------------------------------------------------

} // namespace physics
} // namespace mage