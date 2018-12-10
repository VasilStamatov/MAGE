#include "physics/PhysicsWorld.h"

namespace mage
{
namespace physics
{

// ------------------------------------------------------------------------------

PhysicsWorld::PhysicsWorld(core::World& _ownerWorld)
    : m_physicsSystems()
    , m_ownerWorld(_ownerWorld)
{
}

// ------------------------------------------------------------------------------

PhysicsWorld::~PhysicsWorld() {}

// ------------------------------------------------------------------------------

void PhysicsWorld::Initialize()
{
  for (auto&& physicsSystem : m_physicsSystems)
  {
    physicsSystem->Initialize(m_ownerWorld);
  }
}

// ------------------------------------------------------------------------------

void PhysicsWorld::Uninitialize()
{
  for (auto&& physicsSystem : m_physicsSystems)
  {
    physicsSystem->Uninitialize(m_ownerWorld);
  }
}

// ------------------------------------------------------------------------------

void PhysicsWorld::Simulate(float _deltaSeconds)
{
  for (auto&& physicsSystem : m_physicsSystems)
  {
    physicsSystem->Simulate(m_ownerWorld, _deltaSeconds);
  }
}

// ------------------------------------------------------------------------------

void PhysicsWorld::UpdateEntityStatus(ecs::Entity& _entity,
                                      ecs::ComponentMask _entitySignature)
{
  for (auto&& physicsSystem : m_physicsSystems)
  {
    physicsSystem->OnEntityComponentMaskChange(_entity, _entitySignature);
  }
}

// ------------------------------------------------------------------------------

void PhysicsWorld::AddPhysicsSystem(std::unique_ptr<PhysicsSystem> _system)
{
  m_physicsSystems.emplace_back(std::move(_system));
}

// ------------------------------------------------------------------------------

} // namespace physics
} // namespace mage