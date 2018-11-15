#include "graphics/Camera.h"

namespace mage
{
namespace graphics
{

// ------------------------------------------------------------------------------

Camera::Camera(math::Mat4f _projection)
    : m_projection(std::move(_projection))
    , m_orientation()
    , m_position()
{
}

// ------------------------------------------------------------------------------

void Camera::Translate(const math::Vec3f& _translation)
{
  m_position -= _translation;
}

// ------------------------------------------------------------------------------

void Camera::Rotate(const math::Quatf& _rotation)
{
  m_orientation *= _rotation;
}

// ------------------------------------------------------------------------------

void Camera::SetPosition(const math::Vec3f _position)
{
  m_position = _position * -1;
}

// ------------------------------------------------------------------------------

void Camera::SetRotation(const math::Quatf& _orientation)
{
  m_orientation = _orientation;
}

// ------------------------------------------------------------------------------

math::Mat4f Camera::GetProjection() const { return m_projection; }

// ------------------------------------------------------------------------------

math::Mat4f Camera::GetView() const
{
  return m_orientation.ToMat4() * math::GenTranslationMat(m_position);
}

// ------------------------------------------------------------------------------

math::Vec3f Camera::GetRightAxis() const
{
  return math::Quatf::RotateVec(m_orientation.GetConjugated(),
                                math::Vec3f(1.0f, 0.0f, 0.0f));
}

// ------------------------------------------------------------------------------

math::Vec3f Camera::GetUpAxis() const { return math::Vec3f(0.0f, 1.0f, 0.0f); }

// ------------------------------------------------------------------------------

math::Vec3f Camera::GetForwardAxis() const
{
  return math::Quatf::RotateVec(m_orientation.GetConjugated(),
                                math::Vec3f(0.0f, 0.0f, -1.0f));
}

// ------------------------------------------------------------------------------

} // namespace graphics
} // namespace mage