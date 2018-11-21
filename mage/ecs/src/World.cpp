#include "ecs/World.h"

#include "core/Application.h"

namespace mage
{
namespace ecs
{

// ------------------------------------------------------------------------------

World::World(core::Application& _application)
    : m_componentManagers()
    , m_entityManager()
    , m_gameSystems()
    , m_renderingSystems()
    , m_guiSystems()
    , m_cameras()
    , m_soundLibrary(_application.GetAudioDevice())
    , m_application(_application)
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
  for (auto&& system : m_guiSystems)
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
  for (auto&& system : m_guiSystems)
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
    ComponentMask mask =
        m_entityManager.GetComponentMaskForEntity(m_entitiesToRemove[i]);

    for (auto componentId = 0; componentId < c_maxNumberOfComponentTypes;
         componentId++)
    {
      if (mask.HasComponent(componentId))
      {
        m_componentManagers[componentId]->RemoveComponent(
            m_entitiesToRemove[i]);
      }
    }

    m_entityManager.ResetComponentMask(m_entitiesToRemove[i]);
    m_entityManager.RecycleEntity(m_entitiesToRemove[i]);
  }

  // move the removed entities into the modified container
  if (m_modifiedEntities.empty())
  {
    m_modifiedEntities = std::move(m_entitiesToRemove);
  }
  else
  {
    m_modifiedEntities.reserve(m_modifiedEntities.size() +
                               m_entitiesToRemove.size());

    std::move(std::begin(m_entitiesToRemove), std::end(m_entitiesToRemove),
              std::back_inserter(m_modifiedEntities));

    m_entitiesToRemove.clear();
  }

  // Update the system's registered entities with the ones modified last update
  for (size_t i = 0; i < m_modifiedEntities.size(); i++)
  {
    for (auto&& gameSystem : m_gameSystems)
    {
      gameSystem->OnEntityComponentMaskChange(
          m_modifiedEntities[i],
          m_entityManager.GetComponentMaskForEntity(m_modifiedEntities[i]));
    }
    for (auto&& renderingSystem : m_renderingSystems)
    {
      renderingSystem->OnEntityComponentMaskChange(
          m_modifiedEntities[i],
          m_entityManager.GetComponentMaskForEntity(m_modifiedEntities[i]));
    }
    for (auto&& guiSystem : m_guiSystems)
    {
      guiSystem->OnEntityComponentMaskChange(
          m_modifiedEntities[i],
          m_entityManager.GetComponentMaskForEntity(m_modifiedEntities[i]));
    }
  }

  m_modifiedEntities.clear();
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
  for (const auto& camera : m_cameras)
  {
    const math::Vec4i32& viewport = camera.GetViewport();
    m_application.GetRenderDevice().SetViewport(viewport[0], viewport[1],
                                                viewport[2], viewport[3]);
    for (auto&& system : m_renderingSystems)
    {
      system->Render(*this, camera, _deltaTime);
    }
  }
}

// ------------------------------------------------------------------------------

void World::AddGUISystem(std::unique_ptr<RenderingSystem> _system)
{
  m_guiSystems.push_back(std::move(_system));
}

// ------------------------------------------------------------------------------

void World::TickGUISystems(float _deltaTime)
{
  for (const auto& camera : m_cameras)
  {
    for (auto&& system : m_guiSystems)
    {
      system->Render(*this, camera, _deltaTime);
    }
  }
}

// ------------------------------------------------------------------------------

std::uint32_t World::AddCamera(const math::Vec4i32& _viewport,
                               float _fovDegrees, float _near, float _far,
                               bool _listenForWindowResize)
{
  if (_listenForWindowResize)
  {
    m_cameras.emplace_back(_viewport, _fovDegrees, _near, _far,
                           m_application.GetMessageBus());
  }
  else
  {
    m_cameras.emplace_back(_viewport, _fovDegrees, _near, _far);
  }
  return m_cameras.size() - 1;
}

// ------------------------------------------------------------------------------

graphics::PerspectiveCamera& World::GetCamera(std::uint32_t _id)
{
  assert(_id < m_cameras.size());
  return m_cameras[_id];
}

// ------------------------------------------------------------------------------

messaging::MessageBus& World::GetApplicationMessageBus()
{
  return m_application.GetMessageBus();
}

// ------------------------------------------------------------------------------

audio::SoundLibrary& World::GetSoundLibrary() { return m_soundLibrary; }

// ------------------------------------------------------------------------------

} // namespace ecs
} // namespace mage