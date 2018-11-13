#include "ecs_common/CameraComponent.h"

#include "ecs/World.h"

namespace mage
{
namespace ecs
{
namespace common
{

// ------------------------------------------------------------------------------

CameraComponent::CameraComponent(World& _world, math::Mat4f _projectionMat)
    : m_cameraId(_world.AddCamera(std::move(_projectionMat)))
{
}

// ------------------------------------------------------------------------------

} // namespace common
} // namespace ecs
} // namespace mage