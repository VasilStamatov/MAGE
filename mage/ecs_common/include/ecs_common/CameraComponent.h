#pragma once

#include "ecs/Component.h"
#include "graphics/PerspectiveCamera.h"

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
  CameraComponent(World& _world, const math::Vec4i32& _viewport,
                  float _fovDegrees, float _near, float _far,
                  bool _listenForWindowResize);

  std::uint32_t m_cameraId;
};

// ------------------------------------------------------------------------------

} // namespace common
} // namespace ecs
} // namespace mage