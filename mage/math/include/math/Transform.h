#pragma once

#include "Quat.h"

namespace mage
{
namespace math
{

// ------------------------------------------------------------------------------

class Transform
{
public:
  Transform();

  // ------------------------------------------------------------------------------

  void Rotate(const Quatf& _amountToRotation);
  void Translate(const Vec3f& _translation);
  void Scale(const Vec3f& _scalingToAdd);

  // ------------------------------------------------------------------------------

  void SetRotation(const Quatf& _rotation);
  void SetTranslation(const Vec3f& _translation);
  void SetScale(const Vec3f& _scale);

  // ------------------------------------------------------------------------------

  const Quatf& GetRotation() const;
  const Vec3f& GetTranslation() const;
  const Vec3f& GetScale() const;

  // ------------------------------------------------------------------------------

  Vec3f GetRightAxis() const;
  Vec3f GetUpAxis() const;
  Vec3f GetForwardAxis() const;

  // ------------------------------------------------------------------------------

  Mat4f ToMatrix() const;

  // ------------------------------------------------------------------------------

private:
  Quatf m_rotation;
  Vec3f m_translation;
  Vec3f m_scale;
};

// ------------------------------------------------------------------------------

} // namespace math
} // namespace mage