#pragma once

#include "PhysicsSystem.h"

#include <memory>

namespace mage
{
namespace physics
{

// ------------------------------------------------------------------------------

class PhysicsWorld
{
public:
  PhysicsWorld(core::World& _ownerWorld);
  ~PhysicsWorld();

  // ------------------------------------------------------------------------------

  void Initialize();
  void Uninitialize();

  // ------------------------------------------------------------------------------

  void Simulate(float _deltaSeconds);

  // ------------------------------------------------------------------------------

  void UpdateEntityStatus(ecs::Entity& _entity,
                          ecs::ComponentMask _entitySignature);

  // ------------------------------------------------------------------------------

  void AddPhysicsSystem(std::unique_ptr<PhysicsSystem> _system);

private:
  std::vector<std::unique_ptr<PhysicsSystem>> m_physicsSystems;

  core::World& m_ownerWorld;
};

// ------------------------------------------------------------------------------

} // namespace physics
} // namespace mage