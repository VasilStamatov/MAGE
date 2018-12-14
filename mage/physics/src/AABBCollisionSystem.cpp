#include "physics/AABBCollisionSystem.h"

#include "core/Application.h"
#include "core/Timer.h"
#include "ecs_common/TransformComponent.h"
#include "logger/LogDispatch.h"
#include "physics/SpatialPartition.h"
#include "scheduler/Scheduler.h"

namespace mage
{
namespace physics
{

// ------------------------------------------------------------------------------

struct CollisionData
{
  CollisionData(math::AABB _AABB, ecs::Entity _entity)
      : m_AABB(std::move(_AABB))
      , m_entity(_entity)
  {
  }

  math::AABB m_AABB;
  ecs::Entity m_entity;
};

// ------------------------------------------------------------------------------

struct OutputPartitionData
{
  OutputPartitionData()
      : m_AABB(math::Vec3f(0.0f), math::Vec3f(0.0f))
      , m_entity(0)
  {
  }
  math::AABB m_AABB;
  ecs::Entity m_entity;
  float m_xPos;
  float m_yPos;
  float m_sizeX;
  float m_sizeY;
};

// ------------------------------------------------------------------------------

struct CollisionPrepData
{
  CollisionPrepData(math::Transform* _transform, math::AABB* _AABB,
                    OutputPartitionData* _output, ecs::Entity _entity)
      : m_transform(_transform)
      , m_AABB(_AABB)
      , m_output(_output)
      , m_entity(_entity)
  {
  }

  math::Transform* m_transform;
  math::AABB* m_AABB;
  OutputPartitionData* m_output;
  ecs::Entity m_entity;
};

// ------------------------------------------------------------------------------

struct CollisionTaskData
{
  using IntersectionOutput = std::vector<std::pair<ecs::Entity, ecs::Entity>>;

  CollisionTaskData(CollisionData* _collisionData,
                    IntersectionOutput* _outputIntersections,
                    std::uint32_t _count)
      : m_collisionData(_collisionData)
      , m_outputIntersections(_outputIntersections)
      , m_count(_count)
  {
  }

