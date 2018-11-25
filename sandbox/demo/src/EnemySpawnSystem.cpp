#include "demo/EnemySpawnSystem.h"

#include <ecs/World.h>
#include <ecs_common/TransformComponent.h>
#include <graphics/StaticMeshRenderer.h>
#include <physics/AABBCollisionSystem.h>
#include <physics/MotionSystem.h>

EntitySpawnComponent::EntitySpawnComponent(
    std::shared_ptr<mage::graphics::OBJModel> _enemyModel,
    std::shared_ptr<mage::graphics::GLTexture2D> _enemyTexture,
    float _spawnExtentsRadius, float _spawnFrequency)
    : m_enemyModel(_enemyModel)
    , m_enemyTexture(_enemyTexture)
    , m_spawnExtentsRadius(_spawnExtentsRadius)
    , m_spawnFrequency(_spawnFrequency)
{
}

EntitySpawnSystem::EntitySpawnSystem()
    : m_rng()
{
  m_systemSignature.AddComponent<EntitySpawnComponent>();
  m_systemSignature.AddComponent<mage::ecs::common::TransformComponent>();
}

void EntitySpawnSystem::Initialize(mage::ecs::World& _world) {}

void EntitySpawnSystem::Tick(mage::ecs::World& _world, float _deltaTime)
{
  for (auto&& entity : m_registeredEntities)
  {
    auto* spawner = _world.GetComponent<EntitySpawnComponent>(entity);

    spawner->m_counter += _deltaTime;
    if (spawner->m_counter >= spawner->m_spawnFrequency)
    {
      spawner->m_counter = 0.0f;
      // spawn
      auto& location =
          _world.GetComponent<mage::ecs::common::TransformComponent>(entity)
              ->m_transform.GetTranslation();

      auto newEntity = _world.CreateEntity();

      auto& newEntityTransform =
          newEntity.AddComponent<mage::ecs::common::TransformComponent>();

      mage::math::Vec3f spawnLocation(
          m_rng.GenRandReal(location[0] - spawner->m_spawnExtentsRadius,
                            location[0] + spawner->m_spawnExtentsRadius),
          location[1], location[2]);

      newEntityTransform.m_transform.SetTranslation(spawnLocation);

      auto& staticMeshComp =
          newEntity.AddComponent<mage::graphics::StaticMeshComponent>(
              *spawner->m_enemyModel, spawner->m_enemyTexture);

      auto& colliderComponent =
          newEntity.AddComponent<mage::physics::AABBCollider>(
              spawner->m_enemyModel->GetAABB());

      auto& motionComponent = newEntity.AddComponent<mage::physics::Motion>();
      motionComponent.m_acceleration = mage::math::Vec3f(0.0f, 0.0f, 30.0f);
    }
  }
}