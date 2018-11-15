#include "math/Transform.h"

namespace mage
{
namespace math
{

// ------------------------------------------------------------------------------

Transform::Transform()
    : m_rotation()
    , m_translation()
    , m_scale(1.0f)
{
}

// ------------------------------------------------------------------------------

void Transform::Rotate(const Quatf& _amountToRotation)
{
  m_rotation = _amountToRotation * m_rotation;
}

// ------------------------------------------------------------------------------

void Transform::Translate(const Vec3f& _translation)
{
  m_translation += _translation;
}

// ------------------------------------------------------------------------------

void Transform::Scale(const Vec3f& _scalingToAdd) { m_scale += _scalingToAdd; }

// ------------------------------------------------------------------------------

void Transform::SetRotation(const Quatf& _rotation) { m_rotation = _rotation; }

// ------------------------------------------------------------------------------

void Transform::SetTranslation(const Vec3f& _translation)
{
  m_translation = _translation;
}

// ------------------------------------------------------------------------------

void Transform::SetScale(const Vec3f& _scale) { m_scale = _scale; }

// ------------------------------------------------------------------------------

Quatf Transform::GetRotation() const { return m_rotation; }

// ------------------------------------------------------------------------------

Vec3f Transform::GetTranslation() const { return m_translation; }

// ------------------------------------------------------------------------------

Vec3f Transform::GetScale() const { return m_scale; }

// ------------------------------------------------------------------------------

Vec3f Transform::GetRightAxis() const
{
  return Quatf::RotateVec(m_rotation, Vec3f(1.0f, 0.0f, 0.0f));
}

// ------------------------------------------------------------------------------

Vec3f Transform::GetUpAxis() const
{
  return Quatf::RotateVec(m_rotation, Vec3f(0.0f, 1.0f, 0.0f));
}

// ------------------------------------------------------------------------------

Vec3f Transform::GetForwardAxis() const
{
  return Quatf::RotateVec(m_rotation, Vec3f(0.0f, 0.0f, -1.0f));
}

// ------------------------------------------------------------------------------

Mat4f Transform::ToMatrix() const
{
  const float x2 = m_rotation[0] + m_rotation[0];
  const float y2 = m_rotation[1] + m_rotation[1];
  const float z2 = m_rotation[2] + m_rotation[2];

  const float xx2 = m_rotation[0] * x2;
  const float yy2 = m_rotation[1] * y2;
  const float zz2 = m_rotation[2] * z2;
  const float xy2 = m_rotation[0] * y2;
  const float yz2 = m_rotation[1] * z2;
  const float xz2 = m_rotation[0] * z2;
  const float xw2 = m_rotation[3] * x2;
  const float yw2 = m_rotation[3] * y2;
  const float zw2 = m_rotation[3] * z2;

  const float s0 = m_scale[0];
  const float s1 = m_scale[1];
  const float s2 = m_scale[2];

  float matrixData[16] = {(1.0f - (yy2 + zz2)) * s0,
                          (xy2 - zw2) * s1,
                          (xz2 + yw2) * s2,
                          m_translation[0],
                          (xy2 + zw2) * s0,
                          (1.0f - (xx2 + zz2)) * s1,
                          (yz2 - xw2) * s2,
                          m_translation[1],
                          (xz2 - yw2) * s0,
                          (yz2 + xw2) * s1,
                          (1.0f - (xx2 + yy2)) * s2,
                          m_translation[2],
                          0.0f,
                          0.0f,
                          0.0f,
                          1.0f};

  return Mat4f(matrixData);
}

// ------------------------------------------------------------------------------

} // namespace math
} // namespace mage