  CollisionData* m_collisionData;
  IntersectionOutput* m_outputIntersections;
  std::uint32_t m_count;
};

// ------------------------------------------------------------------------------

static void CollisionPrepTask(scheduler::Task* _task, const void* _taskData)
{
  const CollisionPrepData* data =
      static_cast<const CollisionPrepData*>(_taskData);

  math::AABB aabb = data->m_AABB->Transform(data->m_transform->ToMatrix());

  data->m_output->m_AABB = aabb;
  data->m_output->m_entity = data->m_entity;
  data->m_output->m_xPos = data->m_transform->GetTranslation()[0];
  data->m_output->m_yPos = data->m_transform->GetTranslation()[2];
  data->m_output->m_sizeX = aabb.GetExtents()[0];
  data->m_output->m_sizeY = aabb.GetExtents()[2];
}

// ------------------------------------------------------------------------------

static void CollisionTask(scheduler::Task* _task, const void* _taskData)
{
  const CollisionTaskData* data =
      static_cast<const CollisionTaskData*>(_taskData);

  for (size_t firstE = 0; firstE < data->m_count - 1; firstE++)
  {
    auto& aabbFirst = data->m_collisionData[firstE].m_AABB;

    for (size_t secondE = firstE + 1; secondE < data->m_count; secondE++)
    {
      auto& aabbSecond = data->m_collisionData[secondE].m_AABB;

      if (aabbFirst.Intersects(aabbSecond))
      {
        data->m_outputIntersections->emplace_back(
            data->m_collisionData[firstE].m_entity,
            data->m_collisionData[secondE].m_entity);
      }
    }
  }
}

// ------------------------------------------------------------------------------

AABBCollider::AABBCollider(math::AABB _AABB)
    : m_AABB(std::move(_AABB))
{
}

// ------------------------------------------------------------------------------

AABBCollisionSystem::AABBCollisionSystem()
{
  m_systemSignature.AddComponent<ecs::common::TransformComponent>();
  m_systemSignature.AddComponent<AABBCollider>();
}

// ------------------------------------------------------------------------------
// Sequential:
// Collision System: 40 entities completed in: 0.246433 millis
// Collision System: 82 entities completed in: 1.588382 millis
// Collision System: 124 entities completed in: 4.206631 millis
// Collision System: 147 entities completed in: 7.337818 millis
// Collision System: 165 entities completed in: 7.695006 millis
// Collision System: 207 entities completed in: 12.830264 millis
// Collision System: 249 entities completed in: 18.874182 millis
// Collision System: 290 entities completed in: 25.575478 millis
// Collision System: 332 entities completed in: 32.745750 millis
// Collision System: 374 entities completed in: 41.762585 millis
// Collision System: 415 entities completed in: 52.885708 millis
// Collision System: 457 entities completed in: 63.851246 millis
// Parallel
// Collision System: 31 entities completed in: 0.231935 millis
// Collision System: 73 entities completed in: 0.340373 millis
// Collision System: 114 entities completed in: 0.379546 millis
// Collision System: 156 entities completed in: 0.351007 millis
// Collision System: 198 entities completed in: 0.440579 millis
// Collision System: 239 entities completed in: 0.810518 millis
// Collision System: 281 entities completed in: 0.854617 millis
// Collision System: 323 entities completed in: 0.999358 millis
// Collision System: 364 entities completed in: 1.105345 millis
// Collision System: 406 entities completed in: 1.302463 millis
// Collision System: 448 entities completed in: 1.309489 millis
// Collision System: 489 entities completed in: 1.391028 millis
void AABBCollisionSystem::Simulate(core::World& _world, float _deltaSeconds)
{
  AABBIntersectionsEvent intersections;

  SpatialPartition<CollisionData> partition(64.0f);

  std::vector<OutputPartitionData> m_outDataForPartition;
  m_outDataForPartition.resize(m_registeredEntities.size());

  auto* prepTask = scheduler::CreateTask(scheduler::EmptyTask);

  for (size_t i = 0; i < m_registeredEntities.size(); i++)
  {
    auto& entity = m_registeredEntities[i];

    auto* transform =
        &_world.GetComponent<ecs::common::TransformComponent>(entity)
             ->m_transform;
    auto* aabb = _world.GetComponent<AABBCollider>(entity);

    CollisionPrepData data(transform, &aabb->m_AABB, &m_outDataForPartition[i],
                           entity);

    auto* task = scheduler::CreateChildTask(prepTask, CollisionPrepTask, &data,
                                            sizeof(data));

    scheduler::Run(task);
  }

  scheduler::Run(prepTask);
  scheduler::Wait(prepTask);

  for (auto&& output : m_outDataForPartition)
  {
    partition.AddItem(CollisionData(output.m_AABB, output.m_entity),
                      output.m_xPos, output.m_yPos, output.m_sizeX,
                      output.m_sizeY);
  }

  auto& buckets = partition.GetBuckets();

  // LOG_INFO("AABB Collision",
  //          "Bucket size: " + std::to_string(buckets.size()) + '\n');

  auto* collisionTask = scheduler::CreateTask(scheduler::EmptyTask);

  std::vector<CollisionTaskData::IntersectionOutput> outputIntersections;
  outputIntersections.resize(buckets.size());

  int counter = 0;
  for (auto&& bucket : buckets)
  {
    CollisionTaskData data(bucket.second.data(), &outputIntersections[counter],
                           bucket.second.size());

    counter++;

    auto* task = scheduler::CreateChildTask(collisionTask, CollisionTask, &data,
                                            sizeof(data));

    scheduler::Run(task);
  }

  scheduler::Run(collisionTask);
  scheduler::Wait(collisionTask);

  for (auto&& output : outputIntersections)
  {
    std::move(output.begin(), output.end(),
              std::back_inserter(intersections.m_entityIntersections));
  }

  if (!intersections.m_entityIntersections.empty())
  {
    _world.GetApplication().GetMessageBus().Broadcast(&intersections);
  }
}

// ------------------------------------------------------------------------------

} // namespace physics
} // namespace mage