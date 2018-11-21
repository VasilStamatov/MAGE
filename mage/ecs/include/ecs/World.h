#pragma once

#include "ComponentManager.h"
#include "EntityHandle.h"
#include "EntityManager.h"
#include "GameSystem.h"
#include "RenderingSystem.h"
#include "audio/SoundLibrary.h"

#include <array>

namespace mage
{

namespace core
{
class Application;
}

namespace messaging
{
class MessageBus;
}

namespace ecs
{

// ------------------------------------------------------------------------------

class World
{
public:
  World(core::Application& _application);
  virtual ~World();

  // ------------------------------------------------------------------------------

  void Initialize();

  // ------------------------------------------------------------------------------

  void OnEnter();
  void OnExit();

  // ------------------------------------------------------------------------------

  EntityHandle CreateEntity();
  void DestroyEntity(Entity& _entity);

  // ------------------------------------------------------------------------------

  void RefreshEntityState();

  // ------------------------------------------------------------------------------

  void AddGameSystem(std::unique_ptr<GameSystem> _system);
  void TickGameSystems(float _deltaTime);

  // ------------------------------------------------------------------------------

  void AddRenderingSystem(std::unique_ptr<RenderingSystem> _system);
  void TickRenderingSystems(float _deltaTime);

  // ------------------------------------------------------------------------------

  void AddGUISystem(std::unique_ptr<RenderingSystem> _system);
  void TickGUISystems(float _deltaTime);

  // ------------------------------------------------------------------------------

  std::uint32_t AddPerspectiveCamera(const math::Vec4i32& _viewport,
                                     float _fovDegrees, float _near, float _far,
                                     bool _listenForWindowResize);
  std::uint32_t AddOrthographicCamera(const math::Vec4i32& _viewport,
                                      float _near, float _far,
                                      bool _listenForWindowResize);
  graphics::Camera& GetCamera(std::uint32_t _id);

  // ------------------------------------------------------------------------------

  template <typename ComponentType, typename... TArgs>
  ComponentType& AddComponent(Entity _entity, TArgs&&... _constructionArgs)
  {
    ComponentManager<ComponentType>* manager =
        GetPtrToDerivedComponentManager<ComponentType>();

    ComponentType& componentRef = manager->AddComponent(
        _entity, std::forward<TArgs>(_constructionArgs)...);

    m_entityManager.AddComponent<ComponentType>(_entity);

    if (std::find(m_modifiedEntities.begin(), m_modifiedEntities.end(),
                  _entity) == m_modifiedEntities.end())
    {
      m_modifiedEntities.push_back(_entity);
    }

    return componentRef;
  }

  // ------------------------------------------------------------------------------

  template <typename ComponentType> void RemoveComponent(Entity _entity)
  {
    ComponentManager<ComponentType>* manager =
        GetPtrToDerivedComponentManager<ComponentType>();

    manager->RemoveComponent(_entity);

    m_entityManager.RemoveComponent<ComponentType>(_entity);

    if (std::find(m_modifiedEntities.begin(), m_modifiedEntities.end(),
                  _entity) == m_modifiedEntities.end())
    {
      m_modifiedEntities.push_back(_entity);
    }
  }

  // ------------------------------------------------------------------------------

  template <typename ComponentType> ComponentType& GetComponent(Entity _entity)
  {
    ComponentManager<ComponentType>* manager =
        GetPtrToDerivedComponentManager<ComponentType>();
    return manager->GetComponent(_entity);
  }

  // ------------------------------------------------------------------------------

  template <typename ComponentType>
  std::vector<ComponentType>& GetAllComponentsOfType()
  {
    ComponentManager<ComponentType>* manager =
        GetPtrToDerivedComponentManager<ComponentType>();
    return manager->GetAllComponents();
  }

  // ------------------------------------------------------------------------------

  messaging::MessageBus& GetApplicationMessageBus();
  audio::SoundLibrary& GetSoundLibrary();

  // ------------------------------------------------------------------------------

private:
  virtual void AddSystems() = 0;
  virtual void AddEntitiesAndComponents() = 0;

  // ------------------------------------------------------------------------------

  template <typename ComponentType>
  ComponentManager<ComponentType>* GetPtrToDerivedComponentManager()
  {
    const std::int32_t componentTypeId = GetComponentTypeId<ComponentType>();
    auto& baseComponentManager = m_componentManagers[componentTypeId];
    if (baseComponentManager == nullptr)
    {
      baseComponentManager =
          std::make_unique<ComponentManager<ComponentType>>();
    }
    return static_cast<ComponentManager<ComponentType>*>(
        baseComponentManager.get());
  }

  // ------------------------------------------------------------------------------

protected:
  std::array<std::unique_ptr<BaseComponentManager>, c_maxNumberOfComponentTypes>
      m_componentManagers;
  EntityManager m_entityManager;
  std::vector<Entity> m_entitiesToRemove;
  std::vector<Entity> m_modifiedEntities;
  std::vector<std::unique_ptr<GameSystem>> m_gameSystems;
  std::vector<std::unique_ptr<RenderingSystem>> m_renderingSystems;
  std::vector<std::unique_ptr<RenderingSystem>> m_guiSystems;

  std::vector<graphics::Camera> m_cameras;
  graphics::Camera m_screenCamera;

  audio::SoundLibrary m_soundLibrary;
  core::Application& m_application;
};

// ------------------------------------------------------------------------------

} // namespace ecs
} // namespace mage