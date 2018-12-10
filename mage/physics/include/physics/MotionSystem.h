#pragma once

#include "PhysicsSystem.h"
#include "math/Vec.h"

namespace mage
{
namespace physics
{

// ------------------------------------------------------------------------------

/////////////////////////////////////////////////
/// The motion component described the ability of an entity to move with
/// velocity and acceleration.
/////////////////////////////////////////////////
struct Motion : public ecs::Component
{
  math::Vec3f m_velocity;
  math::Vec3f m_acceleration;
};

// ------------------------------------------------------------------------------

/////////////////////////////////////////////////
/// The motion system applies movement integration to all entities with motion
/// and a transform.
/////////////////////////////////////////////////
class MotionSystem : public PhysicsSystem
{
public:
  MotionSystem();

  virtual void Simulate(core::World& _world, float _deltaSeconds) override;
};

// ------------------------------------------------------------------------------

} // namespace physics
} // namespace mage