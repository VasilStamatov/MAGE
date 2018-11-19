#pragma once

#include "math/Quat.h"

namespace mage
{
namespace graphics
{

// ------------------------------------------------------------------------------

class Camera
{
public:
  Camera(math::Mat4f _projection);

  // ------------------------------------------------------------------------------

  math::Mat4f GetProjection() const;
  math::Mat4f GetView() const;

  // ------------------------------------------------------------------------------

  void SetProjection(math::Mat4f _proj);
  void SetView(math::Mat4f _view);

private:
  math::Mat4f m_projection;
  math::Mat4f m_view;
};

// ------------------------------------------------------------------------------

} // namespace graphics
} // namespace mage