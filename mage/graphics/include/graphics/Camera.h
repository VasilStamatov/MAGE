#pragma once

#include "math/Transform.h"

namespace mage
{
namespace graphics
{

class Camera
{
public:
  Camera(math::Mat4f _projection);

  math::Mat4f GetProjection() const;
  math::Mat4f GetView() const;

  void Translate(const math::Vec3f& _translation);
  void Rotate(const math::Vec3f& _axis, float _angleRad);

  void SetPosition(const math::Vec3f _position);
  void SetRotation(const math::Vec3f& _axis, float _angleRad);

private:
  math::Mat4f m_projection;
  math::Transform m_transform;
};

} // namespace graphics
} // namespace mage