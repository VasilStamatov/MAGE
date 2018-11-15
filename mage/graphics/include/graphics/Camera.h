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

  void Translate(const math::Vec3f& _translation);
  void Rotate(const math::Quatf& _rotation);

  // ------------------------------------------------------------------------------

  void SetPosition(const math::Vec3f _position);
  void SetRotation(const math::Quatf& _orientation);

  // ------------------------------------------------------------------------------

  math::Mat4f GetProjection() const;
  math::Mat4f GetView() const;

  // ------------------------------------------------------------------------------

  math::Vec3f GetRightAxis() const;
  math::Vec3f GetUpAxis() const;
  math::Vec3f GetForwardAxis() const;

  // ------------------------------------------------------------------------------

private:
  math::Mat4f m_projection;
  math::Quatf m_orientation;
  math::Vec3f m_position;
};

// ------------------------------------------------------------------------------

} // namespace graphics
} // namespace mage