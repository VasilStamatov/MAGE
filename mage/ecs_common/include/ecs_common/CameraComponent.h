#pragma once

#include "ecs/Component.h"

namespace mage
{
namespace ecs
{
namespace common
{

// ------------------------------------------------------------------------------

/////////////////////////////////////////////////
/// The Camera component adds a camera to the world and stores its Id.
/////////////////////////////////////////////////
struct CameraComponent : public ecs::Component
{
  CameraComponent(std::uint32_t _cameraId);

  std::uint32_t m_cameraId;
};

// ------------------------------------------------------------------------------

} // namespace common
} // namespace ecs
} // namespace mage