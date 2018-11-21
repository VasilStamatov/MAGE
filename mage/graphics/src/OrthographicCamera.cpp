#include "graphics/OrthographicCamera.h"

#include "messaging/MessageBus.h"
#include "video/Window.h"

namespace mage
{
namespace graphics
{

// ------------------------------------------------------------------------------

OrthographicCamera::OrthographicCamera(const math::Vec4i32& _viewport,
                                       float _near, float _far)
    : m_projection(1.0f)
    , m_view(1.0f)
    , m_viewport(_viewport)
    , m_near(_near)
    , m_far(_far)
{
  m_projection =
      math::GenOrthoMat((float)_viewport[0], (float)_viewport[2],
                        (float)_viewport[1], (float)_viewport[3], _near, _far);
}

// ------------------------------------------------------------------------------

OrthographicCamera::OrthographicCamera(const math::Vec4i32& _viewport,
                                       float _near, float _far,
                                       messaging::MessageBus& _msgBus)

    : m_projection(1.0f)
    , m_view(1.0f)
    , m_viewport(_viewport)
    , m_near(_near)
    , m_far(_far)
{
  m_projection =
      math::GenOrthoMat((float)_viewport[0], (float)_viewport[2],
                        (float)_viewport[1], (float)_viewport[3], _near, _far);

  _msgBus.Subscribe(this, &OrthographicCamera::WindowFramebufferResizedHandler);
}

// ------------------------------------------------------------------------------

void OrthographicCamera::SetView(math::Mat4f _view)
{
  m_view = std::move(_view);
}

// ------------------------------------------------------------------------------

math::Mat4f OrthographicCamera::GetProjection() const { return m_projection; }

// ------------------------------------------------------------------------------

math::Mat4f OrthographicCamera::GetView() const { return m_view; }

// ------------------------------------------------------------------------------

const math::Vec4i32& OrthographicCamera::GetViewport() const
{
  return m_viewport;
}

// ------------------------------------------------------------------------------

void OrthographicCamera::WindowFramebufferResizedHandler(
    video::OnWindowFramebufferResized* _event)
{
  m_viewport[2] = _event->m_width;
  m_viewport[3] = _event->m_height;

  m_projection = math::GenOrthoMat((float)m_viewport[0], (float)m_viewport[2],
                                   (float)m_viewport[1], (float)m_viewport[3],
                                   m_near, m_far);
}

} // namespace graphics
} // namespace mage