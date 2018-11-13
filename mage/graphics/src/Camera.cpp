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

math::Mat4f Camera::GetProjection() const { return m_projection; }

// ------------------------------------------------------------------------------

math::Mat4f Camera::GetView() const { return m_transform.ToMatrix(); }

// ------------------------------------------------------------------------------

void Camera::Translate(const math::Vec3f& _translation)
{
  m_transform.Translate(_translation * -1);
}

// ------------------------------------------------------------------------------

void Camera::Rotate(const math::Vec3f& _axis, float _angleRad)
{
  m_transform.Rotate(_axis, _angleRad * -1);
}

// ------------------------------------------------------------------------------

void Camera::SetPosition(const math::Vec3f _position)
{
  m_transform.SetTranslation(_position * -1);
}

// ------------------------------------------------------------------------------

void Camera::SetRotation(const math::Vec3f& _axis, float _angleRad)
{
  m_transform.SetRotation(math::Quatf::GenRotation(_angleRad * -1, _axis));
}

// ------------------------------------------------------------------------------

} // namespace graphics
} // namespace mage