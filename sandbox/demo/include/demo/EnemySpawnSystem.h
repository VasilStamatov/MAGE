#pragma once

#include <ecs/GameSystem.h>

#include <graphics/OBJModelLibrary.h>
#include <graphics/Texture2DLibrary.h>
#include <util/RandomNumberGenerator.h>

// ------------------------------------------------------------------------------

struct EntitySpawnComponent : public mage::ecs::Component
{
  EntitySpawnComponent(
      std::shared_ptr<mage::graphics::OBJModel> _enemyModel,
      std::shared_ptr<mage::graphics::GLTexture2D> _enemyTexture,
      float _spawnExtentsRadius, float _spawnFrequency);

  std::shared_ptr<mage::graphics::OBJModel> m_enemyModel;
  std::shared_ptr<mage::graphics::GLTexture2D> m_enemyTexture;
  float m_spawnExtentsRadius = 1.0f;
  float m_spawnFrequency = 10.0f;
  float m_counter = 0.0f;
};

// ------------------------------------------------------------------------------

class EntitySpawnSystem : public mage::ecs::GameSystem
{
public:
  EntitySpawnSystem();

  virtual void Initialize(mage::ecs::World& _world) override;

  virtual void Tick(mage::ecs::World& _world, float _deltaTime) override;

private:
  mage::util::RandomNumberGenerator m_rng;
};

// ------------------------------------------------------------------------------
