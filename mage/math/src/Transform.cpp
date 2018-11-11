#include "math/Transform.h"

namespace mage
{
namespace math
{

// ------------------------------------------------------------------------------

Transform::Transform()
    : m_rotation()
    , m_translation()
    , m_scale()
{
}

// ------------------------------------------------------------------------------

void Transform::Rotate(const Vec3f& _eulerAnglesRadians)
{
  Quatf toRotate(_eulerAnglesRadians);

  m_rotation = (toRotate * m_rotation).GetNormalized();
}

// ------------------------------------------------------------------------------

void Transform::Rotate(const Vec3f& _axis, float _angleRad)
{
  Quatf toRotate = Quatf::GenRotation(_angleRad, _axis);

  m_rotation = (toRotate * m_rotation).GetNormalized();
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

Vec3f Transform::GetRightAxis() const noexcept
{
  return Quatf::RotateVec(m_rotation, Vec3f(1.0f, 0.0f, 0.0f));
}

// ------------------------------------------------------------------------------

Vec3f Transform::GetUpAxis() const noexcept
{
  return Quatf::RotateVec(m_rotation, Vec3f(0.0f, 1.0f, 0.0f));
}

// ------------------------------------------------------------------------------

Vec3f Transform::GetForwardAxis() const noexcept
{
  return Quatf::RotateVec(m_rotation, Vec3f(0.0f, 0.0f, -1.0f));
}

// ------------------------------------------------------------------------------

Mat4f Transform::ToMatrix() const
{
  float x2 = m_rotation[0] + m_rotation[0];
  float y2 = m_rotation[1] + m_rotation[1];
  float z2 = m_rotation[2] + m_rotation[2];

  float xx2 = m_rotation[0] * x2;
  float yy2 = m_rotation[1] * y2;
  float zz2 = m_rotation[2] * z2;
  float xy2 = m_rotation[0] * y2;
  float yz2 = m_rotation[1] * z2;
  float xz2 = m_rotation[0] * z2;
  float xw2 = m_rotation[3] * x2;
  float yw2 = m_rotation[3] * y2;
  float zw2 = m_rotation[3] * z2;

  float s0 = m_scale[0];
  float s1 = m_scale[1];
  float s2 = m_scale[2];

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