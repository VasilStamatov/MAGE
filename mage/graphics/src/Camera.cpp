#include "graphics/Camera.h"

namespace mage
{
namespace graphics
{

// ------------------------------------------------------------------------------

Camera::Camera(math::Mat4f _projection)
    : m_projection(std::move(_projection))
    , m_view()
{
}

// ------------------------------------------------------------------------------

math::Mat4f Camera::GetProjection() const { return m_projection; }

// ------------------------------------------------------------------------------

math::Mat4f Camera::GetView() const { return m_view; }

// ------------------------------------------------------------------------------

void Camera::SetProjection(math::Mat4f _proj)
{
  m_projection = std::move(_proj);
}

// ------------------------------------------------------------------------------

void Camera::SetView(math::Mat4f _view) { m_view = std::move(_view); }

// ------------------------------------------------------------------------------

} // namespace graphics
} // namespace mage