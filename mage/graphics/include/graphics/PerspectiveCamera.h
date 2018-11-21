#pragma once

#include "math/Quat.h"

namespace mage
{

namespace video
{
struct OnWindowFramebufferResized;
}

namespace messaging
{
class MessageBus;
}

namespace graphics
{

// ------------------------------------------------------------------------------

class PerspectiveCamera
{
public:
  PerspectiveCamera(const math::Vec4i32& _viewport, float _fovDegrees,
                    float _near, float _far);
  PerspectiveCamera(const math::Vec4i32& _viewport, float _fovDegrees,
                    float _near, float _far, messaging::MessageBus& _msgBus);

  // ------------------------------------------------------------------------------

  void SetView(math::Mat4f _view);

  // ------------------------------------------------------------------------------

  math::Mat4f GetProjection() const;
  math::Mat4f GetView() const;

  // ------------------------------------------------------------------------------

  const math::Vec4i32& GetViewport() const;

private:
  void
  WindowFramebufferResizedHandler(video::OnWindowFramebufferResized* _event);

private:
  math::Mat4f m_projection;
  math::Mat4f m_view;

  math::Vec4i32 m_viewport;
  float m_fovDegrees;
  float m_near;
  float m_far;
};

// ------------------------------------------------------------------------------

} // namespace graphics
} // namespace mage