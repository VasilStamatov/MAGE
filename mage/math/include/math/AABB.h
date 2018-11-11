#pragma once

#include "Mat.h"

namespace mage
{
namespace math
{

// ------------------------------------------------------------------------------

class AABB
{
public:
  AABB(Vec3f _min, Vec3f _max);

  // ------------------------------------------------------------------------------

  AABB Transform(const Mat4f& _transform) const;

  // ------------------------------------------------------------------------------

  AABB Expand(const Vec3f& _amt) const;

  // ------------------------------------------------------------------------------

  AABB MoveTo(const Vec3f& _destination) const;

  // ------------------------------------------------------------------------------

  bool Intersects(const AABB& _other) const;
  bool Contains(const Vec3f& _point) const;
  bool Contains(const AABB& _other) const;

  // ------------------------------------------------------------------------------

  AABB Translate(const Vec3f& _amt) const;
  AABB ScaleFromCenter(const Vec3f& _amt) const;
  AABB ScaleFromOrigin(const Vec3f& _amt) const;

  // ------------------------------------------------------------------------------

  AABB AddPoint(const Vec3f& _other) const;
  AABB AddAABB(const AABB& _other) const;

  // ------------------------------------------------------------------------------

  Vec3f GetCenter() const;
  Vec3f GetExtents() const;

  // ------------------------------------------------------------------------------

  bool operator==(const AABB& _other) const;
  bool operator!=(const AABB& _other) const;

  // ------------------------------------------------------------------------------

private:
  Vec3f m_minExtent;
  Vec3f m_maxExtent;
};

// ------------------------------------------------------------------------------

} // namespace math
} // namespace mage