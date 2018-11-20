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

const Quatf& Transform::GetRotation() const { return m_rotation; }

// ------------------------------------------------------------------------------

const Vec3f& Transform::GetTranslation() const { return m_translation; }

// ------------------------------------------------------------------------------

const Vec3f& Transform::GetScale() const { return m_scale; }

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
  return GenTranslationMat(m_translation) * m_rotation.ToMat4() *
         GenScalingMat(m_scale);
}

// ------------------------------------------------------------------------------

} // namespace math
} // namespace mage