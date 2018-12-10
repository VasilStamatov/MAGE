#include "physics/MotionIntegrators.h"

namespace mage
{
namespace physics
{
namespace MotionIntegrators
{

// ------------------------------------------------------------------------------

void Verlet(math::Vec3f& _pos, math::Vec3f& _velocity,
            const math::Vec3f& _acceleration, float _deltaSeconds)
{
  float halfDelta = _deltaSeconds * 0.5f;
  _pos += _velocity * halfDelta;
  _velocity += _acceleration * _deltaSeconds;
  _pos += _velocity * halfDelta;
}

// ------------------------------------------------------------------------------

void ForestRuth(math::Vec3f& _pos, math::Vec3f& _velocity,
                const math::Vec3f& _acceleration, float _deltaSeconds)
{
  static const float frCoefficient =
      1.0f / (2.0f - math::Pow(2.0f, 1.0f / 3.0f));
  static const float frComplement = 1.0f - 2.0f * frCoefficient;
  Verlet(_pos, _velocity, _acceleration, _deltaSeconds * frCoefficient);
  Verlet(_pos, _velocity, _acceleration, _deltaSeconds * frComplement);
  Verlet(_pos, _velocity, _acceleration, _deltaSeconds * frCoefficient);
}

// ------------------------------------------------------------------------------

void ModifiedEuler(math::Vec3f& _pos, math::Vec3f& _velocity,
                   const math::Vec3f& _acceleration, float _deltaSeconds)
{
  _velocity += _acceleration * _deltaSeconds;
  _pos += _velocity * _deltaSeconds;
}

// ------------------------------------------------------------------------------

} // namespace MotionIntegrators
} // namespace physics
} // namespace mage