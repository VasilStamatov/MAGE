#pragma once

#include "ecs/GameSystem.h"
#include "math/Vec.h"

namespace mage
{
namespace physics
{

// ------------------------------------------------------------------------------

struct Motion : public ecs::Component
{
  math::Vec3f m_velocity;
  math::Vec3f m_acceleration;
};

// ------------------------------------------------------------------------------

class MotionSystem : public ecs::GameSystem
{
public:
  MotionSystem();

  virtual void Tick(ecs::World& _world, float _deltaTime) override;
};

// ------------------------------------------------------------------------------

} // namespace physics
} // namespace mage