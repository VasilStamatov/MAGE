#pragma once

#include "math/Quat.h"
#include "renderer/GLFramebuffer2D.h"

#include <memory>

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

/////////////////////////////////////////////////
/// A camera is used in the rendering systems update to render the scene from
/// the camera's perspective. The camera can potentially have a render target so
/// it doesn't render directly to the screen buffer.
/////////////////////////////////////////////////
class Camera
{
public:
  // Perspective
  Camera(const math::Vec4i32& _viewport, float _fovDegrees, float _near,
         float _far);
  Camera(const math::Vec4i32& _viewport, float _fovDegrees, float _near,
         float _far, messaging::MessageBus& _msgBus);

  // Ortho
  Camera(const math::Vec4i32& _viewport, float _near, float _far);
  Camera(const math::Vec4i32& _viewport, float _near, float _far,
         messaging::MessageBus& _msgBus);

  // ------------------------------------------------------------------------------

  void SetView(math::Mat4f _view);

  // ------------------------------------------------------------------------------

  math::Mat4f GetProjection() const;
  math::Mat4f GetView() const;

  // ------------------------------------------------------------------------------

  const math::Vec4i32& GetViewport() const;

  // ------------------------------------------------------------------------------

  void MakeRenderToTarget();
  void MakeRenderToTarget(std::uint32_t _width, std::uint32_t _height);

  // ------------------------------------------------------------------------------

  GLFramebuffer2D* GetRenderTarget() const;

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

  std::unique_ptr<GLFramebuffer2D> m_renderTarget;

  bool m_isOrtho;
};

// ------------------------------------------------------------------------------

} // namespace graphics
} // namespace mage