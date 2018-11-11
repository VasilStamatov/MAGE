#include "math/AABB.h"

#include "math/MathUtils.h"

namespace mage
{
namespace math
{

// ------------------------------------------------------------------------------

AABB::AABB(Vec3f _min, Vec3f _max)
    : m_minExtent(_min)
    , m_maxExtent(_max)
{
}

// ------------------------------------------------------------------------------

// Transform all 8 points of the AABB and choose new min/max
AABB AABB::Transform(const Mat4f& _transform) const
{
  // Get the 8 points from the min and max extents
  // m_minExtent = bottom left behind
  // m_maxExtent = top right front

  Vec4f bottomLeftBehind =
      Vec4f(m_minExtent[0], m_minExtent[1], m_minExtent[2], 1.0f);

  Vec4f topRightFront =
      Vec4f(m_maxExtent[0], m_maxExtent[1], m_maxExtent[2], 1.0f);

  Vec4f bottomRightBehind =
      Vec4f(m_maxExtent[0], m_minExtent[1], m_minExtent[2], 1.0f);

  Vec4f bottomRightFront =
      Vec4f(m_maxExtent[0], m_minExtent[1], m_maxExtent[2], 1.0f);

  Vec4f TopRightBehind =
      Vec4f(m_maxExtent[0], m_maxExtent[1], m_minExtent[2], 1.0f);

  Vec4f TopLeftBehind =
      Vec4f(m_minExtent[0], m_minExtent[1], m_minExtent[2], 1.0f);

  Vec4f TopLeftFront =
      Vec4f(m_minExtent[0], m_maxExtent[1], m_maxExtent[2], 1.0f);

  Vec4f bottomLeftFront =
      Vec4f(m_minExtent[0], m_minExtent[1], m_maxExtent[2], 1.0f);

  // Now transform all points

  bottomLeftBehind = _transform * bottomLeftBehind;
  topRightFront = _transform * topRightFront;
  bottomRightBehind = _transform * bottomRightBehind;
  bottomRightFront = _transform * bottomRightFront;
  TopRightBehind = _transform * TopRightBehind;
  TopLeftBehind = _transform * TopLeftBehind;
  TopLeftFront = _transform * TopLeftFront;
  bottomLeftFront = _transform * bottomLeftFront;

  // Recalc the min/max points and construct new AABB
  Vec4f min = GetMinValues(
      GetMinValues(
          GetMinValues(
              GetMinValues(
                  GetMinValues(GetMinValues(GetMinValues(bottomLeftBehind,
                                                         topRightFront),
                                            bottomRightBehind),
                               bottomRightFront),
                  TopRightBehind),
              TopLeftBehind),
          TopLeftFront),
      bottomLeftFront);

  Vec4f max = GetMinValues(
      GetMinValues(
          GetMinValues(
              GetMinValues(
                  GetMinValues(GetMinValues(GetMinValues(bottomLeftBehind,
                                                         topRightFront),
                                            bottomRightBehind),
                               bottomRightFront),
                  TopRightBehind),
              TopLeftBehind),
          TopLeftFront),
      bottomLeftFront);

  return AABB(Vec3f(min[0], min[1], min[2]), Vec3f(max[0], max[1], max[2]));
}

// ------------------------------------------------------------------------------

AABB AABB::Expand(const Vec3f& _amt) const
{
  return AABB(m_minExtent - _amt, m_maxExtent + _amt);
}

// ------------------------------------------------------------------------------

AABB AABB::MoveTo(const Vec3f& _destination) const
{
  return Translate(_destination - GetCenter());
}

// ------------------------------------------------------------------------------

bool AABB::Intersects(const AABB& _other) const
{
  return (m_maxExtent >= _other.m_minExtent) &&
         (m_minExtent <= _other.m_maxExtent);
}

// ------------------------------------------------------------------------------

bool AABB::Contains(const Vec3f& _point) const
{
  return (_point >= m_minExtent) && (_point <= m_maxExtent);
}

// ------------------------------------------------------------------------------

bool AABB::Contains(const AABB& _other) const
{
  return (_other.m_minExtent >= m_minExtent) &&
         (_other.m_maxExtent <= m_maxExtent);
}

// ------------------------------------------------------------------------------

AABB AABB::Translate(const Vec3f& _amt) const
{
  return AABB(m_minExtent + _amt, m_maxExtent + _amt);
}

// ------------------------------------------------------------------------------

AABB AABB::ScaleFromCenter(const Vec3f& _amt) const
{
  const Vec3f center = GetCenter();
  const Vec3f scaledExtents = GetExtents() * _amt;
  return AABB(center - scaledExtents, center + scaledExtents);
}

// ------------------------------------------------------------------------------

AABB AABB::ScaleFromOrigin(const Vec3f& _amt) const
{
  return AABB(m_minExtent * _amt, m_maxExtent * _amt);
}

// ------------------------------------------------------------------------------

AABB AABB::AddPoint(const Vec3f& _other) const
{
  return AABB(GetMinValues(m_minExtent, _other),
              GetMaxValues(m_maxExtent, _other));
}

// ------------------------------------------------------------------------------

AABB AABB::AddAABB(const AABB& _other) const
{
  return AABB(GetMinValues(m_minExtent, _other.m_minExtent),
              GetMaxValues(m_maxExtent, _other.m_maxExtent));
}

// ------------------------------------------------------------------------------

Vec3f AABB::GetCenter() const { return (m_minExtent + m_maxExtent) * 0.5f; }

// ------------------------------------------------------------------------------

Vec3f AABB::GetExtents() const { return (m_maxExtent - m_minExtent) * 0.5f; }

// ------------------------------------------------------------------------------

bool AABB::operator==(const AABB& _other) const
{
  return m_minExtent == _other.m_minExtent && m_maxExtent == _other.m_maxExtent;
}

// ------------------------------------------------------------------------------

bool AABB::operator!=(const AABB& _other) const
{
  return m_minExtent != _other.m_minExtent && m_maxExtent != _other.m_maxExtent;
}

// ------------------------------------------------------------------------------

} // namespace math
} // namespace mage