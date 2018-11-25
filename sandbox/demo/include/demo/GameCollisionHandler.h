#pragma once

#include <physics/AABBCollisionSystem.h>

// ------------------------------------------------------------------------------

class GameCollisionhandler : public mage::ecs::GameSystem
{
public:
  GameCollisionhandler();

  virtual void Initialize(mage::ecs::World& _world) override;

  virtual void Tick(mage::ecs::World& _world, float _deltaTime) override;

private:
  void OnCollisionEvent(mage::physics::AABBIntersectionsEvent* _event);

private:
  std::vector<std::pair<mage::ecs::Entity, mage::ecs::Entity>>
      m_entityIntersections;
};

// ------------------------------------------------------------------------------
