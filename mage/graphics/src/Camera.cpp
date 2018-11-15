#include "graphics/Camera.h"

namespace mage
{
namespace graphics
{

// ------------------------------------------------------------------------------

Camera::Camera(math::Mat4f _projection)
    : m_projection(std::move(_projection))
    , m_transform()
{
}

// ------------------------------------------------------------------------------

void Camera::Translate(const math::Vec3f& _translation)
{
  m_transform.Translate(_translation * -1);
}

// ------------------------------------------------------------------------------

void Camera::Rotate(const math::Quatf& _rotation)
{
  m_transform.Rotate(_rotation);
}

// ------------------------------------------------------------------------------

void Camera::SetPosition(const math::Vec3f _position)
{
  m_transform.SetTranslation(_position * -1);
}

// ------------------------------------------------------------------------------

void Camera::SetRotation(const math::Quatf& _orientation)
{
  m_transform.SetRotation(_orientation);
}

// ------------------------------------------------------------------------------

math::Mat4f Camera::GetProjection() const { return m_projection; }

// ------------------------------------------------------------------------------

math::Mat4f Camera::GetView() const { return m_transform.ToMatrix(); }

// ------------------------------------------------------------------------------

math::Vec3f Camera::GetRightAxis() const { return m_transform.GetRightAxis(); }

// ------------------------------------------------------------------------------

math::Vec3f Camera::GetUpAxis() const { return m_transform.GetUpAxis(); }

// ------------------------------------------------------------------------------

math::Vec3f Camera::GetForwardAxis() const
{
  return m_transform.GetForwardAxis();
}

// ------------------------------------------------------------------------------

} // namespace graphics
} // namespace mage