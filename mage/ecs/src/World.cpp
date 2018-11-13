#include "ecs/World.h"

namespace mage
{
namespace ecs
{

// ------------------------------------------------------------------------------

World::World(messaging::MessageBus& _applicationMessageBus)
    : m_componentManagers()
    , m_entityManager()
    , m_gameSystems()
    , m_renderingSystems()
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

void World::OnEnter()
{
  m_gameSystems.InitializeSystems(*this);
  m_renderingSystems.InitializeSystems(*this);
}

// ------------------------------------------------------------------------------

void World::OnExit()
{
  m_gameSystems.UninitializeSystems(*this);
  m_renderingSystems.UninitializeSystems(*this);
}

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

  m_gameSystems.OnEntityComponentMaskChange(
      _entity, m_entityManager.GetComponentMaskForEntity(_entity));

  m_renderingSystems.OnEntityComponentMaskChange(
      _entity, m_entityManager.GetComponentMaskForEntity(_entity));

  m_entityManager.RecycleEntity(_entity);
}

// ------------------------------------------------------------------------------

void World::AddGameSystem(std::unique_ptr<System> _system)
{
  m_gameSystems.AddSystem(std::move(_system));
}

// ------------------------------------------------------------------------------

void World::TickGameSystems(float _deltaTime)
{
  m_gameSystems.TickSystems(*this, _deltaTime);
}

// ------------------------------------------------------------------------------

void World::AddRenderingSystem(std::unique_ptr<System> _system)
{
  m_renderingSystems.AddSystem(std::move(_system));
}

// ------------------------------------------------------------------------------

void World::TickRenderingSystems(float _deltaTime)
{
  m_renderingSystems.TickSystems(*this, _deltaTime);
}

// ------------------------------------------------------------------------------

messaging::MessageBus& World::GetApplicationMessageBus()
{
  return m_applicationMessageBus;
}

// ------------------------------------------------------------------------------

} // namespace ecs
} // namespace mage