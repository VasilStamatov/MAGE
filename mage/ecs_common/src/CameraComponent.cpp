#include "ecs_common/CameraComponent.h"

#include "ecs/World.h"

namespace mage
{
namespace ecs
{
namespace common
{

// ------------------------------------------------------------------------------

CameraComponent::CameraComponent(World& _world, const math::Vec4i32& _viewport,
                                 float _fovDegrees, float _near, float _far,
                                 bool _listenForWindowResize)
    : m_cameraId(_world.AddPerspectiveCamera(_viewport, _fovDegrees, _near,
                                             _far, _listenForWindowResize))
{
}

// ------------------------------------------------------------------------------

CameraComponent::CameraComponent(World& _world, const math::Vec4i32& _viewport,
                                 float _near, float _far,
                                 bool _listenForWindowResize)
    : m_cameraId(_world.AddOrthographicCamera(_viewport, _near, _far,
                                              _listenForWindowResize))
{
}

// ------------------------------------------------------------------------------

} // namespace common
} // namespace ecs
} // namespace mage