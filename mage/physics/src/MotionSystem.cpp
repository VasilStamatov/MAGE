#include "physics/MotionSystem.h"

#include "core/World.h"
#include "ecs_common/TransformComponent.h"
#include "physics/MotionIntegrators.h"
#include "scheduler/ParallelFor.h"

namespace mage
{
namespace physics
{

// ------------------------------------------------------------------------------

struct MotionTaskData
{
  MotionTaskData(math::Transform* _transform, Motion* _motion,
                 float _deltaSeconds)
      : m_transform(_transform)
      , m_motion(_motion)
      , m_deltaSeconds(_deltaSeconds)
  {
  }

  math::Transform* m_transform;
  Motion* m_motion;
  float m_deltaSeconds;
};

// ------------------------------------------------------------------------------

void MotionTaskExecutor(MotionTaskData* _data, std::uint32_t _count)
{
  for (size_t i = 0; i < _count; i++)
  {
    math::Vec3f newPos = _data[i].m_transform->GetTranslation();
    MotionIntegrators::Verlet(newPos, _data[i].m_motion->m_velocity,
                              _data[i].m_motion->m_acceleration,
                              _data[i].m_deltaSeconds);

    _data[i].m_transform->SetTranslation(newPos);

    // TODO: This is a cheap hack to get resistance for now! Replace
    // with a proper system later
    _data[i].m_motion->m_velocity *= 0.95f;
    _data[i].m_motion->m_acceleration *= 0.95f;
  }
}

// ------------------------------------------------------------------------------

MotionSystem::MotionSystem()
{
  m_systemSignature.AddComponent<ecs::common::TransformComponent>();
  m_systemSignature.AddComponent<Motion>();
}

// ------------------------------------------------------------------------------

void MotionSystem::Simulate(core::World& _world, float _deltaSeconds)
{
  std::vector<MotionTaskData> taskData;
  taskData.reserve(m_registeredEntities.size());

  for (auto&& entity : m_registeredEntities)
  {
    auto* transform =
        &_world.GetComponent<ecs::common::TransformComponent>(entity)
             ->m_transform;
    auto* motion = _world.GetComponent<Motion>(entity);

    taskData.emplace_back(transform, motion, _deltaSeconds);
  }

  auto motionTask =
      scheduler::ParralelFor<MotionTaskData, scheduler::CountSplitter>(
          taskData.data(), taskData.size(), MotionTaskExecutor,
          scheduler::CountSplitter(128));

  scheduler::Run(motionTask);
  scheduler::Wait(motionTask);
}

// ------------------------------------------------------------------------------

} // namespace physics
} // namespace mage