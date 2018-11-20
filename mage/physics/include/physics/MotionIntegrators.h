#pragma once

#include "math/MathUtils.h"
#include "math/Vec.h"

namespace mage
{
namespace physics
{
namespace MotionIntegrators
{

// ------------------------------------------------------------------------------

void Verlet(math::Vec3f& _pos, math::Vec3f& _velocity,
            const math::Vec3f& _acceleration, float _delta);

// ------------------------------------------------------------------------------

void ForestRuth(math::Vec3f& _pos, math::Vec3f& _velocity,
                const math::Vec3f& _acceleration, float _delta);

// ------------------------------------------------------------------------------

void ModifiedEuler(math::Vec3f& _pos, math::Vec3f& _velocity,
                   const math::Vec3f& _acceleration, float _delta);

// ------------------------------------------------------------------------------

} // namespace MotionIntegrators
} // namespace physics
} // namespace mage