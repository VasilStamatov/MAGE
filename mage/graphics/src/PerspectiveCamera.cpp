#include "graphics/PerspectiveCamera.h"

#include "messaging/MessageBus.h"
#include "video/Window.h"

namespace mage
{
namespace graphics
{

// ------------------------------------------------------------------------------

PerspectiveCamera::PerspectiveCamera(const math::Vec4i32& _viewport,
                                     float _fovDegrees, float _near, float _far)
    : m_projection(1.0f)
    , m_view(1.0f)
    , m_viewport(_viewport)
    , m_fovDegrees(_fovDegrees)
    , m_near(_near)
    , m_far(_far)
{
  m_projection = math::GenPerspectiveMat(
      mage::math::ToRadians(_fovDegrees),
      (float)_viewport[2] / (float)_viewport[3], _near, _far);
}

// ------------------------------------------------------------------------------

PerspectiveCamera::PerspectiveCamera(const math::Vec4i32& _viewport,
                                     float _fovDegrees, float _near, float _far,
                                     messaging::MessageBus& _msgBus)

    : m_projection(1.0f)
    , m_view(1.0f)
    , m_viewport(_viewport)
    , m_fovDegrees(_fovDegrees)
    , m_near(_near)
    , m_far(_far)
{
  m_projection = math::GenPerspectiveMat(
      mage::math::ToRadians(_fovDegrees),
      (float)_viewport[2] / (float)_viewport[3], _near, _far);

  _msgBus.Subscribe(this, &PerspectiveCamera::WindowFramebufferResizedHandler);
}

// ------------------------------------------------------------------------------

void PerspectiveCamera::SetView(math::Mat4f _view)
{
  m_view = std::move(_view);
}

// ------------------------------------------------------------------------------

math::Mat4f PerspectiveCamera::GetProjection() const { return m_projection; }

// ------------------------------------------------------------------------------

math::Mat4f PerspectiveCamera::GetView() const { return m_view; }

// ------------------------------------------------------------------------------

const math::Vec4i32& PerspectiveCamera::GetViewport() const
{
  return m_viewport;
}

// ------------------------------------------------------------------------------

void PerspectiveCamera::WindowFramebufferResizedHandler(
    video::OnWindowFramebufferResized* _event)
{
  m_viewport[2] = _event->m_width;
  m_viewport[3] = _event->m_height;

  m_projection = math::GenPerspectiveMat(
      mage::math::ToRadians(m_fovDegrees),
      (float)m_viewport[2] / (float)m_viewport[3], m_near, m_far);
}

} // namespace graphics
} // namespace mage