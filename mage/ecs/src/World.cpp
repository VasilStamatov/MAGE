#include "ecs/World.h"

namespace mage
{
namespace ecs
{

// ------------------------------------------------------------------------------

World::World(messaging::MessageBus& _applicationMessageBus)
    : m_componentManagers()
    , m_entityManager()
    , m_systemManager()
    , m_applicationMessageBus(_applicationMessageBus)
{
}

// ------------------------------------------------------------------------------

World::~World() {}

// ------------------------------------------------------------------------------

void World::Initialize()
{
  AddSystems();
  AddEntitiesAndComponents();
}

// ------------------------------------------------------------------------------

void World::OnEnter() { m_systemManager.InitializeSystems(*this); }

// ------------------------------------------------------------------------------

void World::OnExit() { m_systemManager.UninitializeSystems(*this); }

// ------------------------------------------------------------------------------

EntityHandle World::CreateEntity()
{
  return EntityHandle(*this, m_entityManager.CreateEntity());
}

// ------------------------------------------------------------------------------

void World::DestroyEntity(Entity& _entity)
{
  ComponentMask mask = m_entityManager.GetComponentMaskForEntity(_entity);

  for (auto i = 0; i < c_maxNumberOfComponentTypes; i++)
  {
    if (mask.HasComponent(i))
    {
      m_componentManagers[i]->RemoveComponent(_entity);
    }
  }

  m_entityManager.ResetComponentMask(_entity);

  m_systemManager.OnEntityComponentMaskChange(
      _entity, m_entityManager.GetComponentMaskForEntity(_entity));

  m_entityManager.RecycleEntity(_entity);
}

// ------------------------------------------------------------------------------

void World::AddSystem(std::unique_ptr<System> _system)
{
  m_systemManager.AddSystem(std::move(_system));
}

// ------------------------------------------------------------------------------

void World::TickSystems(float _deltaTime)
{
  m_systemManager.TickSystems(*this, _deltaTime);
}

// ------------------------------------------------------------------------------

messaging::MessageBus& World::GetApplicationMessageBus()
{
  return m_applicationMessageBus;
}

// ------------------------------------------------------------------------------

} // namespace ecs
} // namespace mage