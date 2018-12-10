#include "core/World.h"

#include "core/Application.h"

namespace mage
{
namespace core
{

// ------------------------------------------------------------------------------

World::World(Application& _ownerApplication)
    : m_ownerApplication(_ownerApplication)
    , m_gameWorld(*this)
    , m_audioWorld(_ownerApplication.GetAudioDevice(), *this)
    , m_renderWorld(_ownerApplication.GetRenderDevice(), *this)
    , m_physicsWorld(*this)
    , m_componentManagers()
    , m_entityManager()
    , m_entitiesToRemove()
    , m_modifiedEntities()
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
  m_gameWorld.Initialize();
  m_audioWorld.Initialize();
  m_renderWorld.Initialize();
  m_physicsWorld.Initialize();
}

// ------------------------------------------------------------------------------

void World::OnExit()
{
  m_physicsWorld.Uninitialize();
  m_renderWorld.Uninitialize();
  m_audioWorld.Uninitialize();
  m_gameWorld.Uninitialize();
}

// ------------------------------------------------------------------------------

EntityHandle World::CreateEntity()
{
  return EntityHandle(*this, m_entityManager.CreateEntity());
}

// ------------------------------------------------------------------------------

void World::DestroyEntity(ecs::Entity& _entity)
{
  m_entitiesToRemove.push_back(_entity);
}

// ------------------------------------------------------------------------------

void World::RefreshEntityState()
{
  if (m_entitiesToRemove.empty() && m_modifiedEntities.empty())
  {
    // no need to refresh any entities
    return;
  }

  // Remove entities destroyed from the last update
  for (size_t i = 0; i < m_entitiesToRemove.size(); i++)
  {
    ecs::ComponentMask mask =
        m_entityManager.GetComponentMaskForEntity(m_entitiesToRemove[i]);

    for (auto componentId = 0; componentId < ecs::c_maxNumberOfComponentTypes;
         componentId++)
    {
      if (mask.HasComponent(componentId))
      {
        m_componentManagers[componentId]->RemoveComponent(
            m_entitiesToRemove[i]);
      }
    }

    m_entityManager.ResetComponentMask(m_entitiesToRemove[i]);

    m_modifiedEntities.push_back(m_entitiesToRemove[i]);

    m_entityManager.RecycleEntity(m_entitiesToRemove[i]);
  }
  m_entitiesToRemove.clear();

  for (size_t i = 0; i < m_modifiedEntities.size(); i++)
  {
    m_gameWorld.UpdateEntityStatus(
        m_modifiedEntities[i],
        m_entityManager.GetComponentMaskForEntity(m_modifiedEntities[i]));

    m_audioWorld.UpdateEntityStatus(
        m_modifiedEntities[i],
        m_entityManager.GetComponentMaskForEntity(m_modifiedEntities[i]));

    m_renderWorld.UpdateEntityStatus(
        m_modifiedEntities[i],
        m_entityManager.GetComponentMaskForEntity(m_modifiedEntities[i]));

    m_physicsWorld.UpdateEntityStatus(
        m_modifiedEntities[i],
        m_entityManager.GetComponentMaskForEntity(m_modifiedEntities[i]));
  }

  m_modifiedEntities.clear();
}

// ------------------------------------------------------------------------------

void World::AddGameSystem(std::unique_ptr<ecs::GameSystem> _system)
{
  m_gameWorld.AddGameSystem(std::move(_system));
}

// ------------------------------------------------------------------------------

void World::AddAudioSystem(std::unique_ptr<audio::AudioSystem> _system)
{
  m_audioWorld.AddAudioSystem(std::move(_system));
}

// ------------------------------------------------------------------------------

void World::AddRenderingSystem(
    std::unique_ptr<graphics::RenderingSystem> _system)
{
  m_renderWorld.AddRenderingSystem(std::move(_system));
}

// ------------------------------------------------------------------------------

void World::AddPostProcessPass(
    std::unique_ptr<graphics::PostProcessPipeline> _pipeline)
{
  m_renderWorld.AddPostProcessPipeline(std::move(_pipeline));
}

// ------------------------------------------------------------------------------

void World::AddGUISystem(std::unique_ptr<graphics::RenderingSystem> _system)
{
  m_renderWorld.AddGUISystem(std::move(_system));
}

// ------------------------------------------------------------------------------

void World::AddPhysicsSystem(std::unique_ptr<physics::PhysicsSystem> _system)
{
  m_physicsWorld.AddPhysicsSystem(std::move(_system));
}

// ------------------------------------------------------------------------------

void World::Update(float _deltaSeconds)
{
  m_gameWorld.Tick(_deltaSeconds);
  m_physicsWorld.Simulate(_deltaSeconds);
  m_audioWorld.Tick();
}

// ------------------------------------------------------------------------------

void World::Render(float _interpolation)
{
  m_renderWorld.Render(_interpolation);
}

// ------------------------------------------------------------------------------

} // namespace core
} // namespace mage