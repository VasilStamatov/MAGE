#pragma once

#include <physics/AABBCollisionSystem.h>

// ------------------------------------------------------------------------------

class GameCollisionhandler : public mage::physics::PhysicsSystem
{
public:
  GameCollisionhandler();

  virtual void Initialize(mage::core::World& _world) override;

  virtual void Simulate(mage::core::World& _world, float _deltaSeconds) override;

private:
  void OnCollisionEvent(mage::physics::AABBIntersectionsEvent* _event);

private:
  std::vector<std::pair<mage::ecs::Entity, mage::ecs::Entity>>
      m_entityIntersections;
};

// ------------------------------------------------------------------------------
