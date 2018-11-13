#pragma once

#include "ecs/Component.h"
#include "graphics/Camera.h"

namespace mage
{
namespace ecs
{

// ------------------------------------------------------------------------------

class World;

// ------------------------------------------------------------------------------

namespace common
{

// ------------------------------------------------------------------------------

struct CameraComponent : public ecs::Component
{
  CameraComponent(World& _world, math::Mat4f _projectionMat);

  std::uint32_t m_cameraId;
};

// ------------------------------------------------------------------------------

} // namespace common
} // namespace ecs
} // namespace mage