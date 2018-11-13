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
  for (auto&& system : m_gameSystems)
  {
    system->Initialize(*this);
  }
  for (auto&& system : m_renderingSystems)
  {
    system->Initialize(*this);
  }
}

// ------------------------------------------------------------------------------

void World::OnExit()
{
  for (auto&& system : m_gameSystems)
  {
    system->Uninitialize(*this);
  }
  for (auto&& system : m_renderingSystems)
  {
    system->Uninitialize(*this);
  }
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

  for (auto&& system : m_gameSystems)
  {
    system->OnEntityComponentMaskChange(
        _entity, m_entityManager.GetComponentMaskForEntity(_entity));
  }
  for (auto&& system : m_renderingSystems)
  {
    system->OnEntityComponentMaskChange(
        _entity, m_entityManager.GetComponentMaskForEntity(_entity));
  }

  m_entityManager.RecycleEntity(_entity);
}

// ------------------------------------------------------------------------------

void World::AddGameSystem(std::unique_ptr<GameSystem> _system)
{
  m_gameSystems.push_back(std::move(_system));
}

// ------------------------------------------------------------------------------

void World::TickGameSystems(float _deltaTime)
{
  for (auto&& system : m_gameSystems)
  {
    system->Tick(*this, _deltaTime);
  }
}

// ------------------------------------------------------------------------------

void World::AddRenderingSystem(std::unique_ptr<RenderingSystem> _system)
{
  m_renderingSystems.push_back(std::move(_system));
}

// ------------------------------------------------------------------------------

void World::TickRenderingSystems(float _deltaTime)
{
  for (auto&& system : m_renderingSystems)
  {
    for (const auto& camera : m_cameras)
    {
      system->Render(*this, camera, _deltaTime);
    }
  }
}

// ------------------------------------------------------------------------------

std::uint32_t World::AddCamera(math::Mat4f _projectionMat)
{
  m_cameras.emplace_back(std::move(_projectionMat));
  return m_cameras.size() - 1;
}

// ------------------------------------------------------------------------------

graphics::Camera& World::GetCamera(std::uint32_t _id)
{
  assert(_id < m_cameras.size());
  return m_cameras[_id];
}

// ------------------------------------------------------------------------------

messaging::MessageBus& World::GetApplicationMessageBus()
{
  return m_applicationMessageBus;
}

// ------------------------------------------------------------------------------

} // namespace ecs
} // namespace mage