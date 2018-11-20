#include "physics/MotionSystem.h"

#include "ecs/World.h"
#include "ecs_common/TransformComponent.h"
#include "physics/MotionIntegrators.h"

namespace mage
{
namespace physics
{

// ------------------------------------------------------------------------------

MotionSystem::MotionSystem()
{
  m_systemSignature.AddComponent<ecs::common::TransformComponent>();
  m_systemSignature.AddComponent<Motion>();
}

// ------------------------------------------------------------------------------

void MotionSystem::Tick(ecs::World& _world, float _deltaTime)
{
  for (auto&& entity : m_registeredEntities)
  {
    auto& transform =
        _world.GetComponent<ecs::common::TransformComponent>(entity)
            .m_transform;
    auto& motion = _world.GetComponent<Motion>(entity);

    math::Vec3f newPos = transform.GetTranslation();
    MotionIntegrators::ForestRuth(newPos, motion.m_velocity,
                                  motion.m_acceleration, _deltaTime);
    transform.SetTranslation(newPos);

    // TODO: This is a cheap hack to get resistance for now! Replace with a
    // proper system later
    motion.m_velocity *= 0.95f;
    motion.m_acceleration *= 0.95f;
  }
}

// ------------------------------------------------------------------------------

} // namespace physics
} // namespace mage