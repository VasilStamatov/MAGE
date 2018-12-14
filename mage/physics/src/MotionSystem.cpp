#include "physics/MotionSystem.h"

#include "core/Timer.h"
#include "core/World.h"
#include "ecs_common/TransformComponent.h"
#include "logger/LogDispatch.h"
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

static void MotionTask(scheduler::Task* _task, const void* _taskData)
{
  const MotionTaskData* data = static_cast<const MotionTaskData*>(_taskData);

  math::Vec3f newPos = data->m_transform->GetTranslation();
  MotionIntegrators::Verlet(newPos, data->m_motion->m_velocity,
                            data->m_motion->m_acceleration,
                            data->m_deltaSeconds);

  data->m_transform->SetTranslation(newPos);

  // TODO: This is a cheap hack to get resistance for now! Replace
  // with a proper system later
  data->m_motion->m_velocity *= 0.95f;
  data->m_motion->m_acceleration *= 0.95f;
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
  auto* rootTask = scheduler::CreateTask(scheduler::EmptyTask);

  for (auto&& entity : m_registeredEntities)
  {
    auto* transform =
        &_world.GetComponent<ecs::common::TransformComponent>(entity)
             ->m_transform;
    auto* motion = _world.GetComponent<Motion>(entity);

    MotionTaskData data(transform, motion, _deltaSeconds);

    auto* task =
        scheduler::CreateChildTask(rootTask, MotionTask, &data, sizeof(data));

    scheduler::Run(task);
  }

  scheduler::Run(rootTask);
  scheduler::Wait(rootTask);
}

// ------------------------------------------------------------------------------

} // namespace physics
} // namespace mage