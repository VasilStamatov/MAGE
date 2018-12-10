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

/////////////////////////////////////////////////
/// Verlet motion integrator https://en.wikipedia.org/wiki/Verlet_integration
/////////////////////////////////////////////////
void Verlet(math::Vec3f& _pos, math::Vec3f& _velocity,
            const math::Vec3f& _acceleration, float _deltaSeconds);

// ------------------------------------------------------------------------------

/////////////////////////////////////////////////
/// Forest Ruth motion intefgator
/// https://en.wikipedia.org/wiki/Verlet_integration
/////////////////////////////////////////////////
void ForestRuth(math::Vec3f& _pos, math::Vec3f& _velocity,
                const math::Vec3f& _acceleration, float _deltaSeconds);

// ------------------------------------------------------------------------------

/////////////////////////////////////////////////
/// Modified euler integration
/// https://gafferongames.com/post/integration_basics/
/////////////////////////////////////////////////
void ModifiedEuler(math::Vec3f& _pos, math::Vec3f& _velocity,
                   const math::Vec3f& _acceleration, float _deltaSeconds);

// ------------------------------------------------------------------------------

} // namespace MotionIntegrators
} // namespace physics
} // namespace mage