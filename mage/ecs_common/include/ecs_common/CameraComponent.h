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

/////////////////////////////////////////////////
/// The Camera component adds a camera to the world and stores its Id.
/////////////////////////////////////////////////
struct CameraComponent : public ecs::Component
{
  CameraComponent(World& _world, const math::Vec4i32& _viewport,
                  float _fovDegrees, float _near, float _far,
                  bool _listenForWindowResize);
  CameraComponent(World& _world, const math::Vec4i32& _viewport, float _near,
                  float _far, bool _listenForWindowResize);

  std::uint32_t m_cameraId;
};

// ------------------------------------------------------------------------------

} // namespace common
} // namespace ecs
} // namespace mage